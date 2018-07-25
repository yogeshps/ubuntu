#! /usr/bin/env python

import rospy
from sensor_msgs.msg import Joy 
from geometry_msgs.msg import Twist
from std_msgs.msg import String
import time

pub = rospy.Publisher('/mobile_base/commands/velocity', Twist, queue_size=10)

def callback(msg): 
	global move
	print move
 	rospy.loginfo("Sending message through joystick\n") #Just a message to the screen to see if joystick works
	global turn_speed
	global trans_speed
	global a
	a = 1
	A = 0
	B = 1
	X = 2
	Y = 3
	up_down_stick = 4
	left_right_stick = 0
	RB = 5
		
	if msg.axes[up_down_stick] != 0.0:
		print "Got from up-down stick\n"
		move.linear.x = msg.axes[up_down_stick]*(0.35)
		move.angular.z = 0.0
	elif msg.axes[left_right_stick] != 0.0:
		print "Got from left-right stick\n"
		move.linear.x = 0.0
		move.angular.z = msg.axes[left_right_stick]*0.9
	elif msg.buttons[RB] == 1.0:
		move.linear.x = 0.0
		move.angular.z = 0.0				
	else:
		z = 1

	pub.publish(move)

def move_kobuki():
	global move
	global turn_speed
	turn_speed = 0.0
	global trans_speed
	trans_speed = 0.0
	global a
	a = 1
	rospy.init_node('joystick_kobuki_node',anonymous=True)
	sub = rospy.Subscriber('/joy', Joy, callback) #We subscribe to the joystick's topic
	move = Twist()	
	rospy.spin()

if __name__ == '__main__':
	try:
		move_kobuki()
	except rospy.ROSInterruptException:
		pass


