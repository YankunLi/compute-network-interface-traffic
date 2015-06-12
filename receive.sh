#!/bin/bash
while(true)do
first=$(cat /proc/net/dev  | grep eth0 | awk '{print $1}' | awk -F ':' '{print $2}')
sleep 1
last=$(cat /proc/net/dev  | grep eth0 | awk '{print $1}' | awk -F ':' '{print $2}')
echo $[($last - $first)/1024]
done
