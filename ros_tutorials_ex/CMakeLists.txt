cmake_minimum_required(VERSION 3.0.2)
project(ros_tutorials_ex)

find_package(catkin REQUIRED COMPONENTS message_generation roscpp std_msgs)

add_message_files(FILES MsgTutorial.msg)

add_service_files(FILES SrvTutorial.srv)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(LIBRARIES ros_tutorials_ex CATKIN_DEPENDS roscpp std_msgs)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(ros_tutorials_ex src/ros_tutorials_ex_node.cpp)

add_dependencies(ros_tutorials_ex ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(ros_tutorials_ex ${catkin_LIBRARIES})
