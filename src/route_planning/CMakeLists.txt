cmake_minimum_required(VERSION 2.8.3)
project(route_planning)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
	roscpp
	geometry_msgs
	visualization_msgs
	std_msgs
	message_generation
)

catkin_package(
  	INCLUDE_DIRS src
	CATKIN_DEPENDS roscpp visualization_msgs geometry_msgs message_runtime
)

include_directories(${catkin_INCLUDE_DIRS})

add_library(Astar src/Astar.cpp  src/Astar.h )
target_link_libraries(Astar ${catkin_LIBRARIES})
add_dependencies(Astar ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(basic_shapes src/basic_shapes.cpp)
target_link_libraries(basic_shapes  Astar ${catkin_LIBRARIES})

add_executable(obstacle_talker src/obstacle_talker.cpp)
target_link_libraries(obstacle_talker Astar ${catkin_LIBRARIES})
