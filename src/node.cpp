#include "node.h"

using namespace rclcpp;
using namespace std::chrono_literals;

TestNode::TestNode(QObject *parent):
    QObject (parent),
    Node("test_node")
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &TestNode::onQtTimerCB);
    m_timer->start(1000);

    m_periodic_timer = this->create_wall_timer(
          1s,
          [this]() {
            RCLCPP_INFO(this->get_logger(), "in periodic_timer callback");
    });
}

void TestNode::onQtTimerCB()
{
    RCLCPP_INFO(get_logger(), "QT Timer !");
}
