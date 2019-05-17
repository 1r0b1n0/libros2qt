cmake_minimum_required(VERSION 3.5)
project(libros2qt)

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
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_library(GeographicLib_LIBRARIES Geographic)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core SerialPort Network REQUIRED)

include_directories(include ${lib_gnss_INCLUDE_DIRS}
    ${visualization_msgs_INCLUDE_DIRS}
    ${std_srvs_INCLUDE_DIRS}
    ${robopec_msgs_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5SerialPort_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS})
aux_source_directory(src DRIVERS_SRC)
add_executable(testnode ${DRIVERS_SRC})
ament_target_dependencies(testnode rclcpp std_msgs lib_gnss
    std_srvs)
target_link_libraries(testnode Qt5::Core)


install(TARGETS testnode DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
