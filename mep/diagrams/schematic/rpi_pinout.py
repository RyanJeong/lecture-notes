#!/usr/bin/env python3
"""Raspberry Pi 40-pin header pinout, drawn along the canvas like the board."""

# Standard library
from typing import Dict, List, Tuple

# Third-party
from matplotlib.patches import Rectangle

# Local
from common import Frame


class Palette:
    """One colour per signal class, so a pin's role reads at a glance."""

    COLORS: Dict[str, str] = {
        "3V3": "#f39c12",
        "5V": "#c0392b",
        "GND": "#4d4d4d",
        "GPIO": "#27ae60",
        "I2C": "#2980b9",
        "SPI": "#8e44ad",
        "UART": "#16a085",
        "RSVD": "#7f8c8d",
    }
    TEXT_ON_FILL: str = "#ffffff"


class Header:
    """The physical 40-pin header: (physical pin, label, signal class)."""

    # Odd pins run along the bottom row, even pins along the top row.
    ODD: List[Tuple[int, str, str]] = [
        (1, "3V3", "3V3"), (3, "GPIO2\nSDA1", "I2C"), (5, "GPIO3\nSCL1", "I2C"),
        (7, "GPIO4\nGPCLK0", "GPIO"), (9, "GND", "GND"),
        (11, "GPIO17", "GPIO"), (13, "GPIO27", "GPIO"), (15, "GPIO22", "GPIO"),
        (17, "3V3", "3V3"), (19, "GPIO10\nMOSI", "SPI"),
        (21, "GPIO9\nMISO", "SPI"), (23, "GPIO11\nSCLK", "SPI"),
        (25, "GND", "GND"), (27, "GPIO0\nID_SD", "RSVD"),
        (29, "GPIO5", "GPIO"), (31, "GPIO6", "GPIO"),
        (33, "GPIO13\nPWM1", "GPIO"), (35, "GPIO19\nMISO1", "SPI"),
        (37, "GPIO26", "GPIO"), (39, "GND", "GND"),
    ]
    EVEN: List[Tuple[int, str, str]] = [
        (2, "5V", "5V"), (4, "5V", "5V"), (6, "GND", "GND"),
        (8, "GPIO14\nTXD", "UART"), (10, "GPIO15\nRXD", "UART"),
        (12, "GPIO18\nPWM0", "GPIO"), (14, "GND", "GND"),
        (16, "GPIO23", "GPIO"), (18, "GPIO24", "GPIO"), (20, "GND", "GND"),
        (22, "GPIO25", "GPIO"), (24, "GPIO8\nCE0", "SPI"),
        (26, "GPIO7\nCE1", "SPI"), (28, "GPIO1\nID_SC", "RSVD"),
        (30, "GND", "GND"), (32, "GPIO12\nPWM0", "GPIO"), (34, "GND", "GND"),
        (36, "GPIO16", "GPIO"), (38, "GPIO20\nMOSI1", "SPI"),
        (40, "GPIO21\nSCLK1", "SPI"),
    ]


class PinoutDiagram:
    """Renders the header as two rows of twenty labelled pins."""

    OUT_PATH: str = "09/img/22-rpi-pinout.png"
    COLUMNS: int = 20
    CELL_W: float = 1.0
    CELL_H: float = 2.2
    GAP: float = 1.6
    LABEL_SIZE: int = 9
    PIN_SIZE: int = 8
    TITLE: str = "Raspberry Pi 4 - 40-pin GPIO header (BCM naming)"
    TITLE_SIZE: int = 15

    def __init__(self) -> None:
        self._frame = Frame(self.OUT_PATH)
        self._ax = self._frame.axes()

    def render(self) -> str:
        """Draw both rows, the connector body, the title and the legend."""
        self._body()
        self._row(Header.EVEN, self.GAP / 2.0, above=True)
        self._row(Header.ODD, -self.GAP / 2.0 - self.CELL_H, above=False)
        self._title()
        self._legend()
        self._frame.fit((0.0, -5.3, self.COLUMNS * self.CELL_W, 5.1))
        return self._frame.save()

    def _body(self) -> None:
        """The dark strip standing in for the connector shroud."""
        self._ax.add_patch(
            Rectangle(
                (0, -self.GAP / 2.0), self.COLUMNS * self.CELL_W, self.GAP,
                facecolor="#2c3e50", edgecolor="#2c3e50",
            )
        )

    def _row(self, pins: List[Tuple[int, str, str]], y: float, above: bool) -> None:
        """Lay one row of twenty pins out along the header."""
        for column, (number, label, kind) in enumerate(pins):
            x = column * self.CELL_W
            self._cell(x, y, label, kind)
            self._pin_number(x, number, above)

    def _cell(self, x: float, y: float, label: str, kind: str) -> None:
        """One coloured box carrying a pin's name."""
        pad = 0.06
        self._ax.add_patch(
            Rectangle(
                (x + pad, y), self.CELL_W - 2 * pad, self.CELL_H,
                facecolor=Palette.COLORS[kind], edgecolor="none",
            )
        )
        self._ax.text(
            x + self.CELL_W / 2.0, y + self.CELL_H / 2.0, label,
            ha="center", va="center", fontsize=self.LABEL_SIZE,
            color=Palette.TEXT_ON_FILL, linespacing=1.3, rotation=90,
        )

    def _pin_number(self, x: float, number: int, above: bool) -> None:
        """The physical pin number, printed on the connector strip."""
        y = self.GAP / 4.0 if above else -self.GAP / 4.0
        self._ax.text(
            x + self.CELL_W / 2.0, y, str(number), ha="center", va="center",
            fontsize=self.PIN_SIZE, color="#ffffff",
        )

    def _title(self) -> None:
        """Caption above the header."""
        self._ax.text(
            self.COLUMNS * self.CELL_W / 2.0, 4.3, self.TITLE,
            ha="center", va="center", fontsize=self.TITLE_SIZE, color="#222222",
        )

    def _legend(self) -> None:
        """Colour key placed under the odd-numbered row."""
        keys = list(Palette.COLORS.keys())
        width = self.COLUMNS * self.CELL_W / float(len(keys))
        for index, kind in enumerate(keys):
            x = index * width
            self._ax.add_patch(
                Rectangle((x, -4.9), 0.8, 0.7,
                          facecolor=Palette.COLORS[kind], edgecolor="none")
            )
            self._ax.text(x + 1.0, -4.55, kind, ha="left", va="center",
                          fontsize=self.LABEL_SIZE + 2, color="#222222")


def main() -> None:
    print(PinoutDiagram().render())


if __name__ == "__main__":
    main()
