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
Unnecessary languages such as Scala, Rust, Go, etc. are skipped by targeting only required modules. It also includes steps to install **Maven 3.9.6**, which is required for compatibility with `scala-maven-plugin:4.9.5`.

---

### Prerequisites

| Component | Required Version | Notes                                   |
| --------- | ---------------- | --------------------------------------- |
| Java JDK  | 21               | Required for building and running JPlag |
| Maven     | 3.8.1 or later   | Required for Scala plugin compatibility |
| Node.js   | LTS              | Required for the report viewer          |

---

### 1. Install Required Packages

#### Java 21 via Eclipse Temurin

```bash
sudo apt update
sudo apt install -y wget apt-transport-https gnupg

# Import Adoptium GPG key
wget -O - https://packages.adoptium.net/artifactory/api/gpg/key/public | sudo gpg --dearmor -o /usr/share/keyrings/adoptium.gpg

# Add Adoptium repository
echo "deb [signed-by=/usr/share/keyrings/adoptium.gpg] https://packages.adoptium.net/artifactory/deb jammy main" | sudo tee /etc/apt/sources.list.d/adoptium.list

# Install Java 21
sudo apt update
sudo apt install -y temurin-21-jdk
```

#### Install Maven 3.9.6 manually

```bash
# Remove old Maven
sudo apt remove --purge maven -y

# Download and install Maven 3.9.6
wget https://downloads.apache.org/maven/maven-3/3.9.6/binaries/apache-maven-3.9.6-bin.tar.gz

# Extract and move to /opt
tar -xzf apache-maven-3.9.6-bin.tar.gz
sudo mv apache-maven-3.9.6 /opt/maven

# Set environment variables
echo 'export M2_HOME=/opt/maven' >> ~/.bashrc
echo 'export PATH=$M2_HOME/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

#### Node.js (for report viewer)

```bash
sudo apt remove -y nodejs npm
curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash -
sudo apt install -y nodejs
```

---

### 2. Clone the Repository

```bash
git clone https://github.com/jplag/jplag.git
cd jplag
```

---

### 3. Build Only Required Modules (C/C++ with Viewer)

```bash
mvn -P with-report-viewer clean package assembly:single \
  -pl cli,core,languages,language-api,language-antlr-utils \
  -am \
  -DskipTests
```

| Option                  | Description                                               |
| ----------------------- | --------------------------------------------------------- |
| `-P with-report-viewer` | Enables the web-based report viewer                       |
| `-pl`                   | Selects only required modules explicitly                  |
| `-am`                   | Also builds all required dependencies of selected modules |
| `-DskipTests`           | Skips tests to speed up the build                         |

---

### 4. Run JPlag for C/C++

After a successful build, the runnable JAR will be located at:

```text
cli/target/jplag-*-jar-with-dependencies.jar
```

#### Example usage

```bash
java -jar cli/target/jplag-*-jar-with-dependencies.jar \
  -l c/c++ \
  -s ./submissions \
  -r ./report
```
