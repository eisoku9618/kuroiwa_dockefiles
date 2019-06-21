## setup environment

```bash
export DISTRO=melodic
docker build --build-arg DISTRO=$DIRSTO -t model_check:$DIRSTO .
```

### outside docker (local)

```bash
xhost +
```

### inside docker

```bash
docker run --runtime=nvidia --rm -it --env="DISPLAY" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" model_check:$DIRSTO
```

```bash
source /root/catkin_ws/devel/setup.bash
```

## model format conversion step

1. xacro -> urdf
2. urdf -> dae
3. dae -> lisp

```bash
rosrun xacro xacro `rospack find pr2_description`/robots/pr2.urdf.xacro > pr2.urdf
rosrun collada_urdf urdf_to_collada pr2.urdf pr2.dae
rosrun euscollada collada2eus pr2.dae pr2.l
```

## visualization (urdf)

```bash
roslaunch urdf_tutorial display.launch model:=pr2.urdf
```

## mass property calculation (lisp)

```bash
roseus pr2.l
(progn
  (setq *robot* (pr2))
  (objects (list *robot*))
  (format t "weight: ~A [kg]~%centroid: ~A [m]~%inertia-tensor: ~A [kgm^2]~%"
          (* 1e-3 (send *robot* :weight))
          (scale 1e-3 (send *robot* :centroid))
          (m* (make-matrix 3 3 (list (list 1e-9 0 0) (list 0 1e-9 0) (list 0 0 1e-9))) (send *robot* :inertia-tensor))))
```

## generate a combined STL (lisp)

```bash
roseus pr2.l
(progn
  (load "package://eus_assimp/euslisp/eus-assimp.l")
  (setq *robot* (pr2))
  (let (glv-lst)
    (dolist (bd (send *robot* :bodies))
      (let (glv)
        (cond
         ((and (boundp 'gl::glbody) (classp gl::glbody) (derivedp bd gl::glbody))
          (setq glv (send bd :glvertices)))
         (t (setq glv (cdr (assoc 'glvertices (send bd :slots))))))
        (when glv (push glv glv-lst))))
    (apply #'save-mesh-file "pr2.stl" (append-glvertices glv-lst :use-coordinate t) nil)))
```
