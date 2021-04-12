#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <mavros_msgs/SetMode.h>

sensor_msgs::Imu imu;

void imu_cb(const sensor_msgs::Imu::ConstPtr& msg)
{
    imu = *msg;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "mavros_ex");
    ros::NodeHandle nh;

    ros::Subscriber imu_sub = nh.subscribe<sensor_msgs::Imu>("/mavros/imu/data", 1, imu_cb);
    ros::ServiceClient mode_client = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");

    ros::Rate loop_rate(100);
    mavros_msgs::SetMode mode;

    while(ros::ok()){
        ROS_INFO("z = %lf", imu.linear_acceleration.z);
        if(imu.linear_acceleration.z < 3){
            mode.request.custom_mode = "GUIDED";
            mode_client.call(mode);
            ROS_INFO("mode : GUIDED");
        } else {
            mode.request.custom_mode = "AUTO";
            mode_client.call(mode);
            ROS_INFO("mode : AUTO");
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}