# Assignment

A Document Summarizing the Grading Process for Assignments**

1. Download students' assignments from the LMS and clone the private repository needed for grading.

    ```shell
    git clone https://github.com/RyanJeong/dju-asmt
    ```

2. Run `unzip.sh` to prepare the assignments for grading. Then, review the results to ensure there are no missing or problematic submissions before starting the grading process (You can use `print_results.sh` during this task).
3. Run `jplag.sh` to analyze similarity between assignments.
4. Run `viewer.sh <ASMT_DEST_DIR>` to check similarity results and decide whether to reject scoring due to high similarity.
5. ~~Run `evaluate_all.sh <ASMT_SRC_DIR> <ASMT_DEST_DIR> <RAND_SIZE>`.~~

-> Need to build in the docker container that we use in lectures.
-> 1. Add a dockerfile that we use in lectures at here
-> 2. Investigate how to run another docker container from this env.
-> 3. Fix some scripts related with build-stuff.
