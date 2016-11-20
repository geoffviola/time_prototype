#include <chrono>
#include "time/Time.hpp"

namespace framework
{

using std::chrono::nanoseconds;
using std::chrono::steady_clock;
using std::chrono::time_point;

Time::Time(rclcpp::node::Node::SharedPtr node)
    : receivedFirstClockMsg(false)
    , sub(node->create_subscription<builtin_interfaces::msg::Time>(
            "asi_clock",
            [this](builtin_interfaces::msg::Time::SharedPtr msg) {
        this->lastTime = *msg;
        this->receivedFirstClockMsg = true;
    std::cout << "time is " << msg->sec << "\n";
    }, rmw_qos_profile_sensor_data))
{
    while (rclcpp::ok() && !this->receivedFirstClockMsg)
    {
        rclcpp::spin_some(node);
        rclcpp::sleep_for(std::chrono::milliseconds(1));
    }
}

builtin_interfaces::msg::Time Time::getTime() const
{
    return this->lastTime;
}

time_point<std::chrono::steady_clock> toTimePoint(const builtin_interfaces::msg::Time& msg)
{
    return time_point<steady_clock>(
        std::chrono::nanoseconds(msg.sec * static_cast<uint64_t>(1000000000LU) + msg.nanosec));
}

time_point<std::chrono::steady_clock> toTimePoint(const double time_s)
{
    return time_point<steady_clock>(
        std::chrono::nanoseconds(static_cast<uint64_t>(time_s * 1000000000.0)));
}

double toSecondsAsDouble(const builtin_interfaces::msg::Time& msg)
{
    return toSecondsAsDouble(toTimePoint(msg));
}

double toSecondsAsDouble(time_point<steady_clock> const& time_point)
{
    return std::chrono::duration_cast<nanoseconds>(time_point.time_since_epoch()).count() / 1e9;
}
}
