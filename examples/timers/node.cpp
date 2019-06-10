#include "node.h"
#include <QDebug>
#include <QThread>

using namespace rclcpp;
using namespace std::chrono_literals;

TestNode::TestNode(QObject *parent):
    QObject (parent),
    Node("test_node")
{
    m_monotonicTimer.start();
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &TestNode::onQtTimerCB);
    m_timer->start(1000);

    m_periodic_timer = this->create_wall_timer(
          1s,
          [this]() {
            qDebug() << "@" << m_monotonicTimer.elapsed() << "ms : ros timer timeout from thread : " << QThread::currentThreadId();
    });
}

void TestNode::onQtTimerCB()
{
    qDebug() << "@" << m_monotonicTimer.elapsed() << "ms : QTimer timeout from thread : " << QThread::currentThreadId();
}
