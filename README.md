# lecture-notes

A collection of lecture notes, slides, and study materials

## Prerequisite

* [VSCode](https://code.visualstudio.com/download)
* [Docker](https://docs.docker.com/get-started/get-docker/)

## Build `dockerfile`

```shell
docker build \
  --build-arg PASSWORD=docker \
  --build-arg SSH_PUB_KEY="$(cat ~/.ssh/id_rsa.pub)" \
  --build-arg SSH_PRIV_KEY="$(cat ~/.ssh/id_rsa)" \
  --build-arg GIT_NAME="$(git config user.name)" \
  --build-arg GIT_EMAIL="$(git config user.email)" \
  -t marp-dev ./

docker run -p 33221:22 -v ${HOME}/share:/home/docker/share -itd --name marp-dev marp-dev
```

## Access the Container

```shell
code --remote ssh-remote+marp /home/docker/lecture-notes
```

(Opt.) Install `markdownlint` if you want to lint and formatting markdowns:

```shell
code --install-extension DavidAnson.vscode-markdownlint
```
