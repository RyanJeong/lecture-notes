#!/usr/bin/env bash

# ============================================================================
# Inline ODR Tests
# ============================================================================
# Usage:
#   bash tests/test_inline_odr.sh
#
# Description:
#   Verify multiple translation units with and without inline at -O0.
# ============================================================================

set -euo pipefail

readonly REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readonly FIXTURE="$(mktemp -d)"
trap 'rm -rf "${FIXTURE}"' EXIT

cp "${REPO_DIR}/cpp/02/src/05_inline_odr.hpp" "${FIXTURE}/math_utils.hpp"
printf '#include "math_utils.hpp"\nint First() { return Square(3); }\n' \
  >"${FIXTURE}/first.cc"
printf '#include "math_utils.hpp"\nint First();\nint main() { return First() == 9 && Square(4) == 16 ? 0 : 1; }\n' \
  >"${FIXTURE}/second.cc"
g++ -std=c++14 -O0 -fno-inline -Wall -Wextra -Werror \
  "${FIXTURE}/first.cc" "${FIXTURE}/second.cc" -o "${FIXTURE}/inline"
"${FIXTURE}/inline"
printf '[PASS] inline links and runs without inline optimization\n'

sed 's/^inline int /int /' "${FIXTURE}/math_utils.hpp" >"${FIXTURE}/plain.hpp"
mv "${FIXTURE}/plain.hpp" "${FIXTURE}/math_utils.hpp"
g++ -std=c++14 -O0 -c "${FIXTURE}/first.cc" -o "${FIXTURE}/first.o"
g++ -std=c++14 -O0 -c "${FIXTURE}/second.cc" -o "${FIXTURE}/second.o"
if g++ "${FIXTURE}/first.o" "${FIXTURE}/second.o" -o "${FIXTURE}/plain" \
  >"${FIXTURE}/link.log" 2>&1; then
  printf '[FAIL] non-inline duplicate definitions unexpectedly linked\n' >&2
  exit 1
fi
grep -q 'multiple definition' "${FIXTURE}/link.log"
printf '[PASS] non-inline definitions compile but fail at link time\n'
