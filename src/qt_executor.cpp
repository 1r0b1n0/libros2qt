#include "libros2qt/qt_executor.h"

#include "rclcpp/executors/single_threaded_executor.hpp"
#include "rclcpp/any_executable.hpp"
#include "rclcpp/scope_exit.hpp"
#include <thread>
#include <QCoreApplication>

using namespace rclcpp;

QtExecutor::QtExecutor(const ExecutorOptions &args)
: executor::Executor(args) {
    connect(this, &QtExecutor::onNewWork, this, &QtExecutor::processWork, Qt::ConnectionType::BlockingQueuedConnection);
}

QtExecutor::~QtExecutor() {
    m_thread.join();
}

void
QtExecutor::spin()
{
}

void
QtExecutor::start()
{
    m_thread = std::thread([this](){
       while(rclcpp::ok(this->context_))
       {
           wait_for_work();
           if(rclcpp::ok(this->context_)) {
               // If we are shutting down, we must not call onNewWork because the QT Event loop is closed.
               onNewWork();
           }
       }
       QMetaObject::invokeMethod(QCoreApplication::instance(), "quit", Qt::ConnectionType::QueuedConnection);
    });
}

void QtExecutor::processWork()
{
    spin_some();
}
