FROM ubuntu:18.04

RUN apt update

# for build
RUN apt install -y build-essential cmake git zlib1g-dev

# for eigen
RUN apt install -y libeigen3-dev

# for gtest
RUN apt install -y libgtest-dev

# for coin-or
RUN apt install -y coinor-libclp-dev coinor-clp

# for clang and include-what-you-use
RUN apt install -y clang iwyu

CMD ["/bin/bash"]
