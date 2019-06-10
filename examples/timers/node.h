#pragma once

#include <QCoreApplication>
#include <QTimer>
#include <QObject>
#include <QElapsedTimer>
#include <rclcpp/rclcpp.hpp>

class TestNode : public QObject, public rclcpp::Node
{
    Q_OBJECT

public:
    TestNode(QObject* parent=nullptr);
    virtual ~TestNode() = default;

private slots:
    void onQtTimerCB();

private:

    QTimer *m_timer;
    QElapsedTimer m_monotonicTimer;
    rclcpp::TimerBase::SharedPtr m_periodic_timer;
};
