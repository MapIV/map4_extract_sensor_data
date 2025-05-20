#ifndef MAP4_EXTRACT_IMAGE_HPP
#define MAP4_EXTRACT_IMAGE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class ExtractImageNode : public rclcpp::Node {
public:
    explicit ExtractImageNode(const rclcpp::NodeOptions &options);

private:
    void ensure_output_directories();
    void save_image(const sensor_msgs::msg::Image::SharedPtr msg, const std::string &folder);
    std::string output_folder_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
};

#endif // MAP4_EXTRACT_IMAGE_HPP
