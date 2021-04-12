#include <ros/ros.h>
#include <ros_tutorials_ex/MsgTutorial.h>
#include <ros_tutorials_ex/SrvTutorial.h>

ros_tutorials_ex::MsgTutorial msg;

bool calculation(ros_tutorials_ex::SrvTutorial::Request &req, ros_tutorials_ex::SrvTutorial::Response &res)
{
    res.result = req.a + req.b;
    msg.data = res.result;
    ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: [%ld]", (long int)res.result);
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tutorials_ex");
    ros::NodeHandle nh;

    ros::ServiceServer ros_tutorials_service_server = nh.advertiseService("ros_tutorials_srv", calculation);;
    ros::Publisher ros_tutorials_topic_publisher = nh.advertise<ros_tutorials_ex::MsgTutorial>("ros_tutorials_msg", 1);

    ros::Rate loop_rate(10);

    while (ros::ok()){
        msg.stamp = ros::Time::now();
        ROS_INFO("send msg = %d", msg.stamp.sec);
        ROS_INFO("send msg = %d", msg.stamp.nsec);
        ROS_INFO("send msg = %d", msg.data);
        ros_tutorials_topic_publisher.publish(msg);
        ros::spinOnce();
        loop_rate.sleep(); 
    }
    return 0;
}