#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/LaserScan.h>
#include <math.h>

ros::Publisher distance_pub;
ros::Subscriber distance_sub;

void scanCallback(const sensor_msgs::LaserScanPtr &scan)
{
      std_msgs::Float32 distance;
      distance.data = scan->range_max;
      float angle = scan->angle_min;
      float x,y;
      for(int i = 0;angle <= scan->angle_max;i++){
        x = scan->ranges[i]*sin(angle);
        y = scan->ranges[i]*cos(angle);
        if(fabs(x) < 0.25 && y < distance.data && y >0)
          distance.data = y;
        angle += scan->angle_increment;
      }
      
      distance_pub.publish(distance);
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "obstacles_dis_pubshilher");
    
    ros::NodeHandle n;
    distance_pub = n.advertise<std_msgs::Float32>("ob_distance", 1);
    distance_sub = n.subscribe("scan",1,scanCallback);
    ros::Rate r(1.0);

    while(n.ok()){
      ros::spinOnce();
      r.sleep();
    }

}
