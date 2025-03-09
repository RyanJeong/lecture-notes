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
