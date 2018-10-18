#!/bin/bash
set -e

# setup ros environment
source "~/catkin_ws/indigo/devel/setup.bash"
exec "$@"
