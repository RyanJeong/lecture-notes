#!/usr/bin/env python3
"""One framing rule for every breadboard layout."""

# Standard library
from typing import Tuple

# Local
from board import Breadboard


class Framing:
    """Bounds wide enough for the pin captions and the routing lanes."""

    LABEL_MARGIN: float = 9.5
    BELOW_MARGIN: float = 1.6
    ABOVE_MARGIN: float = 24.4

    @classmethod
    def bounds(cls, board_x: float) -> Tuple[float, float, float, float]:
        """The rectangle a layout is fitted into, given its board origin."""
        return (-cls.LABEL_MARGIN, -cls.BELOW_MARGIN,
                board_x + Breadboard.WIDTH, cls.ABOVE_MARGIN)
