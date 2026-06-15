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

## Appendix: Building JPlag for C/C++ Only (with Report Viewer) on Ubuntu 22.04

This guide explains how to build and run JPlag for **C/C++ plagiarism detection only**, with the optional **web-based report viewer** enabled.

Unnecessary languages such as Scala, Rust, Go, etc. are skipped by targeting only the required modules. It also covers the **JAVA_HOME / default-JDK setup** that JPlag's build relies on, plus a Maven version recent enough to run on JDK 25.

> **Why JDK 25 matters:** JPlag 6.x compiles with `--release 25`. If Maven runs on an older JDK, the build fails on the very first module with `invalid target release: 25`. The steps below make sure Maven actually runs on JDK 25.

---

### Prerequisites

| Component | Required Version | Notes                                                  |
| --------- | ---------------- | ------------------------------------------------------ |
| Java JDK  | 25               | Required for building **and** running JPlag 6.x        |
| Maven     | 3.9.11           | Recent enough to run reliably on JDK 25                |
| Node.js   | LTS (22.x)       | Required for the report viewer                         |

---

### 1. Install Required Packages

#### Java 25 via Eclipse Temurin

```bash
sudo apt update
sudo apt install -y wget apt-transport-https gnupg

# Import Adoptium GPG key
wget -O - https://packages.adoptium.net/artifactory/api/gpg/key/public \
  | sudo gpg --dearmor -o /usr/share/keyrings/adoptium.gpg

# Add Adoptium repository
echo "deb [signed-by=/usr/share/keyrings/adoptium.gpg] https://packages.adoptium.net/artifactory/deb jammy main" \
  | sudo tee /etc/apt/sources.list.d/adoptium.list

# Install Java 25
sudo apt update
sudo apt install -y temurin-25-jdk
```

#### Make JDK 25 the active toolchain (required)

Installing the package is **not** enough — if another JDK is already the system
default, Maven will still use it. Point `JAVA_HOME` at Temurin 25, set it as the
default, and persist it. The `find` below works on both `amd64` and `arm64`.

```bash
# Resolve the Temurin 25 home (e.g. temurin-25-jdk-amd64 or temurin-25-jdk-arm64)
export JAVA_HOME="$(find /usr/lib/jvm -maxdepth 1 -type d -name 'temurin-25-jdk*' | head -n1)"

# Make it the system default
sudo update-alternatives --install /usr/bin/java  java  "$JAVA_HOME/bin/java"  2000
sudo update-alternatives --install /usr/bin/javac javac "$JAVA_HOME/bin/javac" 2000
sudo update-alternatives --set java  "$JAVA_HOME/bin/java"
sudo update-alternatives --set javac "$JAVA_HOME/bin/javac"

# Persist for future shells
echo "export JAVA_HOME=$JAVA_HOME" >> ~/.bashrc
echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ~/.bashrc
source ~/.bashrc

# Verify — both MUST report 25.x before building
java -version
javac -version
```

#### Install Maven 3.9.11 manually

```bash
# Remove the distro Maven (often too old / tied to the wrong JDK)
sudo apt remove --purge maven -y || true

# Download from the Apache archive (keeps every released version)
wget https://archive.apache.org/dist/maven/maven-3/3.9.11/binaries/apache-maven-3.9.11-bin.tar.gz

# Extract and move to /opt
tar -xzf apache-maven-3.9.11-bin.tar.gz
sudo rm -rf /opt/maven
sudo mv apache-maven-3.9.11 /opt/maven
rm -f apache-maven-3.9.11-bin.tar.gz

# Set environment variables
echo 'export M2_HOME=/opt/maven' >> ~/.bashrc
echo 'export PATH=$M2_HOME/bin:$PATH' >> ~/.bashrc
source ~/.bashrc

# Verify — should report 3.9.11 and "Java version: 25..."
mvn -version
```

#### Node.js (for report viewer)

```bash
sudo apt remove -y nodejs npm || true
curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash -
sudo apt install -y nodejs
```

---

### 2. Clone the Repository

```bash
cd "$HOME"
git clone https://github.com/jplag/jplag.git
cd jplag
```

---

### 3. Build Only Required Modules (C/C++ with Viewer)

> Before building, confirm `mvn -version` lists **Java version: 25**. If it shows
> an older version, revisit the "Make JDK 25 the active toolchain" step — otherwise
> the build fails with `invalid target release: 25`.

```bash
mvn -P with-report-viewer clean package assembly:single \
  -pl cli,core,language-api,language-antlr-utils,languages/c,languages/cpp \
  -am \
  -DskipTests
```

| Option                  | Description                                               |
| ----------------------- | --------------------------------------------------------- |
| `-P with-report-viewer` | Enables the web-based report viewer                       |
| `-pl`                   | Selects only the required modules explicitly              |
| `-am`                   | Also builds all required dependencies of selected modules |
| `-DskipTests`           | Skips tests to speed up the build                         |

---

### 4. Run JPlag for C/C++

After a successful build, the runnable JAR is located at:

```text
cli/target/jplag-*-jar-with-dependencies.jar
```

The language identifiers are **separate**: use `cpp` for C++ and `c` for C
(the old combined `c/c++` / `c_cpp` value no longer exists).

#### Example usage (C++)

```bash
java -jar cli/target/jplag-*-jar-with-dependencies.jar \
  -l cpp \
  -r ./report \
  ./submissions
```

For C, replace `-l cpp` with `-l c`. The submissions directory is passed as a
positional argument; `-r` sets the result file (a `.jplag` archive).

Run the JAR with `-h` to list all options, or with no arguments to open the
bundled report viewer directly:

```bash
java -jar cli/target/jplag-*-jar-with-dependencies.jar -h
java -jar cli/target/jplag-*-jar-with-dependencies.jar        # opens the viewer
```
