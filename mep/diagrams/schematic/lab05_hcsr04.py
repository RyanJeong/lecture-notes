#!/usr/bin/env python3
"""Lab 05 schematic: HC-SR04 with a 1k/2k echo divider, plus a buzzer."""

# Standard library
from typing import List, Tuple

# Third-party
import schemdraw.elements as elm

# Local
from common import Sheet


class Lab05Schematic:
    """Draws the sonar module, the 5V-to-3.3V echo divider and the buzzer."""

    OUT_PATH: str = "10/img/14-lab05-circuit.png"
    MODULE_LABEL: str = "HC-SR04\n(5 V sonar)"
    MODULE_X: float = 11.0
    MODULE_SIZE: Tuple[float, float] = (3.4, 5.2)
    PIN_LABEL_SIZE: int = 11
    # Listed bottom-up: schemdraw stacks the first pin at the bottom edge.
    # ECHO sits at the bottom so its divider drops into clear space; the
    # module's real pin order is shown in the wiring diagram instead.
    PINS: List[str] = ["ECHO", "GND", "TRIG", "VCC"]
    DIRECT_LEADS: List[Tuple[str, str, float]] = [
        ("VCC", "5 V (Pin 2)", 6.0),
        ("TRIG", "GPIO23 (Pin 16)", 6.0),
        ("GND", "GND (Pin 6)", 6.0),
    ]
    TOP_R: str = "1 k$\\Omega$"
    BOTTOM_R: str = "2 k$\\Omega$"
    BUZZER_DROP: float = 4.0
    WARNING: str = "Echo is 5 V: the divider is mandatory,\n"\
                   "a direct connection damages the SoC"

    def __init__(self) -> None:
        self._sheet = Sheet(self.OUT_PATH)
        self._d = self._sheet.drawing()

    def render(self) -> str:
        """Place the module, its plain leads, the echo divider and the buzzer."""
        module = self._module()
        self._d += module
        for name, label, length in self.DIRECT_LEADS:
            self._lead(module, name, label, length)
        self._echo_divider(module)
        self._buzzer_row(module)
        return self._sheet.save()

    def _module(self) -> elm.Element:
        """The HC-SR04 block with all four pins facing the header."""
        pins = [
            elm.IcPin(name=name, side="left", lblsize=self.PIN_LABEL_SIZE)
            for name in self.PINS
        ]
        return (
            elm.Ic(pins=pins, size=self.MODULE_SIZE)
            .right()
            .at((self.MODULE_X, 0))
            .label(self.MODULE_LABEL, loc="top", ofst=0.4)
        )

    def _lead(
        self, module: elm.Element, name: str, label: str, length: float
    ) -> None:
        """Run a plain wire from one module pin left to its header label."""
        self._d += (
            elm.Line()
            .left()
            .at(getattr(module, name))
            .length(length)
            .label(label, loc="left", ofst=0.2)
        )

    def _echo_divider(self, module: elm.Element) -> None:
        """ECHO -> 1k -> node -> GPIO24, with 2k from the node down to GND."""
        self._d += elm.Resistor().left().at(module.ECHO).label(self.TOP_R)
        node = self._d.add(elm.Dot())
        self._d += (
            elm.Line().left().length(2.0).label("GPIO24 (Pin 18)", loc="left")
        )
        self._d += elm.Resistor().down().at(node.center).label(self.BOTTOM_R)
        self._d += elm.Ground()
        self._d += (
            elm.Label().at((node.center[0] + 1.0, -3.6)).label(self.WARNING)
        )

    def _buzzer_row(self, module: elm.Element) -> None:
        """A separate GPIO drives the warning buzzer straight to GND."""
        self._d.here = (0, module.GND[1] - self.BUZZER_DROP)
        self._d += (
            elm.Line()
            .right()
            .length(1.2)
            .label("GPIO18\n(Pin 12)", loc="left", ofst=0.2)
        )
        self._d += elm.RBox().right().label("Buzzer")
        self._d += elm.Line().right().length(0.8)
        self._d += elm.Ground()


def main() -> None:
    print(Lab05Schematic().render())


if __name__ == "__main__":
    main()
