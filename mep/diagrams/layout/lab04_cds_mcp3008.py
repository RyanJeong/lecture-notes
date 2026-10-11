#!/usr/bin/env python3
"""Lab 04 breadboard layout: CdS divider, MCP3008 on SPI0 and one LED."""

# Standard library
from typing import Dict, List, Tuple

# Local
from board import Breadboard, Parts, PiHeader
from frame_bounds import Framing
from router import Router

# Third-party
from common import Frame


class Lab04Layout:
    """The ADC straddles the channel; the divider feeds its first channel."""

    OUT_PATH: str = "10/img/17-lab04-layout.png"
    BOARD_X: float = 9.0
    BOARD_Y: float = 2.5
    USED_PINS: Dict[int, str] = {
        1: "3V3", 9: "GND", 11: "GPIO17", 17: "3V3", 19: "MOSI",
        21: "MISO", 23: "SCLK", 24: "CE0", 25: "GND",
    }
    ADC_COLUMN: int = 11
    ADC_BOTTOM: List[str] = ["CH0", "CH1", "CH2", "CH3",
                             "CH4", "CH5", "CH6", "CH7"]
    ADC_TOP: List[str] = ["VDD", "VREF", "AGND", "CLK",
                          "DOUT", "DIN", "CS", "DGND"]
    # (column offset inside the package, header pin, colour)
    SPI_LINKS: List[Tuple[int, int, str]] = [
        (3, 23, "YE"), (4, 21, "GN"), (5, 19, "BU"), (6, 24, "VT"),
    ]
    # (column offset, rail, colour)
    ADC_POWER: List[Tuple[int, str, str]] = [
        (0, "top+", "RD"), (1, "top+", "RD"),
        (2, "top-", "BK"), (7, "top-", "BK"),
    ]
    CDS_COLUMNS: Tuple[int, int, int] = (2, 5, 8)
    LED_COLUMNS: Tuple[int, int, int] = (22, 24, 25)
    SERIES_R: str = "330R"
    FIXED_R: str = "10k"

    def __init__(self) -> None:
        self._frame = Frame(self.OUT_PATH)
        self._ax = self._frame.axes()
        self._board = Breadboard(self.BOARD_X, self.BOARD_Y)
        self._header = PiHeader(0.0, 0.0)
        self._router = Router(self.BOARD_X - 0.8, self.BOARD_Y + 19.2,
                              self.BOARD_Y - 0.9)

    def render(self) -> str:
        """Draw the board, the ADC, the divider and the indicator LED."""
        Parts.reset()
        self._board.draw(self._ax)
        self._header.draw(self._ax, self.USED_PINS)
        self._power_rails()
        Parts.dip(self._ax, self._board, self.ADC_COLUMN, "MCP3008",
                  self.ADC_BOTTOM, self.ADC_TOP)
        self._adc_links()
        self._divider()
        self._led_branch()
        Parts.verify()
        self._frame.fit(Framing.bounds(self.BOARD_X))
        return self._frame.save()

    def _power_rails(self) -> None:
        """Feed both rails from the header and bridge them end to end."""
        self._router.above(self._ax, self._header.pin(1),
                           self._board.rail(1, "top+"), Parts.color("RD"))
        self._router.above(self._ax, self._header.pin(9),
                           self._board.rail(2, "top-"), Parts.color("BK"))
        # Fed directly rather than bridged across the board: a rail-to-rail
        # jumper would have to cross every component row.
        # Column 4: reaching the + rail means passing the - rail hole in the
        # same column, so it must not be the one carrying the ground feed.
        self._router.below(self._ax, self._header.pin(17),
                           self._board.rail(4, "bottom+"), Parts.color("RD"))
        self._router.below(self._ax, self._header.pin(25),
                           self._board.rail(1, "bottom-"), Parts.color("BK"))

    def _adc_links(self) -> None:
        """Rail stubs for power, routed jumpers for the four SPI lines."""
        for offset, rail, color in self.ADC_POWER:
            column = self.ADC_COLUMN + offset
            Parts.stub(self._ax, self._board.hole(column, "j"),
                       self._board.rail(column, rail), color)
        for offset, pin, color in self.SPI_LINKS:
            column = self.ADC_COLUMN + offset
            self._router.above(self._ax, self._header.pin(pin),
                               self._board.hole(column, "j"),
                               Parts.color(color))

    def _divider(self) -> None:
        """3V3 rail -> CdS -> node -> 10k -> ground, then node to CH0.

        The rows read bottom upwards in build order: the 3.3 V feed sits
        directly under the CdS leg, the 10k goes in the row above the CdS,
        and only then does the CH0 wire leave from the row above that. All
        three of those leads land in the node column, which is what makes
        them one electrical point. Put the CH0 wire in a different column
        and the 10k is out of circuit: no path to ground, so no current, no
        voltage drop, and CH0 floats to 3.3 V.
        """
        top, node, bottom = self.CDS_COLUMNS
        # Row a, not row b: the CdS leg sits in row b of this column and a
        # hole takes one lead only.
        Parts.stub(self._ax, self._board.rail(top, "bottom+"),
                   self._board.hole(top, "a"), "RD")
        Parts.resistor(self._ax, self._board.hole(top, "b"),
                       self._board.hole(node, "b"), "CdS", label_below=True)
        Parts.resistor(self._ax, self._board.hole(node, "c"),
                       self._board.hole(bottom, "c"), self.FIXED_R,
                       label_below=True)
        # Row a, the row nearest the rail: a stub from row c would run
        # straight through the resistor leg on its way down.
        Parts.stub(self._ax, self._board.hole(bottom, "a"),
                   self._board.rail(bottom, "bottom-"), "BK")
        Parts.stub(self._ax, self._board.hole(node, "d"),
                   self._board.hole(self.ADC_COLUMN, "d"), "BR")

    def _led_branch(self) -> None:
        """Stage 1 of the lab: one LED straight off a GPIO."""
        signal, junction, cathode = self.LED_COLUMNS
        self._router.above(self._ax, self._header.pin(11),
                           self._board.hole(signal, "j"), Parts.color("OG"))
        Parts.resistor(self._ax, self._board.hole(signal, "g"),
                       self._board.hole(junction, "g"), self.SERIES_R)
        Parts.led(self._ax, self._board.hole(junction, "f"),
                  self._board.hole(cathode, "f"), "OG", "LED")
        Parts.stub(self._ax, self._board.hole(cathode, "j"),
                   self._board.rail(cathode, "top-"), "BK")


def main() -> None:
    print(Lab04Layout().render())


if __name__ == "__main__":
    main()
