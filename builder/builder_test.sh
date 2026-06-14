# https://chatgpt.com/c/68a03dac-332c-8321-bcab-ab49c474c0ef
#!/usr/bin/env bash
set -euo pipefail

docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "$PWD":/workspace \
  -w /workspace \
  gcc14-builder \
  bash -lc '
    set -euo pipefail
    shopt -s nullglob

    mkdir -p output

    echo "[INFO] Building single .c files in top-level..."
    for c in *.c; do
      base="${c%.c}"
      echo "  gcc $c -> output/$base"
      gcc $CFLAGS "$c" -o "output/$base" $LDFLAGS
    done

    echo "[INFO] Building directories (dir/*.c -> one binary per dir)..."
    for d in */ ; do
      [ "$d" = "output/" ] && continue

      cs=( "$d"*.c )
      if (( ${#cs[@]} )); then
        out="output/${d%/}"
        echo "  gcc ${d}*.c -> $out"
        gcc $CFLAGS "$d"*.c -o "$out" $LDFLAGS
      fi
    done

    echo "[INFO] Done. Artifacts are in ./output"
  '
