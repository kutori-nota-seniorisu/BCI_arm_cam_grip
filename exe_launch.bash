#!/bin/bash
roslaunch online_analysis ana_simu.launch &
#sleep 0.1
#rosrun online_analysis chatpub.py &
#rosrun online_analysis onlineanalysis.py
echo "Analysis Simulate start success!"
wait
exit 0
