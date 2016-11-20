#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include "builtin_interfaces/msg/time.hpp"

namespace framework
{
class Time
{
public:
    explicit Time(rclcpp::node::Node::SharedPtr node);
builtin_interfaces::msg::Time getTime() const;
private:
    bool receivedFirstClockMsg;
builtin_interfaces::msg::Time lastTime;
    rclcpp::subscription::Subscription<builtin_interfaces::msg::Time>::SharedPtr sub;
};

std::chrono::time_point<std::chrono::steady_clock> toTimePoint(const builtin_interfaces::msg::Time& msg);
std::chrono::time_point<std::chrono::steady_clock> toTimePoint(double time_s);

double toSecondsAsDouble(const builtin_interfaces::msg::Time& msg);
double toSecondsAsDouble(std::chrono::time_point<std::chrono::steady_clock> const& time_point);

}  // namespace framework
