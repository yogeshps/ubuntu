#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
//#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>

ros::Publisher pub1;
ros::Publisher pub2;

typedef pcl::PointCloud<pcl::PointXYZ> pc;

void 
cloud_cb1 (const pc::ConstPtr &input)
{
  // Create a container for the data.
  pc output;

  // Do data processing here...
  output = *input;

  // Publish the data.
  pub1.publish (output);
}

void 
cloud_cb2 (const pc::ConstPtr &input)
{
  // Create a container for the data.
  pc output;

  // Do data processing here...
  output = *input;

  // Publish the data.
  pub2.publish (output);
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "example");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub1 = nh.subscribe<pc> ("/camera1/depth/points", 1, cloud_cb1);
  ros::Subscriber sub2 = nh.subscribe<pc> ("/camera2/depth/points", 1, cloud_cb2);

  // Create a ROS publisher for the output point cloud
  pub1 = nh.advertise<pc> ("output1", 1);
  pub2 = nh.advertise<pc> ("output2", 1);


  // Spin
  ros::spin ();
}