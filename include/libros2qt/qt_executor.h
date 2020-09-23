#pragma once

#include <QObject>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/executors/single_threaded_executor.hpp>
#include <rclcpp/any_executable.hpp>
#include <rclcpp/scope_exit.hpp>


#include <rmw/rmw.h>

#include <cassert>
#include <cstdlib>
#include <memory>
#include <vector>

#include "rclcpp/executor.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/memory_strategies.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/utilities.hpp"
#include "rclcpp/rate.hpp"
#include "rclcpp/visibility_control.hpp"

#ifdef POST_FOXY
  using Executor = rclcpp::Executor;
  using ExecutorOptions = rclcpp::ExecutorOptions;
#else
    using Executor = rclcpp::executor::Executor;
    using ExecutorOptions = rclcpp::executor::ExecutorArgs;
#endif

/// Single-threaded executor implementation
// This is the default executor created by rclcpp::spin.
class QtExecutor : public QObject, public Executor
{
    Q_OBJECT
public:
  RCLCPP_SMART_PTR_DEFINITIONS(QtExecutor)

  /// Default constructor. See the default constructor for Executor.
  RCLCPP_PUBLIC
  QtExecutor(const ExecutorOptions &args = ExecutorOptions());

  /// Default destrcutor.
  RCLCPP_PUBLIC
  virtual ~QtExecutor();

  /// Single-threaded implementation of spin.
  // This function will block until work comes in, execute it, and keep blocking.
  // It will only be interrupt by a CTRL-C (managed by the global signal handler).
  RCLCPP_PUBLIC
  void
  spin();

  RCLCPP_PUBLIC
  void
  start();

private:

  Q_INVOKABLE void processWork();
  Q_SIGNAL void onNewWork();

private:
  RCLCPP_DISABLE_COPY(QtExecutor)

  std::thread m_thread;
};

