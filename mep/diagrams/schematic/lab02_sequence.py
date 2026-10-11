#!/usr/bin/env python3
"""Lab 02 schematic: two LEDs driven by a state machine, one pulled-up button."""

# Standard library
from typing import List, Tuple

# Third-party
import schemdraw.elements as elm

# Local
from common import Sheet


class Lab02Schematic:
    """Draws the Lab 02 circuit: two LED branches plus one button branch."""

    OUT_PATH: str = "09/img/08-lab02-circuit.png"
    LED_PINS: List[Tuple[str, str, str]] = [
        ("GPIO17", "11", "Red"),
        ("GPIO27", "13", "Green"),
    ]
    BUTTON: Tuple[str, str, str] = ("GPIO23", "16", "SW")
    SERIES_R: str = "330 $\\Omega$"
    PULLUP_R: str = "10 k$\\Omega$"
    RAIL: str = "3.3 V"
    ROW_GAP: float = 2.4
    BUTTON_COLUMN_X: float = 11.5

    def __init__(self) -> None:
        self._sheet = Sheet(self.OUT_PATH)
        self._d = self._sheet.drawing()
        self._y = 0.0

    def render(self) -> str:
        """Draw both LED rows, then the single button branch."""
        for bcm, header, name in self.LED_PINS:
            self._led_row(bcm, header, name)
        self._button_row(*self.BUTTON)
        return self._sheet.save()

    def _led_row(self, bcm: str, header: str, name: str) -> None:
        """GPIO -> 330 ohm -> LED -> GND."""
        self._d.here = (0, self._y)
        self._d += self._lead(bcm, header)
        self._d += elm.Resistor().right().label(self.SERIES_R)
        self._d += elm.LED().right().label(name)
        self._d += elm.Line().right().length(0.8)
        self._d += elm.Ground()
        self._y -= self.ROW_GAP

    def _button_row(self, bcm: str, header: str, name: str) -> None:
        """3.3V -> 10k -> node -> button -> GND, node sensed by the GPIO."""
        self._d.here = (self.BUTTON_COLUMN_X, 0.0)
        self._d += elm.Vdd().label(self.RAIL)
        self._d += elm.Resistor().right().label(self.PULLUP_R)
        node = self._d.add(elm.Dot())
        self._d += elm.Button().right().label(name)
        self._d += elm.Line().right().length(0.8)
        self._d += elm.Ground()
        self._tap(node, bcm, header)

    def _tap(self, node: elm.Element, bcm: str, header: str) -> None:
        """Stub off the divider node naming the sensing pin."""
        self._d += elm.Line().down().at(node.center).length(1.0)
        self._d += elm.Dot(open=True).label(
            "%s\n(Pin %s)" % (bcm, header), loc="bottom", ofst=0.15
        )

    def _lead(self, bcm: str, header: str) -> elm.Element:
        """Short lead standing in for the header pin."""
        return (
            elm.Line()
            .right()
            .length(1.2)
            .label("%s\n(Pin %s)" % (bcm, header), loc="left", ofst=0.2)
        )


def main() -> None:
    print(Lab02Schematic().render())


if __name__ == "__main__":
    main()
