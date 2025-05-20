#ifndef MAP4_EXTRACT_POINTCLOUD2_NODE_HPP
#define MAP4_EXTRACT_POINTCLOUD2_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class ExtractPointcloud2Node : public rclcpp::Node {
public:
    explicit ExtractPointcloud2Node(const rclcpp::NodeOptions &options);

private:
    void save_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg, const std::string &folder);

    std::string output_folder_;

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_sub_;
};

#endif // MAP4_EXTRACT_POINTCLOUD2_NODE_HPP
