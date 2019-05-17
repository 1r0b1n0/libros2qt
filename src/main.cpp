#include "rclcpp/rclcpp.hpp"
#include <QCoreApplication>
#include <QTimer>
#include <rclcpp/executor.hpp>
#include <QObject>
#include "qt_executor.h"
#include "node.h"

using namespace rclcpp;

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    QCoreApplication a(argc, argv);

    auto server = std::make_shared<TestNode>();

    //executors::SingleThreadedExecutor executor;
    QtExecutor executor;
    executor.add_node(server);

    /*
    QTimer rosPollTimer;
    rosPollTimer.connect(&rosPollTimer, &QTimer::timeout, [&]() {
        executor.spin_some();
        if(rclcpp::ok() == false)
        {
            qApp->quit();
        }
    });
    rosPollTimer.start(10);
    */
    executor.start();

    auto res = a.exec();
    rclcpp::shutdown();
    return res;
}
