# lecture-notes
A collection of lecture notes, slides, and study materials

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

code --remote ssh-remote+marp /home/docker/lecture-notes
```
