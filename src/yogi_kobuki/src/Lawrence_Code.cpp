#include <iostream>
#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
//#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
//#include <opencv/cv.h>
//#include <opencv2/core/mat.hpp>
#include <opencv-3.3.1-dev/opencv2/core/mat.hpp>
//#include <pcl/io/pcd_io.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_ros/io/pcd_io.h>


ros::Publisher pub1;
//ros::Publisher pub2;

typedef pcl::PointCloud<pcl::PointXYZ> pc;

void 
cloud_cb1 (const pc::ConstPtr &input)
{
  // Create a container for the data.
  pc::Ptr output(new pcl::PointCloud<pcl::PointXYZ>);
  pc::Ptr output_filtered(new pcl::PointCloud<pcl::PointXYZ>);

  // Do data processing here...
  *output = *input; //already fed data from pointcloud to output
  std::cerr << "Cloud before filtering: " << std::endl;
  std::cerr << *output << std::endl;

  // Create the filtering object
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
  sor.setInputCloud (output);
  sor.setMeanK (50);
  sor.setStddevMulThresh (1.0);
  sor.filter (*output_filtered);

  std::cerr << "Cloud after filtering: " << std::endl;
  std::cerr << *output_filtered << std::endl;

  // Publish the data.
  pub1.publish (*output_filtered);
}

/*void 
cloud_cb2 (const pc::ConstPtr &input)
{
  // Create a container for the data.
  pc output;

  // Do data processing here...
  output = *input;

  // Publish the data.
  pub2.publish (output);
}*/

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "Lawrence_Code");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub1 = nh.subscribe<pc> ("/camera/depth/points", 1, cloud_cb1);
  //ros::Subscriber sub2 = nh.subscribe<pc> ("/camera2/depth/points", 1, cloud_cb2);

  // Create a ROS publisher for the output point cloud
  pub1 = nh.advertise<pc> ("output1", 1);
  //pub2 = nh.advertise<pc> ("output2", 1);


  // Spin
  ros::spin ();
}