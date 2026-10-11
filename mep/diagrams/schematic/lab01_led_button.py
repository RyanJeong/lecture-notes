#!/usr/bin/env python3
"""Lab 01 schematic: three LEDs on 330 ohm limiters, two pulled-up buttons."""

# Standard library
from typing import List, Tuple

# Third-party
import schemdraw.elements as elm

# Local
from common import Sheet


class Lab01Schematic:
    """Draws the Lab 01 circuit as one row per GPIO branch."""

    OUT_PATH: str = "09/img/04-lab01-circuit.png"
    LED_PINS: List[Tuple[str, str, str]] = [
        ("GPIO17", "11", "LED 1"),
        ("GPIO27", "13", "LED 2"),
        ("GPIO22", "15", "LED 3"),
    ]
    BUTTON_PINS: List[Tuple[str, str, str]] = [
        ("GPIO23", "16", "SW 1"),
        ("GPIO24", "18", "SW 2"),
    ]
    SERIES_R: str = "330 $\\Omega$"
    PULLUP_R: str = "10 k$\\Omega$"
    RAIL: str = "3.3 V"
    LED_ROW_GAP: float = 2.4
    BUTTON_ROW_GAP: float = 4.2
    BUTTON_COLUMN_X: float = 11.5

    def __init__(self) -> None:
        self._sheet = Sheet(self.OUT_PATH)
        self._d = self._sheet.drawing()
        self._y = 0.0

    def render(self) -> str:
        """Draw the LED column, then the button column beside it."""
        for bcm, header, name in self.LED_PINS:
            self._led_row(bcm, header, name)
        self._y = 0.0
        for bcm, header, name in self.BUTTON_PINS:
            self._button_row(bcm, header, name)
        return self._sheet.save()

    def _led_row(self, bcm: str, header: str, name: str) -> None:
        """GPIO -> 330 ohm -> LED -> GND, drawn left to right."""
        self._d.here = (0, self._y)
        self._d += self._source_label(bcm, header)
        self._d += elm.Resistor().right().label(self.SERIES_R)
        self._d += elm.LED().right().label(name)
        self._d += elm.Line().right().length(0.8)
        self._d += elm.Ground()
        self._y -= self.LED_ROW_GAP

    def _button_row(self, bcm: str, header: str, name: str) -> None:
        """3.3V -> 10k -> node -> button -> GND, with the node read by the GPIO."""
        self._d.here = (self.BUTTON_COLUMN_X, self._y)
        self._d += elm.Vdd().label(self.RAIL)
        self._d += elm.Resistor().right().label(self.PULLUP_R)
        node = self._d.add(elm.Dot())
        self._d += elm.Button().right().label(name)
        self._d += elm.Line().right().length(0.8)
        self._d += elm.Ground()
        self._tap(node, bcm, header)
        self._y -= self.BUTTON_ROW_GAP

    def _tap(self, node: elm.Element, bcm: str, header: str) -> None:
        """Drop a stub off the divider node showing which pin senses it."""
        self._d += elm.Line().down().at(node.center).length(1.0)
        self._d += elm.Dot(open=True).label(
            "%s\n(Pin %s)" % (bcm, header), loc="bottom", ofst=0.15
        )

    def _source_label(self, bcm: str, header: str) -> elm.Element:
        """A short lead standing in for the header pin at the row start."""
        return (
            elm.Line()
            .right()
            .length(1.2)
            .label("%s\n(Pin %s)" % (bcm, header), loc="left", ofst=0.2)
        )


def main() -> None:
    print(Lab01Schematic().render())


if __name__ == "__main__":
    main()
