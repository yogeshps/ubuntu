#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
//#include <pcl/point_cloud.h>
#include <pcl-1.7/pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <iostream.h>
//#include <pcl/point_types.h>
#include <pcl-1.7/pcl/filters/passthrough.h>

ros::Publisher pub1;

typedef pcl::PointCloud<pcl::PointXYZ> pc;
typedef pcl::PointCloud<pcl::PointXYZ> pc_filtered;

void 
cloud_cb1 (const pc::ConstPtr &input)
{
  // Create a container for the data.
  pc output;
  pc output_filtered;

  // Do data processing here...
  output = *input;
    // Create the filtering object
  pcl::PassThrough<pcl::PointXYZ> pass;
  pass.setInputCloud (output);
  pass.setFilterFieldName ("x");  
  pass.setFilterLimits (0.85, 1.35);
  //pass.setFilterLimitsNegative (true);
  pass.filter (*output_filtered);



  // Publish the data.
  pub1.publish (output_filtered);
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "example");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub1 = nh.subscribe<pc> ("/camera/depth/points", 1, cloud_cb1);

  // Create a ROS publisher for the output point cloud
  pub1 = nh.advertise<pc> ("filtered", 1);

  // Spin
  ros::spin ();
}