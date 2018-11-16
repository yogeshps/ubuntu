#! /usr/bin/env python

import rospy
from sensor_msgs.msg import Joy 
from geometry_msgs.msg import Twist
from std_msgs.msg import String
import time

# Remember to keep joystick in X mode and not in D mode
pub = rospy.Publisher('/mobile_base/commands/velocity', Twist, queue_size=10)

def callback(msg): 
	global move
	print move
 	rospy.loginfo("Sending message through joystick\n") #Just a message to the screen to see if joystick works

	up_down_stick = 4
	left_right_stick = 0
	RB = 5
		
	# If the forward or backward value is beyond a certain threshold, then move	else stop
	if ((msg.axes[up_down_stick]*0.35 >= 0.12) or (msg.axes[up_down_stick]*0.35 <= -0.12)):
		print "Got from up-down stick\n"
		move.linear.x = msg.axes[up_down_stick]*(0.35)
		move.angular.z = 0.0

	# If the left or right value is beyond a certain threshold, then move else stop
	elif ((msg.axes[left_right_stick]*1.3 >= 0.3) or (msg.axes[left_right_stick]*1.3 <= -0.3)):
		print "Got from left-right stick\n"
		move.linear.x = 0.0
		move.angular.z = msg.axes[left_right_stick]*1.3

	#In any other case i.e either no buttons are pressed, or threshold motor value is not reached then just stop	
	else:
		move.linear.x = 0.0
		move.angular.z = 0.0

	pub.publish(move)

def move_kobuki():
	global move
	rospy.init_node('joystick_kobuki_node',anonymous=True)
	sub = rospy.Subscriber('/joy', Joy, callback) #We subscribe to the joystick's topic
	move = Twist()	
	rospy.spin()

if __name__ == '__main__':
	try:
		move_kobuki()
	except rospy.ROSInterruptException:
		pass


