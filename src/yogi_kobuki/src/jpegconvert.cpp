#ifndef byte
typedef unsigned char byte;
#endif

// Note: For Asus Xtion or Kinect 2, SensorMaxDepth = 5.0f (5 meters)
void  ConvertPCL2Depth8(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud2,
cv::Mat &OutputImage, float SensorMaxDepth)
{
    OutputImage.create(cloud2->height,cloud2->width,CV_8UC1); // Create byte array.

    for(int i=0;i<cloud2->height;i++)
        for(int j=0;j<cloud2->width;j++)
        {
            float depth_f = cloud2->at(j,i).z;
            depth_f = (depth_f/SensorMaxDepth)*255.0f; // Converting the distance to byte (unsigned char).
            if(depth_f>255.0) depth_f = 255.0
            byte depth_8 = (unsigned char) depth_f;
            OutputImage.at<byte>(i,j) = depth_8;
        }

}