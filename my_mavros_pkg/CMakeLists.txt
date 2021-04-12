cmake_minimum_required(VERSION 3.0.2)
project(my_mavros_pkg)

find_package(catkin REQUIRED COMPONENTS
  mavros_msgs
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES my_mavros_pkg
  CATKIN_DEPENDS mavros_msgs roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# includes
  ${catkin_INCLUDE_DIRS}
)

add_executable(my_mavros_node src/my_mavros_node.cpp)
target_link_libraries(my_mavros_node
  ${catkin_LIBRARIES}
)
