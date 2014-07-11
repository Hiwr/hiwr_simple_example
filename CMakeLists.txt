cmake_minimum_required(VERSION 2.8.3)
project(hiwr_simple_example)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  rospack
  sensor_msgs
  tf
  hyve_msg
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs rospack hyve_msg
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

link_directories(/opt/ros/groovy/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++0x -pthread -pg")

add_executable(hiwr_simple_example src/hiwr_simple_example.cpp)
target_link_libraries(hiwr_simple_example ${catkin_LIBRARIES})
