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
    QCoreApplication a(argc, argv);
    rclcpp::init(argc, argv);

    auto server = std::make_shared<TestNode>();

    QtExecutor executor;
    executor.add_node(server);

    executor.start();

    auto res = a.exec();
    printf("Exited QT thread\n");
    rclcpp::shutdown();
    return res;
}
