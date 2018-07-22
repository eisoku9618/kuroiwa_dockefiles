FROM debian:sid-slim

RUN apt update && apt install -y \
clang-format-6.0 \
git \
&& rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]
