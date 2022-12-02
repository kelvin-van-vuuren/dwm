#!/bin/bash

Xephyr -br -ac -reset -screen 3840x2160 :1 &
# Xephyr +xinerama -br -reset -screen 1920x1080 -screen 1920x1080 -ac :1 &
sleep 1s
export DISPLAY=:1
setbg &
./dwm
