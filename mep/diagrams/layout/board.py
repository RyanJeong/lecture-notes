#!/usr/bin/env python3
"""Fritzing-style parts: a half-size breadboard, the Pi header and components.

Coordinates are in hole pitches. The breadboard occupies x in [0, 30] and
y in [0, 17]; the Pi header sits to its left. Laying the two out side by
side gives roughly the canvas aspect, so a layout fills the frame.
"""

# Standard library
from typing import Dict, List, Tuple

# Third-party
from matplotlib.patches import Circle, FancyBboxPatch, Rectangle


class Palette:
    """Colours shared by every layout."""

    BOARD: str = "#f2f0e6"
    BOARD_EDGE: str = "#c9c4b0"
    CHANNEL: str = "#e2ded0"
    HOLE: str = "#9a9584"
    RAIL_POS: str = "#c0392b"
    RAIL_NEG: str = "#2c3e50"
    RAIL_MARK_POS: str = "#d4796f"
    RAIL_MARK_NEG: str = "#7f93ad"
    LEG: str = "#5d6d6e"
    PI_BOARD: str = "#0b6623"
    PI_HEADER: str = "#2c3e50"
    PIN_IDLE: str = "#7f8c8d"
    PIN_USED: str = "#f1c40f"
    RESISTOR: str = "#d8c9a3"
    MODULE: str = "#34495e"
    TEXT: str = "#222222"
    WIRE: Dict[str, str] = {
        "RD": "#c0392b", "BK": "#2c3e50", "YE": "#f1c40f", "GN": "#27ae60",
        "BU": "#2980b9", "OG": "#e67e22", "VT": "#8e44ad", "WH": "#bdc3c7",
        "BR": "#795548", "GY": "#7f8c8d",
    }


