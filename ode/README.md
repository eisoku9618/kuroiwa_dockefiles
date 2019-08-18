## aptではダメなのか？
aptで入るODEだと描画ライブラリであるdrawstuffがインストールされないため

## dockerでGUIを表示できるのか？
https://qiita.com/eisoku9618/items/c2cca0f0bf764def2efd にやり方が書いてある

## sample

```bash
docker build . -f ode_dockerfile -t ode
xhost +
docker run --rm -it --env="DISPLAY" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" -v $(pwd)/sample:/root/ws -w /root/ws ode
mkdir build
cmake -Bbuild -H.
make -C build
./build/2dof_arm
```
