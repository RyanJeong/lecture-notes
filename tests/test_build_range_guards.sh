#!/usr/bin/env bash

# ============================================================================
# Build Range Guard Tests
# ============================================================================
# Usage:
#   ./tests/test_build_range_guards.sh
#
# Description:
#   Verify that line-ranged INCLUDE placeholders are bounded by marked
#   preprocessor guards.
# ============================================================================

set -euo pipefail

readonly TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly REPO_DIR="$(dirname "${TEST_DIR}")"
readonly MARKER="DO NOT CONTAIN THIS LINE IN THE MARKDOWN"

source "${REPO_DIR}/build.sh"

pass_count=0

pass() {
  printf '[PASS] %s\n' "$1"
  pass_count=$((pass_count + 1))
}

expect_success() {
  local name="$1"
  local file="$2"
  shift 2

  validate_include_range_guards "${file}" "$@"
  pass "${name}"
}

expect_failure() {
  local name="$1"
  local file="$2"
  shift 2

  if (validate_include_range_guards "${file}" "$@" >/dev/null 2>&1); then
    printf '[FAIL] %s\n' "${name}" >&2
    exit 1
  fi
  pass "${name}"
}

main() {
  local temp_dir
  temp_dir=$(mktemp -d)
  trap "rm -rf '${temp_dir}'" EXIT

  cat >"${temp_dir}/valid.c" <<EOF
#if 1 /* ${MARKER} */
int value = 1;
#endif /* ${MARKER} */
#if 0 /* ${MARKER} */
this is intentionally invalid
#endif /* ${MARKER} */
EOF

  expect_success "accepts #if 1 range" "${temp_dir}/valid.c" 2 2
  expect_success "accepts #if 0 range" "${temp_dir}/valid.c" 5 5
  expect_failure "rejects shifted closing guard" "${temp_dir}/valid.c" 2 3
  expect_failure "rejects missing opening guard" "${temp_dir}/valid.c" 1 2
  expect_failure "rejects open-ended range" "${temp_dir}/valid.c" 2 ""

  printf '#if 1 /* %s */\nint final_value = 1;\n#endif /* %s */' \
    "${MARKER}" "${MARKER}" >"${temp_dir}/no_newline.c"
  expect_success "accepts file without trailing newline" \
    "${temp_dir}/no_newline.c" 2 2

  printf '[PASS] %d range guard tests\n' "${pass_count}"
}

main "$@"