class Breadboard:
    """A 30-column half-size breadboard with two power rail pairs."""

    COLUMNS: int = 30
    WIDTH: float = 30.0
    HEIGHT: float = 18.0
    ROW_Y: Dict[str, float] = {
        "a": 4.0, "b": 5.0, "c": 6.0, "d": 7.0, "e": 8.0,
        "f": 10.0, "g": 11.0, "h": 12.0, "i": 13.0, "j": 14.0,
    }
    # Both rail groups sit two rows clear of the matrix, so the board reads
    # the same way at the top and the bottom.
    RAIL_Y: Dict[str, float] = {
        "bottom-": 1.0, "bottom+": 2.0, "top-": 16.0, "top+": 17.0,
    }
    HOLE_R: float = 0.17
    # Rows e and f straddle the centre channel; a tactile switch bridges it.
    CHANNEL_SPAN: float = 2.0

    def __init__(self, origin_x: float = 0.0, origin_y: float = 0.0) -> None:
        self._x0 = origin_x
        self._y0 = origin_y

    def hole(self, column: int, row: str) -> Tuple[float, float]:
        """Centre of the tie point at (column 1-30, row a-j)."""
        return (self._x0 + column - 0.5, self._y0 + self.ROW_Y[row])

    def rail(self, column: int, name: str) -> Tuple[float, float]:
        """Centre of a power rail hole, e.g. name='bottom-'."""
        return (self._x0 + column - 0.5, self._y0 + self.RAIL_Y[name])

    def draw(self, ax) -> None:
        """Render the board body, the channel, every hole and the rails."""
        self._body(ax)
        self._channel(ax)
        self._rail_lines(ax)
        self._holes(ax)
        self._labels(ax)

    def _labels(self, ax) -> None:
        """Column numbers and row letters, as printed on a real board.

        Without them a diagram cannot say which hole a lead belongs in, which
        is the difference between a picture and a build instruction.
        """
        for column in range(1, self.COLUMNS + 1):
            if column % 5 != 0 and column != 1:
                continue
            x = self._x0 + column - 0.5
            for y in (self._y0 + 14.9, self._y0 + 3.1):
                ax.text(x, y, str(column), ha="center", va="center",
                        fontsize=5, color="#8a8574", zorder=4)
        for row, y in self.ROW_Y.items():
            for x in (self._x0 + 0.15, self._x0 + self.WIDTH - 0.15):
                ax.text(x, self._y0 + y, row, ha="center", va="center",
                        fontsize=5, color="#8a8574", zorder=4)

    def _body(self, ax) -> None:
        """The plastic slab."""
        ax.add_patch(
            FancyBboxPatch(
                (self._x0 + 0.2, self._y0 + 0.2),
                self.WIDTH - 0.4, self.HEIGHT - 0.4,
                boxstyle="round,pad=0.2", linewidth=1.0,
                facecolor=Palette.BOARD, edgecolor=Palette.BOARD_EDGE,
            )
        )

    def _channel(self, ax) -> None:
        """The centre trough that splits the two five-hole halves."""
        ax.add_patch(
            Rectangle(
                (self._x0 + 0.3, self._y0 + 8.5), self.WIDTH - 0.6, 1.0,
                facecolor=Palette.CHANNEL, edgecolor="none",
            )
        )

    def _rail_lines(self, ax) -> None:
        """The red and blue stripes marking the four power rails."""
        for name, offset, color in (
            ("bottom-", -0.55, Palette.RAIL_MARK_NEG),
            ("bottom+", 0.55, Palette.RAIL_MARK_POS),
            ("top-", -0.55, Palette.RAIL_MARK_NEG),
            ("top+", 0.55, Palette.RAIL_MARK_POS),
        ):
            y = self._y0 + self.RAIL_Y[name] + offset
            ax.plot(
                [self._x0 + 0.5, self._x0 + self.WIDTH - 0.5], [y, y],
                color=color, linewidth=1.0, zorder=1,
            )

    def _holes(self, ax) -> None:
        """Every tie point, drawn once for the matrix and once per rail."""
        for column in range(1, self.COLUMNS + 1):
            for row in self.ROW_Y:
                self._hole(ax, self.hole(column, row))
            for name in self.RAIL_Y:
                self._hole(ax, self.rail(column, name))

    def _hole(self, ax, center: Tuple[float, float]) -> None:
        """One tie point."""
        ax.add_patch(
            Circle(center, self.HOLE_R, facecolor=Palette.HOLE,
                   edgecolor="none", zorder=3)
        )


