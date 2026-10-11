#!/usr/bin/env bash

# ============================================================================
# Build Temporary Path Tests
# ============================================================================
# Usage:
#   bash tests/test_build_temp_paths.sh
#
# Description:
#   Verify external build scratch paths, cleanup, and syntax-check compatibility.
# ============================================================================

set -euo pipefail

readonly REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readonly FIXTURE="$(mktemp -d)"
trap 'rm -rf "${FIXTURE}"' EXIT
mkdir -p "${FIXTURE}/repo" "${FIXTURE}/scratch" "${FIXTURE}/bin"
cp "${REPO_DIR}/build.sh" "${FIXTURE}/repo/build.sh"

for course in c cpp mep; do
  mkdir -p "${FIXTURE}/repo/${course}/00/src"
  cp "${REPO_DIR}/${course}/check_syntax.sh" "${FIXTURE}/repo/${course}/check_syntax.sh"
done

cat >"${FIXTURE}/bin/npx" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
case "${TMPDIR}" in
"${FIXTURE}/scratch/"*) ;;
*) printf '[FAIL] conversion scratch is not external\n' >&2; exit 1 ;;
esac
test -f "${TMPDIR}/src/example.c"
test -f "${TMPDIR}/error_file_lists.txt"
printf '%s\n' "${TMPDIR}" >>"${FIXTURE}/scratch-paths"
case "${BUILD_MODE:-success}" in
failure) exit 9 ;;
signal) kill -TERM "${PPID}"; exit 0 ;;
esac
while [ "$#" -gt 0 ]; do
  if [ "$1" = "-o" ]; then
    printf 'converted\n' >"$2"
    break
  fi
  shift
done
EOF
chmod +x "${FIXTURE}/bin/npx"
export FIXTURE
export PATH="${FIXTURE}/bin:${PATH}"
export TMPDIR="${FIXTURE}/scratch"

printf 'int main(void) { return 0; }\n' >"${FIXTURE}/repo/c/00/src/example.c"
printf '[//]: # "INCLUDE: ./c/00/src/example.c"\n' >"${FIXTURE}/repo/c/00/README.md"

run_build() {
  bash "${FIXTURE}/repo/build.sh" c/00/README.md c/00/temp.md c/00/temp.pdf
}

if ! run_build >"${FIXTURE}/success.log" 2>&1; then
  cat "${FIXTURE}/success.log" >&2
  exit 1
fi
test -f "${FIXTURE}/repo/c/00/temp.md"
test -f "${FIXTURE}/repo/c/00/temp.pdf"
test ! -e "${FIXTURE}/repo/c/error_file_lists.txt"
test -z "$(find "${FIXTURE}/scratch" -mindepth 1 -print -quit)"
printf '[PASS] scratch and logs external; explicit outputs retained; success cleanup\n'

for mode in failure signal; do
  if BUILD_MODE="${mode}" run_build >"${FIXTURE}/${mode}.log" 2>&1; then
    printf '[FAIL] build ignored %s\n' "${mode}" >&2
    exit 1
  fi
  test -z "$(find "${FIXTURE}/scratch" -mindepth 1 -print -quit)"
  printf '[PASS] %s propagates and cleans scratch\n' "${mode}"
done

printf '[//]: # "INCLUDE: ./c/00/src/missing.c"\n' >"${FIXTURE}/repo/c/00/README.md"
if run_build >"${FIXTURE}/missing.log" 2>&1; then
  printf '[FAIL] missing INCLUDE accepted\n' >&2
  exit 1
fi
test ! -e "${FIXTURE}/repo/c/00/src/missing.c"
test -z "$(find "${FIXTURE}/scratch" -mindepth 1 -print -quit)"
grep -q 'INCLUDE file not found' "${FIXTURE}/missing.log"
printf '[PASS] missing INCLUDE fails without creating a source file\n'

for course in c cpp mep; do
  ext=cc
  [ "${course}" != c ] || ext=c
  mkdir -p "${FIXTURE}/external/src"
  printf 'int main(void) { return 0; }\n' >"${FIXTURE}/external/src/check.${ext}"
  bash "${FIXTURE}/repo/${course}/check_syntax.sh" "${FIXTURE}/external" \
    "${FIXTURE}/external/errors.txt" >"${FIXTURE}/${course}.log" 2>&1
  test ! -e "${FIXTURE}/repo/${course}/error_file_lists.txt"
  printf 'invalid source\n' >"${FIXTURE}/external/src/check.${ext}"
  if bash "${FIXTURE}/repo/${course}/check_syntax.sh" "${FIXTURE}/external" \
    "${FIXTURE}/external/errors.txt" >>"${FIXTURE}/${course}.log" 2>&1; then
    printf '[FAIL] %s external syntax error accepted\n' "${course}" >&2
    exit 1
  fi
  test -s "${FIXTURE}/external/errors.txt"
  if bash "${FIXTURE}/repo/${course}/check_syntax.sh" "${FIXTURE}/absent" \
    "${FIXTURE}/external/errors.txt" >>"${FIXTURE}/${course}.log" 2>&1; then
    printf '[FAIL] %s missing external directory accepted\n' "${course}" >&2
    exit 1
  fi
  rm "${FIXTURE}/external/src/check.${ext}"
  printf 'int main(void) { return 0; }\n' >"${FIXTURE}/repo/${course}/00/src/check.${ext}"
  bash "${FIXTURE}/repo/${course}/check_syntax.sh" 00 >>"${FIXTURE}/${course}.log" 2>&1
  test -f "${FIXTURE}/repo/${course}/error_file_lists.txt"
  printf '[PASS] %s external success/failure and legacy relative path\n' "${course}"
done
