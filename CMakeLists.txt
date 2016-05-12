cmake_minimum_required(VERSION 3.2)
project(eva-cpp)

include(CMakeListsPrivate.txt)

add_definitions(-DF_CPU=80000000L)
add_definitions(-D__ets__)
add_definitions(-DICACHE_FLASH)
add_definitions(-DESP8266)
add_definitions(-DARDUINO_ARCH_ESP8266)
add_definitions(-DARDUINO_ESP8266_ESP07)
add_definitions(-DARDUINO=20200)
add_definitions(-DPLATFORMIO=020901)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(eva-cpp
    src/init.cpp
    src/Logger.cpp
    src/Drone.cpp
    src/Hardware/SpeedControllers/SpeedControllerManager.cpp
    src/Hardware/SpeedControllers/SpeedController.cpp
    src/Agents/AgentManager.cpp
    src/Agents/Wifi/WifiAgentClient.cpp
    src/Agents/Wifi/WifiAgent.cpp
)
