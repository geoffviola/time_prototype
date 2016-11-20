#include <rclcpp/rclcpp.hpp>
#include "time/Time.hpp"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::node::Node::make_shared("steady_clock_publisher_single_threaded");
    auto pub = node->create_publisher<builtin_interfaces::msg::Time>("asi_clock", rmw_qos_profile_sensor_data);

    rclcpp::WallRate rate(1000);
    while (rclcpp::ok())
    {
	static uint32_t fake_sec = 0;
	builtin_interfaces::msg::Time msg;
	msg.sec = fake_sec;
	fake_sec++;
            pub->publish(msg);
            rclcpp::spin_some(node);
            rate.sleep();
    }

    return EXIT_SUCCESS;
}
