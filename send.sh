#!/bin/bash
while(true)do
first=$(cat /proc/net/dev  | grep eth0 | awk '{print $9}')
sleep 1
last=$(cat /proc/net/dev  | grep eth0 | awk '{print $9}')
echo $[($last - $first)/1024]
done
