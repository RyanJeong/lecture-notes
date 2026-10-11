#!/usr/bin/env python3
"""Lab 03 schematic: DHT11 three-pin module on a single-wire data line."""

# Standard library
from typing import List, Tuple

# Third-party
import schemdraw.elements as elm

# Local
from common import Sheet


class Lab03Schematic:
    """Draws the DHT11 module block and its three leads to the header."""

    OUT_PATH: str = "10/img/09-lab03-circuit.png"
    MODULE_LABEL: str = "DHT11\n(3-pin module)"
    MODULE_X: float = 7.0
    # Listed bottom-up: schemdraw stacks the first pin at the bottom edge.
    PINS: List[Tuple[str, str]] = [
        ("GND", "GND (Pin 9)"),
        ("DATA", "GPIO4 (Pin 7)"),
        ("VCC", "3.3 V (Pin 1)"),
    ]
    LEAD_LENGTH: float = 3.4
    PIN_LABEL_SIZE: int = 11
    NOTE: str = "Module carries its own\n10 k$\\Omega$ pull-up on DATA"

    def __init__(self) -> None:
        self._sheet = Sheet(self.OUT_PATH)
        self._d = self._sheet.drawing()

    def render(self) -> str:
        """Place the module, then draw one labelled lead per pin."""
        module = self._module()
        self._d += module
        for name, label in self.PINS:
            self._lead(module, name, label)
        return self._sheet.save()

    def _module(self) -> elm.Element:
        """The DHT11 block with its three pins facing the header."""
        pins = [
            elm.IcPin(name=name, side="left", lblsize=self.PIN_LABEL_SIZE)
            for name, _ in self.PINS
        ]
        return (
            elm.Ic(pins=pins, size=(3.0, 3.2))
            .at((self.MODULE_X, 0))
            .label(self.MODULE_LABEL, loc="top", ofst=0.4)
            .label(self.NOTE, loc="bottom", ofst=0.4)
        )

    def _lead(self, module: elm.Element, name: str, label: str) -> None:
        """Run a wire from one module pin left to its header label."""
        anchor = getattr(module, name)
        self._d += (
            elm.Line().left().at(anchor).length(self.LEAD_LENGTH).label(
                label, loc="left", ofst=0.2
            )
        )


def main() -> None:
    print(Lab03Schematic().render())


if __name__ == "__main__":
    main()
