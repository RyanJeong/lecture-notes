# Diagram toolchain for the MEP lab circuits.
#
# Schemdraw renders the symbol-level schematics and needs only matplotlib.
# WireViz renders the pin-level wiring diagrams and shells out to Graphviz,
# which is why this image exists at all: `dot` is not a Python package.
FROM python:3.12-slim

RUN apt-get update \
  && apt-get install -y --no-install-recommends graphviz fonts-dejavu-core \
  && rm -rf /var/lib/apt/lists/*

COPY requirements.txt /tmp/requirements.txt
RUN pip install --no-cache-dir -r /tmp/requirements.txt

# Keep matplotlib headless and its cache inside the image.
ENV MPLBACKEND=Agg \
    MPLCONFIGDIR=/tmp/matplotlib

WORKDIR /workspace
