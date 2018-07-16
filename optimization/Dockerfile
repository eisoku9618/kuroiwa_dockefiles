FROM ubuntu:18.04

RUN apt update && apt install -y \
# for build
build-essential cmake git zlib1g-dev \
# for eigen
libeigen3-dev \
# for gtest
libgtest-dev \
# for coin-or
coinor-libclp-dev coinor-clp \
# for clang and include-what-you-use
clang iwyu \
&& rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]
