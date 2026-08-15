# Assignment

A Document Summarizing the Grading Process for Assignments

1. Download students' assignments from the LMS and clone the private repository needed for grading.

    ```shell
    git clone https://github.com/RyanJeong/dju-asmt
    ```

    **Each assignment directory should contain a `check.sh` script, in and out files (refer to `dju-asmt/asmt3-cpp` for details).**

2. Download zip files, locate them at here, and run `unzip.sh` to prepare the assignments for grading. Then, review the results to ensure there are no missing or problematic submissions before starting the grading process (You can use `print_results.sh` during this task).

    ```shell
    ./unzip.sh --docker
    ```

    > **macOS**: use `--docker`. The system `unzip` mangles the Korean student
    > names in the LMS archives, which would corrupt the student ids in the
    > grade report.
3. Run `jplag.sh` to analyze similarity between assignments.
4. Run `viewer.sh <ASMT_DEST_DIR>` to check similarity results and decide whether to reject scoring due to high similarity.

    ```shell
    # e.g.,
    ./viewer.sh ./2025_2_564016_01_2583782/
    ```

5. Run `evaluate_all.sh <ASMT_DEST_DIR> <DATASET_DIR>` to compile and grade every submission.

    The same command covers both C and C++: each assignment's `check.sh` compiles
    the submission itself, so there is no separate build step.

    ```shell
    # e.g.,
    ./evaluate_all.sh --docker ./2026_1_565006_01_1614899/ ./dju-asmt/asmt1-c/
    ./evaluate_all.sh --docker ./2026_1_565006_01_2618307/ ./dju-asmt/asmt2-c/
    ./evaluate_all.sh --docker ./2025_2_564016_01_3586204/ ./dju-asmt/asmt3-cpp/

    # General - c (course code 565006)
    for dir in $(find . -maxdepth 1 -type d -name "*565006*"); do
      ./evaluate_all.sh --docker "${dir}" ./dju-asmt/asmt1-c/
    done

    # General - cpp (course code 564016)
    for dir in $(find . -maxdepth 1 -type d -name "*564016*"); do
      ./evaluate_all.sh --docker "${dir}" ./dju-asmt/asmt2-cpp/
    done
    ```

    Each run prints a per-student report and writes it to
    `<ASMT_DEST_DIR>/results.txt`, ending with a `SUMMARY` block:

    ```text
    ==================== SUMMARY ====================
    Mark_712123: 10
    Daniel_712124: 1
    Ben_712125: compilation failed
    ```

    > **macOS**: use `--docker`. macOS ships no `timeout(1)`, and its `clang`
    > reports different warnings than `gcc`, which would change scores under the
    > `-Werror` used for C assignments.

## Grading Environment (Docker)

`unzip.sh --docker` and `evaluate_all.sh --docker` both run inside the image
built from `assignment/Dockerfile`, so grading is identical on Linux and macOS.
The image is built automatically on first use; rebuild it by hand after editing
the Dockerfile:

```shell
docker build -t dju-grader assignment/
```

Override the image with `--image <name>` if you need a different toolchain.

## Grading Scripts (`dju-asmt`)

Every assignment exposes the same interface, so one driver grades them all:

```shell
./check.sh <CODE_PATH> [IN_OUT_DIR]
```

- `CODE_PATH` accepts a single source file, one submission directory, or a
  directory of submission directories (batch mode).
- `IN_OUT_DIR` defaults to the script's own directory.
- Each submission is compiled in a temp directory, run against `in1..inN`, and
  compared to `out1..outN` after whitespace normalization.
- Scores are reported as `<student_id>: <score>` out of 10.

| Assignment  | Language | Compile flags                             | Tests                      |
| ----------- | -------- | ----------------------------------------- | -------------------------- |
| `asmt1-c`   | C        | `-ansi -Wall -Werror -Wextra -lm`         | 4 inputs + `math.h` + in5  |
| `asmt2-c`   | C        | `-ansi -Wall -Werror -Wextra -lm`         | 5 inputs (`-dcl`/`-undcl`) |
| `asmt3-c`   | C        | `-ansi -Wall -Werror -Wextra -lm`         | 5 inputs (stdin commands)  |
| `asmt2-cpp` | C++      | `-std=c++14 -lpthread -lm`                | 5 inputs                   |
| `asmt3-cpp` | C++      | `-std=c++14 -O2 -lpthread -lm`            | 4 inputs + performance     |

C assignments are graded with `-Werror`; C++ assignments are not, matching the
previous C++ pipeline so scores stay comparable across terms.
