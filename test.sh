#!/bin/bash

Xephyr -br -ac -reset -screen 3840x2160 :1 &
sleep 1s
export DISPLAY=:1
setbg &
./dwm
