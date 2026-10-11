#!/usr/bin/env python3
"""Orthogonal jumper routing that keeps wires off each other and off parts.

Every Pi-to-board jumper is drawn as four segments: out of the header, along
a vertical lane in the corridor between the Pi and the board, along a
horizontal lane clear of the board, then straight down (or up) into the
target column. Lanes are allocated so that two wires sharing a lane never
share a span, which is what makes overlap impossible rather than unlikely.
"""

# Standard library
from typing import List, Tuple

# Local
from board import Parts


class LaneSet:
    """Parallel lanes, each holding non-overlapping spans."""

    PAD: float = 0.45

    def __init__(self, base: float, step: float) -> None:
        self._base = base
        self._step = step
        self._lanes: List[List[Tuple[float, float]]] = []

    def assign(self, low: float, high: float) -> float:
        """Return the coordinate of a lane with room for this span."""
        span = (min(low, high), max(low, high))
        for index, taken in enumerate(self._lanes):
            if self._fits(span, taken):
                taken.append(span)
                return self._coordinate(index)
        self._lanes.append([span])
        return self._coordinate(len(self._lanes) - 1)

    def _fits(self, span: Tuple[float, float],
              taken: List[Tuple[float, float]]) -> bool:
        """True when the span clears every span already in that lane."""
        low, high = span
        return all(high < a - self.PAD or low > b + self.PAD for a, b in taken)

    def base(self) -> float:
        """The first lane's coordinate, used as a provisional target."""
        return self._base

    def _coordinate(self, index: int) -> float:
        """Where the n-th lane sits."""
        return self._base + index * self._step


class Router:
    """Allocates lanes and draws the four-segment jumpers."""

    LANE_STEP: float = 0.55
    LINE_WIDTH: float = 1.8
    EXIT_STEP: float = 0.36
    EXIT_TRIES: int = 12

    def __init__(self, corridor_x: float, above_y: float, below_y: float) -> None:
        self._corridor = LaneSet(corridor_x, -self.LANE_STEP)
        self._above = LaneSet(above_y, self.LANE_STEP)
        self._below = LaneSet(below_y, -self.LANE_STEP)
        self._corridor_x = corridor_x
        self._exits: List[float] = []

    def above(self, ax, start, end, color: str) -> None:
        """Route over the top of the board into a top-half column."""
        self._route(ax, start, end, color, self._above)

    def below(self, ax, start, end, color: str) -> None:
        """Route under the board into a bottom-half column."""
        self._route(ax, start, end, color, self._below)

    def _route(self, ax, start, end, color: str, crossing: LaneSet) -> None:
        """Lay the four segments, allocating a lane for each direction.

        The corridor lane is chosen first so the crossing lane only has to
        clear the span the wire really occupies, not the whole corridor.
        """
        exit_y = self._exit_y(start[1])
        lane_x = self._corridor.assign(exit_y, crossing.base())
        cross_y = crossing.assign(lane_x, end[0])
        points = [
            start, (start[0], exit_y), (lane_x, exit_y), (lane_x, cross_y),
            (end[0], cross_y), end,
        ]
        owner = "lead to %s" % (Parts._key(end),)
        self._draw(ax, self._compress(points), color)
        Parts.record((end[0], cross_y), end, owner)
        Parts.pin_marker(ax, start, color)
        Parts.terminal(ax, end, color, owner)

    def _exit_y(self, pin_y: float) -> float:
        """Pick a free row for the run out of the header.

        Two pins in one header row sit at the same height, so without this
        their outbound segments would lie on top of each other.
        """
        for attempt in range(self.EXIT_TRIES):
            offset = self.EXIT_STEP * ((attempt + 1) // 2)
            candidate = pin_y + (offset if attempt % 2 else -offset)
            if self._is_free(candidate):
                self._exits.append(candidate)
                return candidate
        self._exits.append(pin_y)
        return pin_y

    def _is_free(self, candidate: float) -> bool:
        """True when no other wire leaves the header at this height."""
        return all(abs(candidate - used) >= self.EXIT_STEP - 0.01
                   for used in self._exits)

    def _compress(self, points):
        """Drop zero-length segments so the polyline has no doubled points."""
        kept = [points[0]]
        for point in points[1:]:
            if abs(point[0] - kept[-1][0]) > 1e-9 or \
                    abs(point[1] - kept[-1][1]) > 1e-9:
                kept.append(point)
        return kept

    def _draw(self, ax, points, color: str) -> None:
        """Stroke the polyline with rounded joins so corners read cleanly."""
        ax.plot(
            [x for x, _ in points], [y for _, y in points],
            color=color, linewidth=self.LINE_WIDTH, solid_joinstyle="round",
            solid_capstyle="round", zorder=8,
        )
