FROM ubuntu:18.04

LABEL com.nvidia.volumes.needed="nvidia_driver"
ENV PATH /usr/local/nvidia/bin:${PATH}
ENV LD_LIBRARY_PATH /usr/local/nvidia/lib:/usr/local/nvidia/lib64:${LD_LIBRARY_PATH}

WORKDIR /tmp/

RUN apt update

# ODEのソースコードをダウンロードする
RUN apt install -y --no-install-recommends mercurial ca-certificates
RUN mkdir ode && cd ode && hg init && hg pull https://bitbucket.org/odedevs/ode && hg update default

# bootstrapプログラムを実行する
RUN apt install -y --no-install-recommends automake autoconf libtool
RUN cd /tmp/ode && ./bootstrap

# configureプログラムを実行し，makeする
RUN apt install -y --no-install-recommends freeglut3-dev libglew-dev xorg-dev g++ make
RUN cd /tmp/ode && ./configure --enable-double-precision --enable-ou --enable-libccd --with-drawstuff=X11 \
&& make -j`nproc` && make install

# drawstuffは手動でインストールする
RUN cd /tmp/ode \
&& cp -r include/drawstuff /usr/local/include/ \
&& cp drawstuff/src/.libs/libdrawstuff.* /usr/local/lib \
&& ldconfig

# 自前プログラムでcmakeを使うのでインストールしておく
RUN apt install -y --no-install-recommends cmake

RUN rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]
