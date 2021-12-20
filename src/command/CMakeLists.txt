cmake_minimum_required(VERSION 3.0.2)
project(command)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	geometry_msgs
	visualization_msgs
	std_msgs
	message_generation
)

add_message_files(FILES turn.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES command
  CATKIN_DEPENDS roscpp visualization_msgs geometry_msgs message_runtime
#  DEPENDS system_lib
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(cmdvel src/cmdvel.cpp)
target_link_libraries(cmdvel ${catkin_LIBRARIES})

add_executable(skeyboard src/skeyboard.cpp)
target_link_libraries(skeyboard ${catkin_LIBRARIES})