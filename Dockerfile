FROM ubuntu:xenial

RUN apt-get update && apt-get install -y texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-fonts-extra texlive-lang-cjk texlive-xetex texlive-bibtex-extra texlive-science texlive-pictures pgf fonts-lmodern build-essential python3

CMD ["/bin/bash"]
