#include <iostream>
#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
//#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>

//#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

ros::Publisher pub1;

typedef pcl::PointCloud<pcl::PointXYZ> pc;

void 
cloud_cb1 (const pc::ConstPtr &input)
{
  // Create a container for the data.
  pc output, output_f;
  pc *outputptr;
  pc *output_filtered;

  // Do data processing here...
  output = *input;
  outputptr=&output;
  output_f=output;
  output_filtered=&output_f;

  /*float size_str;
  size_str=sizeof(outputptr)/sizeof(outputptr[0]);
  ROS_INFO("%f",size_str);*/
  
  // Create the filtering object
  pcl::PassThrough<pcl::PointXYZ> pass;
  pass.setInputCloud((pc::Ptr)outputptr);
  pass.setFilterFieldName ("y");  
  pass.setFilterLimits (-1.0, 1.0);
  //pass.setFilterLimitsNegative (true);
  pass.filter (*output_filtered);
  
  // Publish the data.
  pub1.publish (output);
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "ros_pcl_yogi");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub1 = nh.subscribe<pc> ("/camera/depth/points", 1, cloud_cb1);

  // Create a ROS publisher for the output point cloud
  pub1 = nh.advertise<pc> ("filtered", 1);

  // Spin
  ros::spin ();
}