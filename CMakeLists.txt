cmake_minimum_required(VERSION 3.14)
project(map4_extract_sensor_data)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ament_cmake_auto REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(cv_bridge)
ament_auto_find_build_dependencies()

include_directories(include ${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} ${pcl_conversions_INCLUDE_DIRS})

# CompressedImage
ament_auto_add_library(extract_compressed_image_node SHARED
        src/extract_compressed_image.cpp
)

target_link_libraries(extract_compressed_image_node ${OpenCV_LIBRARIES})
rclcpp_components_register_node(extract_compressed_image_node
        PLUGIN "ExtractCompressedImageNode"
        EXECUTABLE extract_compressed_image_node_exec
)

# Pointcloud2
ament_auto_add_library(extract_pointcloud2_node SHARED
        src/extract_pointcloud2.cpp
)
target_link_libraries(extract_pointcloud2_node ${OpenCV_LIBRARIES})
rclcpp_components_register_node(extract_pointcloud2_node
        PLUGIN "ExtractPointcloud2Node"
        EXECUTABLE extract_pointcloud2_node_exec
)

# Image
ament_auto_add_library(extract_image_node SHARED
        src/extract_image.cpp
)
target_link_libraries(extract_image_node ${OpenCV_LIBRARIES})
rclcpp_components_register_node(extract_image_node
        PLUGIN "ExtractImageNode"
        EXECUTABLE extract_image_node_exec
)

ament_auto_package(INSTALL_TO_SHARE
        launch
)
