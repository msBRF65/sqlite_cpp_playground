FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y wget

ARG USER_NAME=dev
ARG PROJECT_NAME=sqlite_cpp_playground
ARG APPLICATION_DIRECTORY=/home/${USER_NAME}/${PROJECT_NAME}

RUN wget -qO- "https://cmake.org/files/v3.20/cmake-3.20.2-linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    clang \
    clang-format \
    vim \
    git \
    ninja-build \
    gdb \
    python3-pip \
    libsqlite3-dev 

RUN useradd -ms /bin/sh ${USER_NAME}
RUN chown -R ${USER_NAME} /home/${USER_NAME}
USER ${USER_NAME}

RUN cp /usr/share/bash-completion/completions/git /home/${USER_NAME}/.git-completion.bash
RUN echo "source ~/.git-completion.bash" >> ~/.bashrc
