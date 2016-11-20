cmake_minimum_required(VERSION 3.5)

project(time)

if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rmw REQUIRED)
find_package(rmw_implementation_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)

include_directories(include)

add_library(time src/Time.cpp)
ament_target_dependencies(time rclcpp builtin_interfaces)
add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp)
target_link_libraries(listener time)
add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp builtin_interfaces)
target_link_libraries(talker time)
install(
    TARGETS listener
    RUNTIME DESTINATION bin)
install(
    TARGETS talker
    RUNTIME DESTINATION bin)
install(DIRECTORY include/time DESTINATION include)
ament_export_include_directories(include)

ament_package()
