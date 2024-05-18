#include <wiringPi.h>
#include <wiringSerial.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>
#include <string>

class GpsPublisher : public rclcpp::Node {
public:
    GpsPublisher() : Node("gps_publisher") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("gps_data", 10);
        serial_port_ = serialOpen("/dev/ttyAMA0", 9600);
        if (serial_port_ < 0) {
            RCLCPP_ERROR(this->get_logger(), "Unable to open serial port");
            rclcpp::shutdown();
        } else {
            RCLCPP_INFO(this->get_logger(), "Serial port opened successfully");
        }
    }

    void read_and_publish() {
        if (serialDataAvail(serial_port_) > 0) {
            std::string gps_data;
            while (serialDataAvail(serial_port_) > 0) {
                char c = serialGetchar(serial_port_);
                gps_data += c;
            }

            auto message = std_msgs::msg::String();
            message.data = gps_data;
            publisher_->publish(message);
            RCLCPP_INFO(this->get_logger(), "Published GPS data: '%s'", gps_data.c_str());
        }
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    int serial_port_;
};

int main(int argc, char *argv[]) {
    wiringPiSetup();
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GpsPublisher>();
    rclcpp::Rate loop_rate(1); // 1 Hz

    while (rclcpp::ok()) {
        node->read_and_publish();
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    serialClose(node->serial_port_);
    rclcpp::shutdown();
    return 0;
}