class PiHeader:
    """The Pi's 40-pin header drawn vertically, beside the breadboard."""

    ROWS: int = 20
    WIDTH: float = 2.0
    LABEL_SIZE: int = 6

    def __init__(self, origin_x: float, origin_y: float) -> None:
        self._x0 = origin_x
        self._y0 = origin_y

    def pin(self, number: int) -> Tuple[float, float]:
        """Centre of a physical header pin, numbered 1-40 as on the board."""
        row = (number - 1) // 2
        column = (number - 1) % 2
        return (self._x0 + 0.5 + column, self._y0 + self.ROWS - 0.5 - row)

    def draw(self, ax, used: Dict[int, str]) -> None:
        """Render the board stub, the header and highlight the used pins."""
        self._board(ax)
        for number in range(1, 2 * self.ROWS + 1):
            self._pin(ax, number, used.get(number))
        self._labels(ax, used)

    def _board(self, ax) -> None:
        """A green stub standing in for the Pi PCB."""
        ax.add_patch(
            FancyBboxPatch(
                (self._x0 - 1.6, self._y0 - 0.4), self.WIDTH + 2.0,
                self.ROWS + 0.8, boxstyle="round,pad=0.2", linewidth=1.0,
                facecolor=Palette.PI_BOARD, edgecolor="#084d1a",
            )
        )
        ax.text(
            self._x0 - 0.9, self._y0 + self.ROWS / 2.0, "Raspberry Pi 4",
            rotation=90, ha="center", va="center", fontsize=8, color="#ffffff",
        )

    def _pin(self, ax, number: int, label: str) -> None:
        """One header pin, labelled only when the lab uses it."""
        x, y = self.pin(number)
        color = Palette.PIN_USED if label else Palette.PIN_IDLE
        ax.add_patch(
            Rectangle((x - 0.3, y - 0.3), 0.6, 0.6, facecolor=color,
                      edgecolor="#1a1a1a", linewidth=0.4, zorder=4)
        )

    def _labels(self, ax, used: Dict[int, str]) -> None:
        """Caption every used pin on the left, one line per header row.

        Both pins of a row share a line, so a label can never land in the
        corridor where the jumpers run.
        """
        rows: Dict[int, List[Tuple[int, str]]] = {}
        for number, label in used.items():
            rows.setdefault((number - 1) // 2, []).append((number, label))
        for row, entries in rows.items():
            text = " / ".join("%s (%d)" % (name, number)
                              for number, name in sorted(entries))
            ax.text(self._x0 - 1.9, self._y0 + self.ROWS - 0.5 - row, text,
                    ha="right", va="center", fontsize=self.LABEL_SIZE,
                    color=Palette.TEXT, zorder=5)


class Parts:
    """Through-hole components drawn between two tie points."""

    @staticmethod
    def color(name: str) -> str:
        """Resolve a wire colour code to its hex value."""
        return Palette.WIRE[name]

    TERMINAL_R: float = Breadboard.HOLE_R
    CLEARANCE: float = 0.3
    _claimed: Dict[Tuple[float, float], str] = {}
    _segments: List[Tuple[Tuple[float, float], Tuple[float, float], str]] = []

    @staticmethod
    def reset() -> None:
        """Forget every claimed hole and segment; called once per layout."""
        Parts._claimed = {}
        Parts._segments = []

    @staticmethod
    def record(start, end, owner: str) -> None:
        """Remember a run that lies on the board, for the clearance check."""
        Parts._segments.append((start, end, owner))

    @staticmethod
    def verify() -> None:
        """Refuse any run that passes through a hole it does not terminate in.

        A lead crossing an occupied hole would touch that lead on a real
        board, and reads as a connection that the circuit does not have.
        """
        for start, end, owner in Parts._segments:
            ends = (Parts._key(start), Parts._key(end))
            for point, holder in Parts._claimed.items():
                if point in ends or holder == owner:
                    continue
                if Parts._touches(point, start, end):
                    raise ValueError(
                        "%s runs through the hole at %s held by %s"
                        % (owner, point, holder)
                    )

    @staticmethod
    def _key(point) -> Tuple[float, float]:
        """Canonical hole coordinate."""
        return (round(point[0], 2), round(point[1], 2))

    @staticmethod
    def _touches(point, start, end) -> bool:
        """True when the point lies within clearance of the segment."""
        px, py = point
        dx, dy = end[0] - start[0], end[1] - start[1]
        length = (dx * dx + dy * dy) ** 0.5
        if length < 1e-9:
            return False
        t = ((px - start[0]) * dx + (py - start[1]) * dy) / (length * length)
        if t <= 0.0 or t >= 1.0:
            return False
        near = (start[0] + t * dx, start[1] + t * dy)
        gap = ((px - near[0]) ** 2 + (py - near[1]) ** 2) ** 0.5
        return gap < Parts.CLEARANCE

    @staticmethod
    def claim(point, owner: str) -> None:
        """Record that something occupies this hole.

        A breadboard hole takes exactly one lead, so a second claim is a
        physically impossible layout and is refused rather than drawn.
        """
        key = Parts._key(point)
        held = Parts._claimed.get(key)
        if held is not None:
            raise ValueError(
                "hole %s already taken by %s, cannot also hold %s"
                % (key, held, owner)
            )
        Parts._claimed[key] = owner

    @staticmethod
    def terminal(ax, point, color: str, owner: str = "wire") -> None:
        """Mark the hole a lead occupies, and claim it."""
        Parts.claim(point, owner)
        ax.add_patch(
            Circle(point, Parts.TERMINAL_R,
                   facecolor=Palette.WIRE.get(color, color),
                   edgecolor="none", zorder=9)
        )

    @staticmethod
    def pin_marker(ax, point, color: str) -> None:
        """The same marker on the header side, where no hole is claimed."""
        ax.add_patch(
            Circle(point, Parts.TERMINAL_R,
                   facecolor=Palette.WIRE.get(color, color),
                   edgecolor="none", zorder=9)
        )

    @staticmethod
    def stub(ax, start, end, color: str) -> None:
        """A short straight link between two points on the board itself."""
        ax.plot([start[0], end[0]], [start[1], end[1]],
                color=Palette.WIRE[color], linewidth=1.8,
                solid_capstyle="round", zorder=8)
        owner = "jumper %s" % (Parts._key(start),)
        Parts.record(start, end, owner)
        Parts.terminal(ax, start, color, owner)
        Parts.terminal(ax, end, color, owner)

    @staticmethod
    def resistor(ax, start, end, label: str, label_below: bool = False) -> None:
        """A resistor body centred between its two tie points.

        Stacked dividers leave no room above the body, so the caption can be
        dropped under it instead.
        """
        mid = ((start[0] + end[0]) / 2.0, (start[1] + end[1]) / 2.0)
        ax.plot([start[0], end[0]], [start[1], end[1]], color="#8a8a8a",
                linewidth=1.2, zorder=5)
        ax.add_patch(
            Rectangle((mid[0] - 0.45, mid[1] - 0.28), 0.9, 0.56,
                      facecolor=Palette.RESISTOR, edgecolor="#8a7d5a",
                      linewidth=0.5, zorder=6)
        )
        offset, valign = (-0.62, "top") if label_below else (0.62, "bottom")
        ax.text(mid[0], mid[1] + offset, label, ha="center", va=valign,
                fontsize=6, color=Palette.TEXT, zorder=7)
        Parts.record(start, end, label)
        Parts.terminal(ax, start, Palette.LEG, label)
        Parts.terminal(ax, end, Palette.LEG, label)

    @staticmethod
    def led(ax, anode, cathode, color: str, label: str) -> None:
        """An LED as a coloured dome with its two legs in the board."""
        mid = ((anode[0] + cathode[0]) / 2.0, (anode[1] + cathode[1]) / 2.0)
        ax.plot([anode[0], cathode[0]], [anode[1], cathode[1]],
                color="#8a8a8a", linewidth=1.2, zorder=5)
        ax.add_patch(
            Circle(mid, 0.42, facecolor=Palette.WIRE[color],
                   edgecolor="#5a1a1a", linewidth=0.5, zorder=6)
        )
        ax.text(mid[0], mid[1] + 0.68, label, ha="center", va="bottom",
                fontsize=6, color=Palette.TEXT, zorder=7)
        Parts.record(anode, cathode, label)
        Parts.terminal(ax, anode, Palette.LEG, label)
        Parts.terminal(ax, cathode, Palette.LEG, label)
        Parts._polarity(ax, anode, cathode)

    @staticmethod
    def _polarity(ax, anode, cathode) -> None:
        """Caption the two legs of a polarised part so it cannot be reversed."""
        for point, sign in ((anode, "+"), (cathode, "-")):
            ax.text(point[0], point[1] - 0.62, sign, ha="center", va="center",
                    fontsize=8, color=Palette.TEXT, zorder=8)

    @staticmethod
    def button(ax, left_leg, right_leg, label: str) -> None:
        """A tactile switch straddling the channel between two column pairs.

        Both legs sit in row e; the body reaches up over the channel into
        row f, which is how the part actually lands on the board.
        """
        width = right_leg[0] - left_leg[0]
        ax.add_patch(
            Rectangle((left_leg[0] - 0.4, left_leg[1] - 0.4), width + 0.8, 2.8,
                      facecolor="#95a5a6", edgecolor="#5d6d6e",
                      linewidth=0.6, zorder=6)
        )
        ax.text(left_leg[0] + width / 2.0, left_leg[1] + 2.6, label,
                ha="center", va="bottom", fontsize=6, color=Palette.TEXT,
                zorder=7)
        for leg in (left_leg, right_leg):
            for row in (leg, (leg[0], leg[1] + Breadboard.CHANNEL_SPAN)):
                Parts.terminal(ax, row, Palette.LEG, label)

    @staticmethod
    def module(ax, legs, label: str, pin_names: List[str],
               height: float = 3.4) -> None:
        """A sensor module standing on its legs, body overhanging the board.

        `legs` are the tie points the pins actually occupy; the body is drawn
        above them so it never hides the holes a student has to reach.
        """
        pad = 0.7
        x0, x1 = legs[0][0] - pad, legs[-1][0] + pad
        y0 = legs[0][1] + 0.6
        Parts._module_legs(ax, legs, y0, label)
        ax.add_patch(
            FancyBboxPatch(
                (x0, y0), x1 - x0, height, boxstyle="round,pad=0.12",
                facecolor=Palette.MODULE, edgecolor="#1b2631",
                linewidth=0.8, zorder=6,
            )
        )
        ax.text((x0 + x1) / 2.0, y0 + height - 0.55, label, ha="center",
                va="center", fontsize=7, color="#ffffff", zorder=7)
        Parts._module_pins(ax, legs, y0 + 0.28, pin_names)

    @staticmethod
    def _module_legs(ax, legs, body_y: float, label: str = "module") -> None:
        """Short stubs joining each pin to the body above it."""
        for x, y in legs:
            ax.plot([x, x], [y, body_y], color="#95a5a6", linewidth=1.4,
                    zorder=5)
            Parts.terminal(ax, (x, y), Palette.LEG, label)

    @staticmethod
    def _module_pins(ax, legs, y: float, names: List[str]) -> None:
        """Print each pin name inside the body, right above its own leg."""
        for (x, _), name in zip(legs, names):
            ax.text(x, y, name, ha="center", va="bottom", fontsize=5.5,
                    color="#ecf0f1", zorder=7, rotation=90)

    @staticmethod
    def dip(ax, board, first_column: int, label: str,
            bottom_names: List[str], top_names: List[str]) -> None:
        """A DIP package straddling the centre channel.

        Pin names are printed in the free rows either side of the body, since
        the package itself hides rows e and f of the columns it occupies.
        """
        last = first_column + len(bottom_names) - 1
        x0 = board.hole(first_column, "e")[0] - 0.5
        x1 = board.hole(last, "e")[0] + 0.5
        y0, y1 = board.hole(1, "e")[1], board.hole(1, "f")[1]
        ax.add_patch(
            Rectangle((x0, y0), x1 - x0, y1 - y0, facecolor="#1c2833",
                      edgecolor="#0b0f12", linewidth=0.8, zorder=6)
        )
        ax.add_patch(
            Circle((x0 + 0.45, (y0 + y1) / 2.0), 0.2, facecolor="#566573",
                   edgecolor="none", zorder=7)
        )
        ax.text((x0 + x1) / 2.0, (y0 + y1) / 2.0, label, ha="center",
                va="center", fontsize=6.5, color="#ffffff", zorder=7)
        for offset in range(len(bottom_names)):
            for row in ("e", "f"):
                Parts.claim(board.hole(first_column + offset, row), label)
        Parts._dip_names(ax, board, first_column, bottom_names, "c", "top")
        Parts._dip_names(ax, board, first_column, top_names, "g", "bottom")

    @staticmethod
    def _dip_names(ax, board, first_column: int, names: List[str],
                   row: str, valign: str) -> None:
        """Caption one side of a DIP, just outside the package outline."""
        for offset, name in enumerate(names):
            x, y = board.hole(first_column + offset, row)
            ax.text(x, y, name, ha="center", va=valign, fontsize=5,
                    color=Palette.TEXT, zorder=7, rotation=90)
