#!/usr/bin/env python3
"""Shared canvas, style and helpers for the MEP lab diagrams.

Every generator renders onto one fixed canvas whose aspect matches the
lecture slide's usable content area. A diagram therefore always drops into
a slide at a predictable size: at `h:N` it occupies N x N*ASPECT pixels, so
any height up to MAX_SLIDE_HEIGHT is guaranteed to fit the slide width.
"""

# Standard library
import os
from typing import List, Tuple

# Third-party
import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt  # noqa: E402
import schemdraw  # noqa: E402
import schemdraw.elements as elm  # noqa: E402


class Canvas:
    """The single output frame every diagram is fitted into."""

    # Slide is 1024x768; the theme leaves about 868x470 usable for an image
    # that shares a slide with a heading and a bullet.
    SLIDE_WIDTH: int = 1024
    USABLE_WIDTH: int = 868
    MAX_SLIDE_HEIGHT: int = 460
    ASPECT: float = 1.85

    DPI: int = 200
    WIDTH_IN: float = 8.68
    MARGIN: float = 0.06

    @classmethod
    def height_in(cls) -> float:
        """Canvas height in inches, derived from the fixed aspect."""
        return cls.WIDTH_IN / cls.ASPECT

    @classmethod
    def figure(cls) -> Tuple[plt.Figure, plt.Axes]:
        """A blank figure sized to the canvas, with no axes decoration."""
        fig, ax = plt.subplots(figsize=(cls.WIDTH_IN, cls.height_in()))
        fig.subplots_adjust(left=0, right=1, top=1, bottom=0)
        ax.set_aspect("equal")
        ax.axis("off")
        return fig, ax


class Style:
    """Drawing constants shared by every lab schematic."""

    FONT_SIZE: int = 11
    LINE_WIDTH: float = 1.5
    UNIT: float = 2.4


class Frame:
    """Fits arbitrary content into the canvas and writes the PNG."""

    def __init__(self, out_path: str) -> None:
        self._out_path = out_path
        self._fig, self._axes = Canvas.figure()

    def axes(self) -> plt.Axes:
        """Expose the axes so a generator can draw onto it."""
        return self._axes

    def fit(self, bounds: Tuple[float, float, float, float]) -> None:
        """Centre the given data bounds and letterbox them to the aspect."""
        xmin, ymin, xmax, ymax = bounds
        pad = Canvas.MARGIN * max(xmax - xmin, ymax - ymin)
        width, height = (xmax - xmin) + 2 * pad, (ymax - ymin) + 2 * pad
        if width / height < Canvas.ASPECT:
            width = height * Canvas.ASPECT
        else:
            height = width / Canvas.ASPECT
        mid_x, mid_y = (xmin + xmax) / 2.0, (ymin + ymax) / 2.0
        self._axes.set_xlim(mid_x - width / 2.0, mid_x + width / 2.0)
        self._axes.set_ylim(mid_y - height / 2.0, mid_y + height / 2.0)

    def save(self) -> str:
        """Write the PNG, creating the target directory when absent."""
        directory = os.path.dirname(self._out_path)
        if directory:
            os.makedirs(directory, exist_ok=True)
        self._fig.savefig(self._out_path, dpi=Canvas.DPI, facecolor="white")
        plt.close(self._fig)
        return self._out_path


class Sheet:
    """A schemdraw drawing rendered onto the shared fixed canvas."""

    def __init__(self, out_path: str) -> None:
        self._frame = Frame(out_path)
        self._drawing = schemdraw.Drawing()
        self._drawing.config(
            unit=Style.UNIT, fontsize=Style.FONT_SIZE, lw=Style.LINE_WIDTH
        )

    def drawing(self) -> schemdraw.Drawing:
        """Expose the underlying drawing so a lab can add elements."""
        return self._drawing

    def save(self) -> str:
        """Render the schematic into the canvas and write it out."""
        self._drawing.draw(show=False, canvas=self._frame.axes())
        box = self._drawing.get_bbox()
        self._frame.fit((box.xmin, box.ymin, box.xmax, box.ymax))
        return self._frame.save()


class Board:
    """Builds a Raspberry Pi header block used as a left-hand anchor."""

    LABEL: str = "Raspberry Pi 4"
    SIDE: str = "right"

    def __init__(self, pins: List[Tuple[str, str]]) -> None:
        self._pins = pins

    def element(self) -> elm.Ic:
        """Return an Ic element carrying one labelled pin per entry."""
        return elm.Ic(
            pins=[self._pin(name, num) for name, num in self._pins]
        ).label(self.LABEL, loc="top", ofst=0.3)

    def _pin(self, name: str, num: str) -> elm.IcPin:
        """Wrap one BCM name and its physical header number."""
        return elm.IcPin(name=name, pin=num, side=self.SIDE)
