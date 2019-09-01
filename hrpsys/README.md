## preparation in local machine

```bash
xhost +
```

## run docker container
```bash
# docker build -t eisoku9618/kuroiwa_dockefiles_for_hrpsys .
docker run --rm -it --env="DISPLAY" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" --name hrpsys eisoku9618/kuroiwa_dockefiles_for_hrpsys
byobu-screen
```

## preparation 2 in local machine
```bash
docker cp impedance-test.py hrpsys:/tmp/
```

```bash
. /opt/ros/indigo/setup.sh
roslaunch hrpsys samplerobot.launch
```

```bash
. /opt/ros/indigo/setup.sh
ipython -i /tmp/impedance-test.py
```
