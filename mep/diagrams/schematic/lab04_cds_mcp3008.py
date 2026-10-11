#!/usr/bin/env python3
"""Lab 04 schematic: CdS divider feeding an MCP3008 SPI ADC, plus one LED."""

# Standard library
from typing import List, Tuple

# Third-party
import schemdraw.elements as elm

# Local
from common import Sheet


class Lab04Schematic:
    """Draws the light-sensing divider, the ADC block and its SPI leads."""

    OUT_PATH: str = "10/img/11-lab04-divider-circuit.png"
    ADC_LABEL: str = "MCP3008\n(10-bit SPI ADC)"
    ADC_X: float = 8.0
    ADC_SIZE: Tuple[float, float] = (4.0, 7.0)
    FIXED_R: str = "10 k$\\Omega$"
    SERIES_R: str = "330 $\\Omega$"
    RAIL: str = "3.3 V"
    LEAD_LENGTH: float = 3.6
    PIN_LABEL_SIZE: int = 10
    # Listed bottom-up: schemdraw stacks the first pin at the bottom edge.
    RIGHT_PINS: List[Tuple[str, str]] = [
        ("DGND", "GND"),
        ("CS", "GPIO8 / CE0 (Pin 24)"),
        ("DIN", "GPIO10 / MOSI (Pin 19)"),
        ("DOUT", "GPIO9 / MISO (Pin 21)"),
        ("CLK", "GPIO11 / SCLK (Pin 23)"),
        ("AGND", "GND"),
        ("VREF", "3.3 V"),
        ("VDD", "3.3 V (Pin 1)"),
    ]
    LED_DROP: float = 5.2

    def __init__(self) -> None:
        self._sheet = Sheet(self.OUT_PATH)
        self._d = self._sheet.drawing()

    def render(self) -> str:
        """Draw the divider, the ADC with its leads, then the LED branch."""
        node = self._divider()
        adc = self._adc(node.center[1])
        self._d += adc
        self._d += elm.Line().at(node.center).to(adc.CH0)
        for name, label in self.RIGHT_PINS:
            self._lead(adc, name, label)
        self._led_row(node.center[1] - self.LED_DROP)
        return self._sheet.save()

    def _divider(self) -> elm.Element:
        """3.3V -> CdS -> node -> 10k -> GND, drawn top to bottom."""
        self._d.here = (0, 2.0)
        self._d += elm.Vdd().label(self.RAIL)
        self._d += elm.Photoresistor().down().label("CdS")
        node = self._d.add(elm.Dot())
        self._d += elm.Resistor().down().label(self.FIXED_R)
        self._d += elm.Ground()
        return node

    def _adc(self, center_y: float) -> elm.Element:
        """The MCP3008 block, vertically centred on the divider node."""
        pins = [elm.IcPin(name="CH0", side="left", lblsize=self.PIN_LABEL_SIZE)]
        pins += [
            elm.IcPin(name=name, side="right", lblsize=self.PIN_LABEL_SIZE)
            for name, _ in self.RIGHT_PINS
        ]
        return (
            elm.Ic(pins=pins, size=self.ADC_SIZE)
            .right()
            .at((self.ADC_X, center_y))
            .anchor("CH0")
            .label(self.ADC_LABEL, loc="top", ofst=0.4)
        )

    def _lead(self, adc: elm.Element, name: str, label: str) -> None:
        """Run a wire from one ADC pin right to its header label."""
        self._d += (
            elm.Line()
            .right()
            .at(getattr(adc, name))
            .length(self.LEAD_LENGTH)
            .label(label, loc="right", ofst=0.2, halign="left")
        )

    def _led_row(self, row_y: float) -> None:
        """Stage 1 of the lab drives one LED straight from a GPIO."""
        self._d.here = (0, row_y)
        self._d += (
            elm.Line()
            .right()
            .length(1.2)
            .label("GPIO17\n(Pin 11)", loc="left", ofst=0.2)
        )
        self._d += elm.Resistor().right().label(self.SERIES_R)
        self._d += elm.LED().right().label("LED")
        self._d += elm.Line().right().length(0.8)
        self._d += elm.Ground()


def main() -> None:
    print(Lab04Schematic().render())


if __name__ == "__main__":
    main()
