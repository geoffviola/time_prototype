#include "time/Time.hpp"
#include <iomanip>
#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {

    rclcpp::init(argc, argv);
    auto node = rclcpp::node::Node::make_shared("ros_time_echo");
    std::cout << "waiting for time" << std::endl;
    framework::Time time(node);
    std::cout << "count, time (s)" << std::endl;

    rclcpp::WallRate wallRate(100.0);
    uint64_t i = 0U;
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        std::cout << i << ", " << std::fixed << std::setprecision(3) << framework::toSecondsAsDouble(time.getTime())
              << std::endl;
        ++i;
        wallRate.sleep();
    }
    return EXIT_SUCCESS;
}
