#include "ros/ros.h"
#include "mavros_msgs/State.h"
#include "mavros_msgs/SetMode.h"

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_mavros_node");
    ros::NodeHandle nh;

    ros::Subscriber state_mode = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
    ros::ServiceClient mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    ros::Rate rate(100);

    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    int count = 0;
    while(ros::ok()){
        ++count;
        mavros_msgs::SetMode set_mode;
        if(count >= 100 ){
            if(current_state.mode != "AUTO"){
                set_mode.request.custom_mode = "AUTO";
                mode_client.call(set_mode);
                ROS_INFO("mode : AUTO");
            } else if(current_state.mode != "GUIDED"){
                set_mode.request.custom_mode = "GUIDED";
                mode_client.call(set_mode);
                ROS_INFO("mode : GUIDED");
            }
            count = 0;
        }
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}