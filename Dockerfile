ARG UBUNTU_VERSION="22.04"

FROM ubuntu:${UBUNTU_VERSION}

ARG USER="docker"
ARG PASSWORD="docker"
ARG USER_HOME="/home/${USER}"

ARG SSH_PUB_KEY
ARG SSH_PRIV_KEY

RUN if [ -z "${SSH_PUB_KEY}" ]; then echo "Error: SSH_PUB_KEY is not set" && exit 1; fi
RUN if [ -z "${SSH_PRIV_KEY}" ]; then echo "Error: SSH_PRIV_KEY is not set" && exit 1; fi

ARG GIT_NAME
ARG GIT_EMAIL

RUN if [ -z "${GIT_NAME}" ]; then echo "Error: GIT_NAME is not set" && exit 1; fi
RUN if [ -z "${GIT_EMAIL}" ]; then echo "Error: GIT_EMAIL is not set" && exit 1; fi

SHELL ["/bin/bash", "-c"]

# Replace default servers with Korea servers
RUN sed -i 's/archive.ubuntu.com/mirror.kakao.com/g' /etc/apt/sources.list

# to skip prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# package install
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
      openssh-server \
      gcc \
      g++ \
      git \
      wget \
      curl \
      git \
      vim \
      vim-gtk

# add a user and make a home directory
RUN useradd -d "${USER_HOME}" -m "${USER}" && \
    echo "${USER}:${PASSWORD}" | chpasswd && \
    usermod -aG sudo "${USER}"

# setup SSH and settings
WORKDIR "${USER_HOME}/.ssh"
RUN mkdir -p /run/sshd && \
    sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin no/' /etc/ssh/sshd_config && \
    sed -i 's/#PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config && \
    sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/' /etc/ssh/sshd_config && \
    echo "${SSH_PRIV_KEY}" > id_rsa && \
    chmod 600 id_rsa && \
    ssh-keyscan github.com >> known_hosts && \
    chmod 600 known_hosts && \
    echo "${SSH_PUB_KEY}" > authorized_keys && \
    chmod 600 authorized_keys && \
    chown -R ${USER}:${USER} ${USER_HOME}/.ssh && \
    chmod 700 ${USER_HOME}/.ssh

# set a default shell
RUN sed -i 's:/bin/sh:/bin/bash:g' /etc/passwd

# clang-format
WORKDIR "${USER_HOME}"
RUN apt install -y lsb-release wget software-properties-common gnupg && \
    wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh 19 && \
    apt install -y clang-format-19 && \
    update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-19 100 && \
    update-alternatives --set clang-format /usr/bin/clang-format-19

# marp-cli (depends on node.js)
WORKDIR "${USER_HOME}"
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    DEBIAN_FRONTEND=noninteractive && \
    apt-get update && \
    apt-get install -y nodejs && \
    npm install -g npm && \
    npm install -g @marp-team/marp-cli && \
    marp --version

# vim
WORKDIR "${USER_HOME}"
RUN echo $'set number\n\
syntax on\n\
set softtabstop=2\n\
set tabstop=2\n\
set shiftwidth=2\n\
set expandtab\n\
colorscheme desert\n\
\n\
filetype indent on\n\
filetype plugin indent on\n\
\n\
if system("uname -s") == "Darwin"\n\
set clipboard=unnamed "OSX\n\
else\n\
set clipboard=unnamedplus "Linux\n\
endif \n\
' >> .vimrc

#### To complete some configurations
USER "${USER}"

# set Git
RUN git config --global user.name "${GIT_NAME}" && \
    git config --global user.email "${GIT_EMAIL}"

WORKDIR "${USER_HOME}"
RUN git clone git@github.com:RyanJeong/clang-format.git

#### To be able to run SSH
USER root

# cleanup
WORKDIR "${USER_HOME}"
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

CMD ["/usr/sbin/sshd", "-D"]
