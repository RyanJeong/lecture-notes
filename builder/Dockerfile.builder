FROM gcc:14

# Basic tools
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y \
  gdb git make pkg-config sudo \
  && useradd -m -s /bin/bash vscode \
  && echo "vscode ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/99_vscode \
  && chmod 0440 /etc/sudoers.d/99_vscode \
  && apt clean \
  && rm -rf /var/lib/apt/lists/

# ---- Default compile/link flags ----
# C (gcc): -lm -ansi -Wall -Werror -Wextra -Wpedantic
ENV CFLAGS="-ansi -Wall -Werror -Wextra -Wpedantic"

# Always link with -lm (harmless for C++)
ENV LDFLAGS="-lm -pthread"

# C++ (g++): -std=c++14 -Wall -Werror -Wextra -Wpedantic -pthread
ENV CXXFLAGS="-std=c++14 -Wall -Werror -Wextra -Wpedantic -pthread"

USER vscode