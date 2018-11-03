#! /usr/bin/env python

import rosbag
import rospy
import roslib
import sys
roslib.load_manifest('dl')

print ('hello')

bag = rosbag.Bag('/home/astar/bagfiles/computer.bag')
for topic, msg, t in bag.read_messages(topics=['joy']):
    print (msg)
bag.close()
