#!/usr/bin/env python3
"""Lab 03 breadboard layout: the DHT11 module plugged straight into the board."""

# Standard library
from typing import Dict, List, Tuple

# Local
from board import Breadboard, Parts, PiHeader
from frame_bounds import Framing
from router import Router

# Third-party
from common import Frame


class Lab03Layout:
    """Three jumpers and one module: the whole of Lab 03."""

    OUT_PATH: str = "10/img/16-lab03-layout.png"
    BOARD_X: float = 9.0
    BOARD_Y: float = 2.5
    USED_PINS: Dict[int, str] = {1: "3V3", 7: "GPIO4", 9: "GND"}
    MODULE_PINS: List[str] = ["VCC", "DATA", "GND"]
    # (module column, header pin, wire colour)
    LINKS: List[Tuple[int, int, str]] = [
        (12, 1, "RD"),
        (14, 7, "YE"),
        (16, 9, "BK"),
    ]
    NOTE: str = "3-pin module: the pull-up on DATA is already fitted"

    def __init__(self) -> None:
        self._frame = Frame(self.OUT_PATH)
        self._ax = self._frame.axes()
        self._board = Breadboard(self.BOARD_X, self.BOARD_Y)
        self._header = PiHeader(0.0, 0.0)
        self._router = Router(self.BOARD_X - 0.8, self.BOARD_Y + 19.2,
                              self.BOARD_Y - 0.9)

    def render(self) -> str:
        """Draw the board, seat the module and run the three jumpers."""
        Parts.reset()
        self._board.draw(self._ax)
        self._header.draw(self._ax, self.USED_PINS)
        self._module()
        for column, pin, color in self.LINKS:
            self._router.below(self._ax, self._header.pin(pin),
                               self._board.hole(column, "a"),
                               Parts.color(color))
        self._caption()
        Parts.verify()
        self._frame.fit(Framing.bounds(self.BOARD_X))
        return self._frame.save()

    def _module(self) -> None:
        """The DHT11 seated in row e, its body overhanging the channel."""
        legs = [self._board.hole(column, "e") for column, _, _ in self.LINKS]
        Parts.module(self._ax, legs, "DHT11", self.MODULE_PINS)

    def _caption(self) -> None:
        """A one-line reminder above the board."""
        self._ax.text(
            self.BOARD_X + Breadboard.WIDTH / 2.0, self.BOARD_Y + 19.6,
            self.NOTE, ha="center", va="center", fontsize=7, color="#222222",
        )


def main() -> None:
    print(Lab03Layout().render())


if __name__ == "__main__":
    main()
