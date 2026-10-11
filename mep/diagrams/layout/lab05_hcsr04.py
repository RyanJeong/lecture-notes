#!/usr/bin/env python3
"""Lab 05 breadboard layout: HC-SR04, the 1k/2k echo divider and a buzzer."""

# Standard library
from typing import Dict, List, Tuple

# Local
from board import Breadboard, Parts, PiHeader
from frame_bounds import Framing
from router import Router

# Third-party
from common import Frame


class Lab05Layout:
    """The only 5 V part in the course, so the echo line needs dividing."""

    OUT_PATH: str = "10/img/18-lab05-layout.png"
    BOARD_X: float = 9.0
    BOARD_Y: float = 2.5
    USED_PINS: Dict[int, str] = {
        2: "5V", 6: "GND", 12: "GPIO18", 16: "GPIO23", 18: "GPIO24",
    }
    SONAR_COLUMNS: List[int] = [3, 4, 5, 6]
    SONAR_PINS: List[str] = ["VCC", "TRIG", "ECHO", "GND"]
    # (module column, header pin, colour) for the lines needing no divider
    DIRECT: List[Tuple[int, int, str]] = [(3, 2, "RD"), (4, 16, "YE")]
    ECHO_COLUMN: int = 5
    GND_COLUMN: int = 6
    DIVIDER: Tuple[int, int] = (9, 12)
    BUZZER_COLUMNS: Tuple[int, int] = (20, 22)
    TOP_R: str = "1k"
    BOTTOM_R: str = "2k"
    NOTE: str = "ECHO is 5 V: it reaches GPIO24 only through the 1k/2k divider"

    def __init__(self) -> None:
        self._frame = Frame(self.OUT_PATH)
        self._ax = self._frame.axes()
        self._board = Breadboard(self.BOARD_X, self.BOARD_Y)
        self._header = PiHeader(0.0, 0.0)
        self._router = Router(self.BOARD_X - 0.8, self.BOARD_Y + 19.2,
                              self.BOARD_Y - 0.9)

    def render(self) -> str:
        """Draw the sonar, the divider protecting the GPIO, and the buzzer."""
        Parts.reset()
        self._board.draw(self._ax)
        self._header.draw(self._ax, self.USED_PINS)
        self._ground()
        self._sonar()
        self._echo_divider()
        self._buzzer()
        self._caption()
        Parts.verify()
        self._frame.fit(Framing.bounds(self.BOARD_X))
        return self._frame.save()

    def _ground(self) -> None:
        """Only ground is shared here; 5 V goes straight to the module."""
        self._router.below(self._ax, self._header.pin(6),
                           self._board.rail(1, "bottom-"), Parts.color("BK"))

    def _sonar(self) -> None:
        """Seat the module and run its two direct lines."""
        legs = [self._board.hole(column, "e") for column in self.SONAR_COLUMNS]
        Parts.module(self._ax, legs, "HC-SR04", self.SONAR_PINS)
        for column, pin, color in self.DIRECT:
            self._router.below(self._ax, self._header.pin(pin),
                               self._board.hole(column, "a"),
                               Parts.color(color))
        Parts.stub(self._ax, self._board.hole(self.GND_COLUMN, "a"),
                   self._board.rail(self.GND_COLUMN, "bottom-"), "BK")

    def _echo_divider(self) -> None:
        """ECHO -> 1k -> node -> 2k -> ground, with GPIO24 on the node."""
        node, foot = self.DIVIDER
        Parts.resistor(self._ax, self._board.hole(self.ECHO_COLUMN, "c"),
                       self._board.hole(node, "c"), self.TOP_R)
        Parts.resistor(self._ax, self._board.hole(node, "b"),
                       self._board.hole(foot, "b"), self.BOTTOM_R)
        # Row a, so the stub does not pass through the 2k leg in row b.
        Parts.stub(self._ax, self._board.hole(foot, "a"),
                   self._board.rail(foot, "bottom-"), "BK")
        self._router.below(self._ax, self._header.pin(18),
                           self._board.hole(node, "a"), Parts.color("GN"))

    def _buzzer(self) -> None:
        """A separate GPIO drives the warning buzzer."""
        positive, negative = self.BUZZER_COLUMNS
        legs = [self._board.hole(positive, "e"),
                self._board.hole(negative, "e")]
        Parts.module(self._ax, legs, "Buzzer", ["+", "-"], height=2.6)
        self._router.below(self._ax, self._header.pin(12),
                           self._board.hole(positive, "a"), Parts.color("OG"))
        Parts.stub(self._ax, self._board.hole(negative, "a"),
                   self._board.rail(negative, "bottom-"), "BK")

    def _caption(self) -> None:
        """The warning that matters most in this lab."""
        self._ax.text(
            self.BOARD_X + Breadboard.WIDTH / 2.0, self.BOARD_Y + 19.6,
            self.NOTE, ha="center", va="center", fontsize=7, color="#c0392b",
        )


def main() -> None:
    print(Lab05Layout().render())


if __name__ == "__main__":
    main()
