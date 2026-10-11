#!/usr/bin/env python3
"""Lab 01 breadboard layout: three LED branches and two pulled-up buttons."""

# Standard library
from typing import Dict, List, Tuple

# Local
from board import Breadboard, Parts, PiHeader
from router import Router
from frame_bounds import Framing

# Third-party
from common import Frame


class Lab01Layout:
    """Places the LED and button sections on a half-size breadboard."""

    OUT_PATH: str = "09/img/20-lab01-layout.png"
    BOARD_X: float = 9.0
    BOARD_Y: float = 2.5
    USED_PINS: Dict[int, str] = {
        1: "3V3", 9: "GND", 25: "GND", 11: "GPIO17", 13: "GPIO27",
        15: "GPIO22", 16: "GPIO23", 18: "GPIO24",
    }
    # (signal column, junction column, cathode column, pin, colour, name)
    LEDS: List[Tuple[int, int, int, int, str, str]] = [
        (3, 5, 6, 11, "YE", "LED 1"),
        (8, 10, 11, 13, "GN", "LED 2"),
        (13, 15, 16, 15, "BU", "LED 3"),
    ]
    # (pull-up column, node column, return column, pin, colour, name)
    BUTTONS: List[Tuple[int, int, int, int, str, str]] = [
        (19, 21, 23, 16, "OG", "SW 1"),
        (25, 27, 29, 18, "VT", "SW 2"),
    ]
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
        """Draw the board, the parts, every jumper, then write the PNG."""
        Parts.reset()
        self._board.draw(self._ax)
        self._header.draw(self._ax, self.USED_PINS)
        self._power_rails()
        for spec in self.LEDS:
            self._led_branch(*spec)
        for spec in self.BUTTONS:
            self._button_branch(*spec)
        Parts.verify()
        self._frame.fit(Framing.bounds(self.BOARD_X))
        return self._frame.save()

    def _power_rails(self) -> None:
        """Feed the two rails and bridge the separate ground strips."""
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
        """3V3 rail -> 10k -> node -> switch -> ground rail, lower half."""
        Parts.stub(self._ax, self._board.rail(pullup, "top+"),
                   self._board.hole(pullup, "j"), "RD")
        Parts.resistor(self._ax, self._board.hole(pullup, "g"),
                       self._board.hole(node, "g"), self.PULLUP_R)
        Parts.button(self._ax, self._board.hole(node, "e"),
                     self._board.hole(ret, "e"), name)
        Parts.stub(self._ax, self._board.hole(ret, "a"),
                   self._board.rail(ret, "bottom-"), "BK")
        # The switch straddles the channel, so its two left legs land in rows
        # e and f of the node column and short the a-e net to the f-j net.
        # That is what carries the press up to the pull-up and the GPIO tap.
        # It only holds if the switch is turned the right way round: rotated
        # 90 degrees, the shorted pairs run along the channel instead and the
        # press never reaches the pin.
        self._router.above(self._ax, self._header.pin(pin),
                           self._board.hole(node, "j"), Parts.color(color))


def main() -> None:
    print(Lab01Layout().render())


if __name__ == "__main__":
    main()
