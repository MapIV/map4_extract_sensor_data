#ifndef MAP4_EXTRACT_COMPRESSED_IMAGE_HPP
#define MAP4_EXTRACT_COMPRESSED_IMAGE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class ExtractCompressedImageNode : public rclcpp::Node {
public:
    explicit ExtractCompressedImageNode(const rclcpp::NodeOptions &options);

private:
    void ensure_output_directories();
    void save_image(const sensor_msgs::msg::CompressedImage::SharedPtr msg, const std::string &folder);
    std::string output_folder_;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr image_sub_;
};

#endif // MAP4_EXTRACT_COMPRESSED_IMAGE_HPP
