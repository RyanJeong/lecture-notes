# ============================================================================
# Grading environment
# ============================================================================
# Builds the toolchain used to unzip and grade student submissions, so the
# process is identical on Linux and macOS.
#
# macOS cannot grade natively:
#   - it ships no timeout(1), which every check.sh relies on
#   - its clang reports different warnings than gcc, which changes scores for
#     the C assignments compiled with -Werror
#   - its unzip mangles the Korean student names in the LMS archives, which
#     would corrupt the student ids in the grade report
#
# Build:
#   docker build -t dju-grader assignment/
#
# Used automatically by:
#   ./unzip.sh --docker
#   ./evaluate_all.sh --docker
# ============================================================================

FROM gcc:14

ENV DEBIAN_FRONTEND=noninteractive

# unzip     : extract submission archives, including the nested per-student
#             archives some submissions contain
# coreutils : timeout(1), used by every check.sh
# locales   : UTF-8 handling for Korean file names
# make      : assignments that ship a Makefile
RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  unzip \
  coreutils \
  locales \
  make \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# C.UTF-8 is built into glibc, so no locale-gen step is needed. Without a UTF-8
# locale the Korean directory names extracted from the archives are unusable.
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# Deliberately no CFLAGS/CXXFLAGS here: each assignment's check.sh owns its own
# compile flags, and inheriting stricter ones from the environment would change
# the scores.

WORKDIR /workspace
