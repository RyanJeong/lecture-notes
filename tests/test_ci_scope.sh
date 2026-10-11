#!/usr/bin/env bash

# ============================================================================
# CI Scope Tests
# ============================================================================
# Usage:
#   bash tests/test_ci_scope.sh
#
# Description:
#   Verify course selection and artifact reporting without running builds.
# ============================================================================

set -euo pipefail

readonly TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly REPO_DIR="$(dirname "${TEST_DIR}")"
readonly FIXTURE="$(mktemp -d)"
trap 'rm -rf "${FIXTURE}"' EXIT

cp "${REPO_DIR}/ci.sh" "${FIXTURE}/ci.sh"
mkdir -p "${FIXTURE}/release"
for course in c cpp mep; do
  mkdir -p "${FIXTURE}/${course}" "${FIXTURE}/release/${course}"
  touch "${FIXTURE}/${course}/check_syntax.sh"
  touch "${FIXTURE}/release/${course}/00.pdf"
done

run_ci() {
  (
    source "${FIXTURE}/ci.sh"
    check_dependencies() { return 0; }
    run_lang() {
      printf 'RUN %s\n' "$1"
      record "OK" "$1"
    }
    main "$@"
  )
}

expect_courses() {
  local name="$1"
  local expected="$2"
  shift 2
  local output actual
  output="$(run_ci "$@")"
  actual="$(printf '%s\n' "${output}" | grep '^RUN ' | sort)"
  if [ "${actual}" != "${expected}" ]; then
    printf '[FAIL] %s: unexpected courses\n%s\n' "${name}" "${output}" >&2
    exit 1
  fi
  printf '[PASS] %s\n' "${name}"
}

expect_courses "single course" "RUN c" c
expect_courses "multiple courses" $'RUN c\nRUN mep' c mep
expect_courses "default all courses" $'RUN c\nRUN cpp\nRUN mep'

if run_ci unknown >"${FIXTURE}/invalid.log" 2>&1; then
  printf '[FAIL] unknown course accepted\n' >&2
  exit 1
fi
grep -q 'Unknown course' "${FIXTURE}/invalid.log"
printf '[PASS] unknown course rejected\n'

output="$(run_ci c)"
if printf '%s\n' "${output}" | grep -Eq 'release/(cpp|mep)/'; then
  printf '[FAIL] single-course summary lists unrelated artifacts\n%s\n' "${output}" >&2
  exit 1
fi
printf '%s\n' "${output}" | grep -q 'release/c/00.pdf'
printf '[PASS] summary contains only selected course artifacts\n'

mkdir -p "${FIXTURE}/c/00" "${FIXTURE}/c/01"
printf '%s\n' '#!/usr/bin/env bash' 'set -euo pipefail' 'exit 0' \
  >"${FIXTURE}/c/check_syntax.sh"
printf '%s\n' '#!/usr/bin/env bash' 'set -euo pipefail' 'printf "BUILD:%s\n" "$@"' \
  >"${FIXTURE}/build.sh"
printf '%s\n' '#!/usr/bin/env bash' 'set -euo pipefail' \
  'printf "CHECK:%s\n" "$@"' 'exit "${CHECK_STATUS:-0}"' \
  >"${FIXTURE}/check_and_release.sh"
chmod +x "${FIXTURE}/c/check_syntax.sh" "${FIXTURE}/build.sh" \
  "${FIXTURE}/check_and_release.sh"

run_workflow() {
  (
    source "${FIXTURE}/ci.sh"
    check_dependencies() { return 0; }
    export CHECK_STATUS
    main c
  )
}

CHECK_STATUS=0 run_workflow >"${FIXTURE}/success.log" 2>&1
grep -q '^CHECK:c/00/temp.pdf$' "${FIXTURE}/success.log"
grep -q '^CHECK:c/01/temp.pdf$' "${FIXTURE}/success.log"
printf '[PASS] CI delegates each selected chapter to check_and_release.sh\n'

if CHECK_STATUS=1 run_workflow >"${FIXTURE}/failure.log" 2>&1; then
  printf '[FAIL] CI ignores checker failure\n' >&2
  exit 1
fi
grep -q '^CHECK:c/01/temp.pdf$' "${FIXTURE}/failure.log"
grep -q 'c/00 (check)' "${FIXTURE}/failure.log"
grep -q 'c/01 (check)' "${FIXTURE}/failure.log"
printf '[PASS] CI preserves checker failure and continues remaining chapters\n'
test -f "${FIXTURE}/release/cpp/00.pdf"
test -f "${FIXTURE}/release/mep/00.pdf"
printf '[PASS] unrelated course artifacts are preserved\n'
