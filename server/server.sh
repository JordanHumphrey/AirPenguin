#!/bin/bash

gcc ./main.c -o AirPenguin
while :
do
    killall AirPenguin > /dev/null 2>&1
    echo "Waiting for a connection"
    IP="$(./AirPenguin)"
    echo $IP " wants to stream to this cast"
    for count in 1 2 3 4 5 6 7 8 9 10
    do
	sleep 0.1
        omxplayer -o hdmi rtsp://@$IP/peng.sdp > /dev/null 2>&1 #output hack
    done
done
