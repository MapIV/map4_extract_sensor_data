#include "extract_pointcloud2.hpp"

ExtractPointcloud2Node::ExtractPointcloud2Node(const rclcpp::NodeOptions &options)
    : Node("extract_pointcloud2_node", options) {
    this->declare_parameter<std::string>("output_folder", "./pointcloud2_output");
    output_folder_ = this->get_parameter("output_folder").as_string();
    if (!fs::exists(output_folder_)) {
        fs::create_directories(output_folder_);
    }

    pointcloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "input", 10,
        [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
            save_pointcloud(msg, output_folder_);
        });
}

void ExtractPointcloud2Node::save_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg, const std::string &folder) {
    RCLCPP_DEBUG(this->get_logger(), "Start saving point cloud to %s", folder.c_str());
    try {
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        double ts = msg->header.stamp.sec + (double)msg->header.stamp.nanosec*std::pow(10, -9);
        std::string filename = folder + "/" + std::to_string(ts) + ".pcd";
        pcl::io::savePCDFileASCII(filename, cloud);
        RCLCPP_DEBUG(this->get_logger(), "Saved point cloud to %s", filename.c_str());
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Error saving point cloud: %s", e.what());
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ExtractPointcloud2Node)
