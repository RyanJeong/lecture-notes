#!/usr/bin/env python3
"""Lab 02 breadboard layout: two LEDs and the button that steps the states."""

# Standard library
from typing import Dict, List, Tuple

# Local
from board import Breadboard, Parts, PiHeader
from frame_bounds import Framing
from router import Router

# Third-party
from common import Frame


class Lab02Layout:
    """The same board as Lab 01 with one LED and one button removed."""

    OUT_PATH: str = "09/img/21-lab02-layout.png"
    BOARD_X: float = 9.0
    BOARD_Y: float = 2.5
    USED_PINS: Dict[int, str] = {
        1: "3V3", 9: "GND", 25: "GND", 11: "GPIO17", 13: "GPIO27", 16: "GPIO23",
    }
    LEDS: List[Tuple[int, int, int, int, str, str]] = [
        (4, 6, 7, 11, "RD", "Red"),
        (11, 13, 14, 13, "GN", "Green"),
    ]
    BUTTON: Tuple[int, int, int, int, str, str] = (20, 22, 24, 16, "OG", "SW")
    SERIES_R: str = "330R"
    PULLUP_R: str = "10k"

    def __init__(self) -> None:
        self._frame = Frame(self.OUT_PATH)
        self._ax = self._frame.axes()
        self._board = Breadboard(self.BOARD_X, self.BOARD_Y)
        self._header = PiHeader(0.0, 0.0)
        self._router = Router(self.BOARD_X - 0.8, self.BOARD_Y + 19.2,
                              self.BOARD_Y - 0.9)

    def render(self) -> str:
        """Draw the board, both LED branches and the single button."""
        Parts.reset()
        self._board.draw(self._ax)
        self._header.draw(self._ax, self.USED_PINS)
        self._power_rails()
        for spec in self.LEDS:
            self._led_branch(*spec)
        self._button_branch(*self.BUTTON)
        Parts.verify()
        self._frame.fit(Framing.bounds(self.BOARD_X))
        return self._frame.save()

    def _power_rails(self) -> None:
        """Feed both rails and bridge the two ground strips."""
        self._router.above(self._ax, self._header.pin(1),
                           self._board.rail(1, "top+"), Parts.color("RD"))
        self._router.above(self._ax, self._header.pin(9),
                           self._board.rail(2, "top-"), Parts.color("BK"))
        # A second header ground rather than a jumper bridging the two
        # rails, which would have to cross every component row to get there.
        self._router.below(self._ax, self._header.pin(25),
                           self._board.rail(1, "bottom-"), Parts.color("BK"))

    def _led_branch(
        self, signal: int, junction: int, cathode: int,
        pin: int, color: str, name: str,
    ) -> None:
        """GPIO -> 330R -> LED -> ground rail, all in the upper half."""
        self._router.above(self._ax, self._header.pin(pin),
                           self._board.hole(signal, "j"), Parts.color(color))
        Parts.resistor(self._ax, self._board.hole(signal, "g"),
                       self._board.hole(junction, "g"), self.SERIES_R)
        Parts.led(self._ax, self._board.hole(junction, "f"),
                  self._board.hole(cathode, "f"), color, name)
        Parts.stub(self._ax, self._board.hole(cathode, "j"),
                   self._board.rail(cathode, "top-"), "BK")

    def _button_branch(
        self, pullup: int, node: int, ret: int,
        pin: int, color: str, name: str,
    ) -> None:
        """3V3 rail -> 10k -> node -> switch -> ground rail."""
        Parts.stub(self._ax, self._board.rail(pullup, "top+"),
                   self._board.hole(pullup, "j"), "RD")
        Parts.resistor(self._ax, self._board.hole(pullup, "g"),
                       self._board.hole(node, "g"), self.PULLUP_R)
        Parts.button(self._ax, self._board.hole(node, "e"),
                     self._board.hole(ret, "e"), name)
        Parts.stub(self._ax, self._board.hole(ret, "a"),
                   self._board.rail(ret, "bottom-"), "BK")
        self._router.above(self._ax, self._header.pin(pin),
                           self._board.hole(node, "j"), Parts.color(color))


def main() -> None:
    print(Lab02Layout().render())


if __name__ == "__main__":
    main()
