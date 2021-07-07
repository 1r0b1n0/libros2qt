# librosqt
This is a simple library that merges the event loop of ROS2 and Qt.
This is done by providing a custom executor.

# Usage
In your main.cpp init the node in the following way :

```c++
#include <QCoreApplication>
#include <rclcpp/rclcpp.hpp>
#include <lib_ros2_qt/qt_executor.h>

using namespace rclcpp;
int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    rclcpp::init(argc, argv);

    auto server = std::make_shared<TestNode>();

    QtExecutor executor;
    executor.add_node(server);

    executor.start();

    auto res = a.exec();    
    rclcpp::shutdown();
    return res;
}


```

## Examples
* [Simple example](examples/timers)


# Motivations
The Qt library can be useful for ROS nodes when developping GUI applications, or even in headless nodes using network communications (tcp/ip, modbus, canbus, bluetooth ...).

Both Qt and ROS2 need to have their own event loop spinning : `rclcpp::executors::SingleThreadedExecutor::spin()` for ROS, `QCoreApplication::exec()` for Qt.

## License
[MIT](https://opensource.org/licenses/MIT)

