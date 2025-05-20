#include "extract_compressed_image.hpp"

ExtractCompressedImageNode::ExtractCompressedImageNode(const rclcpp::NodeOptions &options)
    : Node("extract_compressed_img_node", options) {
    this->declare_parameter<std::string>("output_folder", "./compressed_image_output");
    output_folder_ = this->get_parameter("output_folder").as_string();
    if (!fs::exists(output_folder_)) {
        fs::create_directories(output_folder_);
    }

    image_sub_ = this->create_subscription<sensor_msgs::msg::CompressedImage>(
        "input", 10,
        [this](const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
            save_image(msg, output_folder_);
        });
}

void ExtractCompressedImageNode::ensure_output_directories() {

}

void ExtractCompressedImageNode::save_image(const sensor_msgs::msg::CompressedImage::SharedPtr msg, const std::string &folder) {
    RCLCPP_DEBUG(this->get_logger(), "Start saving image to %s", folder.c_str());
    try {
        cv::Mat image = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
        if (image.empty()) {
            RCLCPP_WARN(this->get_logger(), "Received an empty image");
            return;
        }
        double ts = msg->header.stamp.sec + (double)msg->header.stamp.nanosec*std::pow(10, -9);
        std::string filename = folder + "/" + std::to_string(ts) + ".jpg";
        cv::imwrite(filename, image);
        RCLCPP_DEBUG(this->get_logger(), "Saved image to %s", filename.c_str());
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Error saving image: %s", e.what());
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ExtractCompressedImageNode)
