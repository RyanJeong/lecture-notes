# lecture-notes

A collection of lecture notes, slides, and study materials

## Prerequisite

* [Docker](https://docs.docker.com/get-started/get-docker/)

* [VSCode](https://code.visualstudio.com/download)
  * `markdownlint`

  ```shell
  code --install-extension DavidAnson.vscode-markdownlint
  ```

  * `Run on Save`

  ```shell
  code --install-extension emeraldwalk.RunOnSave
  ```

  * `paste image anywhere`

  ```shell
  code --install-extension dzylikecode.md-paste-enhanced
  ```

* [pngstate](https://github.com/jcsalterego/pngpaste)

```shell
brew install pngstate
``` 

## Build `dockerfile`

```shell
# USE_LOCAL_SSH_KEY
# - true  : use ${SSH_PUB_KEY} to set the container's authorized_keys
# - false : use ${AUTH_KEY} to set the container's authorized_keys
USE_LOCAL_SSH_KEY=true
docker build \
  --build-arg PASSWORD=docker \
  --build-arg SSH_PUB_KEY="$(cat ~/.ssh/id_rsa.pub)" \
  --build-arg SSH_PRIV_KEY="$(cat ~/.ssh/id_rsa)" \
  --build-arg AUTH_KEY="$(cat ~/.ssh/authorized_keys)" \
  --build-arg GIT_NAME="$(git config user.name)" \
  --build-arg GIT_EMAIL="$(git config user.email)" \
  --build-arg USE_LOCAL_SSH_KEY="${USE_LOCAL_SSH_KEY}" \
  -t marp-dev ./

docker run -p 33221:22 -v ${HOME}/share:/home/docker/share -itd --name marp-dev marp-dev
```

## Access the Container

```shell
code --remote ssh-remote+marp /home/docker/lecture-notes
```

## Build Markdowns

```shell
LANG="c"
CH="01"
# Usage: ./build.sh source_markdown temp_markdown output_pdf [loop]
./build.sh "$LANG"/"$CH"/README.md pdfs/temp.md pdfs/README.pdf loop
./build.sh "$LANG"/"$CH"/README.md pptxs/temp.md pptxs/README.pptx
```

---

## Appendix: [JPlag](https://github.com/jplag/JPlag) Setup for Offline Code Similarity Check

### Installation

#### 1. Install Java (JDK)

JPlag is Java-based and requires Java 8 or higher.

```bash
sudo apt update
sudo apt install default-jdk
```

#### 2. Clone the JPlag Repository

```bash
git clone https://github.com/jplag/JPlag.git
cd JPlag
```

#### 3. Build JPlag Using Gradle

```bash
./gradlew build
```

The resulting JAR file will be generated at:

```text
build/libs/jplag-<version>.jar
```

### Usage (C/C++ Submissions)

To analyze code similarity across multiple C/C++ submissions:

```bash
java -jar build/libs/jplag-<version>.jar -l c/c++ -r result_dir submissions/
```

#### Parameters

| Flag           | Description                     |
| -------------- | ------------------------------- |
| `-l c/c++`     | Language: C/C++                 |
| `-r result_dir`| Directory to store results      |
| `submissions/` | Root directory of student files |

Example Directory Structure:

```text
submissions/
├── student1/
│   ├── main.cpp
│   └── helper.cpp
├── student2/
│   └── assignment.cpp
├── student3/
│   ├── a.c
│   └── b.c
```

Each student's submission should be placed in a separate folder under `submissions/`.

### Viewing the Results

After execution, JPlag will generate a report in the `result_dir`:

```bash
cd result_dir
xdg-open index.html   # Linux
open index.html       # macOS
```

The HTML report includes:

* Similarity rankings between pairs
* Graphical comparisons with side-by-side highlighting
* Percentage values indicating structural code similarity
