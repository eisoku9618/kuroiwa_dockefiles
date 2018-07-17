FROM ubuntu:18.04

# for tex
ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y \
# for tex
texlive-latex-extra texlive-fonts-recommended texlive-lang-japanese fonts-lmodern \
# for latexmk
latexmk \
# for noto font
fonts-noto-cjk fonts-noto-cjk-extra \
git \
&& rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/vvakame/docker-review.git \
&& mv docker-review/noto /usr/share/texlive/texmf-dist/fonts/map/dvipdfmx/ptex-fontmaps/ \
&& rm -rf docker-review \
&& mktexlsr && kanji-config-updmap-sys noto

CMD ["/bin/bash"]
