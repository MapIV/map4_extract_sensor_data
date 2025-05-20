#include "extract_image.hpp"

ExtractImageNode::ExtractImageNode(const rclcpp::NodeOptions &options)
    : Node("extract_image_node", options) {
    this->declare_parameter<std::string>("output_folder", "./image_output");
    output_folder_ = this->get_parameter("output_folder").as_string();
    if (!fs::exists(output_folder_)) {
        fs::create_directories(output_folder_);
    }

    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "input", 10,
        [this](const sensor_msgs::msg::Image::SharedPtr msg) {
            save_image(msg, output_folder_);
        });
}

void ExtractImageNode::ensure_output_directories() {
    if (!fs::exists(output_folder_)) {
        fs::create_directories(output_folder_);
    }
}

void ExtractImageNode::save_image(const sensor_msgs::msg::Image::SharedPtr msg, const std::string &folder) {
    try {
        cv_bridge::CvImageConstPtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvShare(msg, msg->encoding);  // Pass-through encoding
        } catch (const cv_bridge::Exception &e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        double ts = msg->header.stamp.sec + (double)msg->header.stamp.nanosec * 1e-9;
        std::string filename = folder + "/" + std::to_string(ts) + ".jpg";

        if (!cv::imwrite(filename, cv_ptr->image)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to write image to %s", filename.c_str());
        } else {
            RCLCPP_DEBUG(this->get_logger(), "Saved image to %s", filename.c_str());
        }
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Error saving image: %s", e.what());
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ExtractImageNode)