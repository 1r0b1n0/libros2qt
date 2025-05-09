cmake_minimum_required(VERSION 3.5)
project(libros2qt)

set(COMPILE_EXAMPLES off CACHE BOOL "Compile examples")

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

include_directories(include)

add_library(libros2qt SHARED src/qt_executor.cpp include/libros2qt/qt_executor.h)
target_include_directories(libros2qt PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
if(rclcpp_VERSION_MAJOR GREATER_EQUAL 2)
  message("Foxy or newer rclcpp detected")
  target_compile_definitions(libros2qt PUBLIC POST_FOXY)
endif()
target_link_libraries(libros2qt Qt${QT_VERSION_MAJOR}::Core)
ament_target_dependencies(libros2qt rclcpp)

if(COMPILE_EXAMPLES)
  add_executable(testnode examples/timers/main.cpp examples/timers/node.cpp)
  ament_target_dependencies(testnode rclcpp)
  target_link_libraries(testnode libros2qt Qt${QT_VERSION_MAJOR}::Core)
  install(TARGETS testnode DESTINATION lib/${PROJECT_NAME})
endif()

ament_export_targets(export_libros2qt HAS_LIBRARY_TARGET)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS libros2qt
  EXPORT export_libros2qt
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

ament_package()
