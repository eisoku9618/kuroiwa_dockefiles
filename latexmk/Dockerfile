FROM ubuntu:19.10

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y --no-install-recommends \
# for (u)platex
texlive-lang-japanese \
# for CTAN packages
texlive-plain-generic texlive-latex-base texlive-latex-extra \
# for latexmk
latexmk \
# for noto font: Bold and Regular
fonts-noto-cjk \
# for noto font: Black, DemiLight, Light, Medium, Thin and so on
fonts-noto-cjk-extra \
# for extra fonts
texlive-fonts-recommended \
# for Awesome CV: https://github.com/posquit0/Awesome-CV
texlive-fonts-extra \
texlive-xetex fonts-font-awesome fonts-roboto fontconfig \
&& rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]
