# 環境構築
```bash
docker pull eisoku9618/kuroiwa_dockefiles_for_movie_editor
```

# 動画編集
https://qiita.com/eisoku9618/items/df7bc082545cf70cc724 が詳しい．
ここでは代表的なコマンドを記載する．

## docker containerの起動
まずは，比較的新し目のffmpegが入っているdocker containerを起動し，対象の動画を含むディレクトリをマウントする．

```bash
docker run --rm -it -v `pwd`:/home/ -w /home/ eisoku9618/kuroiwa_dockefiles_for_movie_editor /bin/ash
```

## 代表的なffmpegコマンド
- ``ffmpeg -i input.mp4 -c:v hevc -c:a aac -strict -2 output.mp4``
   - HEVC/AACでエンコードする
- ``ffmpeg -i input.mp4 -c:v h264 -preset slow -tune film -an output.mp4``
   - H264/音無しでエンコードする
- ``ffmpeg -ss 2 -i input.mp4 -t 5 -c:v h264 -preset slow -tune film -an output.mp4``
   - 2秒目から5秒間を対象にH264/音無しでエンコードする
- ``ffmpeg -i input.mp4 -c:v h264 -preset slow -tune film -filter:v "crop=in_w/3*1:in_h:in_w/3*1:0" -an output.mp4``
   - サイズの切り取り
- ``ffmpeg -i in_1.mp4 -i in_2.mp4 -i in_3.mp4 -filter_complex "[0:0]pad=iw:3*ih[a];[a][1:0]overlay=0:h[b];[b][2:0]overlay=0:2*h" output.mp4``
   - 複数の動画を縦に結合して1つの動画にする
- ``ffmpeg -i in_1.mp4 -i in_2.mp4 -filter_complex "concat=n=2:v=1:a=0" output.mp4``
   - 複数の動画を時間方向に連結して1つの動画にする
- ``ffmpeg -i input.mp4 -c:v h264 -preset slow -tune film -an -filter:v "setpts=1/2*PTS" output.mp4``
   - 動画を倍速にする
      - 以下のように文字を入れるには``--enable-libfreetype``付きでビルドされているffmpegが必要であり，残念ながらalpineのapkで入るffmpegはそのオプションが付いていない模様．．．
         - https://stackoverflow.com/a/48037936
         - ``ffmpeg -i input.mp4 -c:v h264 -preset slow -tune film -an -filter:v "setpts=1/2*PTS, drawtext=text='2x':x=0:y=0:fontsize=100:fontcolor=white:box=1:boxcolor=black@0.5" output.mp4``
