# Assignment

A Document Summarizing the Grading Process for Assignments**

1. Download students' assignments from the LMS and clone the private repository needed for grading.

    ```shell
    git clone https://github.com/RyanJeong/dju-asmt
    ```

    **Each assignment directory should contain a `check.sh` script, in and out files (refer to `dju-asmt/asmt3-cpp` for details).**

2. Run `unzip.sh` to prepare the assignments for grading. Then, review the results to ensure there are no missing or problematic submissions before starting the grading process (You can use `print_results.sh` during this task).
3. Run `jplag.sh` to analyze similarity between assignments.
4. Run `viewer.sh <ASMT_DEST_DIR>` to check similarity results and decide whether to reject scoring due to high similarity.

    ```shell
    # e.g.,
    ./viewer.sh ./2025_2_564016_01_2583782/
    ```

5. Run `{c|cpp}_compile_all.sh <ASMT_DEST_DIR>` to build.

    ```shell
    # e.g.,
    ./cpp_compile_all.sh ./2025_2_564016_01_2583782/

    # General - c
    for dir in $(find . -maxdepth 1 -type d -name "*565006*"); do
      ./cpp_compile_all.sh ${dir}
    done

    # General - cpp
    for dir in $(find . -maxdepth 1 -type d -name "*564016*"); do
      ./cpp_compile_all.sh ${dir}
    done
    ```

6. Run `evaluate_all.sh <ASMT_DEST_DIR> <DATASET_DIR>` to evaluate.

    ```shell
    # e.g.,
    ./evaluate_all.sh ./2025_2_564016_01_2583782/ ./dju-asmt/asmt2-cpp/
    ./evaluate_all.sh ./2025_2_564016_02_2583786/ ./dju-asmt/asmt2-cpp/
    ./evaluate_all.sh ./2025_2_564016_01_3586204/ ./dju-asmt/asmt3-cpp/
    ./evaluate_all.sh ./2025_2_564016_02_3586203/ ./dju-asmt/asmt3-cpp/
    ```

## TODO

- Implement `c_compile_all.sh`
- Check `check.sh` scripts in C assignments
