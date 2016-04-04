cmake_minimum_required(VERSION 3.2)
project(eva)

set(ENV{PATH} "/opt/OpenPrinting-Gutenprint/sbin:/opt/OpenPrinting-Gutenprint/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/home/iain/.rvm/bin:/home/iain/Projects/src/github.com/pfalcon/esp-open-sdk/xtensa-lx106-elf/bin:/home/iain/.local/bin")
set(PLATFORMIO_CMD "/home/iain/.local/bin/platformio")

include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/variants/adafruit")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/cores/esp8266")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/cores/esp8266/spiffs")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFi/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFi/src/arch")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFi/src/include")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFi/src/lwip")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-xtensa/lib/gcc/xtensa-lx106-elf/4.8.2/include-fixed")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-xtensa/lib/gcc/xtensa-lx106-elf/4.8.2/include")

add_definitions(-DF_CPU=80000000L)
add_definitions(-D__ets__)
add_definitions(-DICACHE_FLASH)
add_definitions(-DESP8266)
add_definitions(-DARDUINO_ARCH_ESP8266)
add_definitions(-DARDUINO_ESP8266_ESP12)
add_definitions(-DARDUINO=200)
add_definitions(-DPLATFORMIO=020701)

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

add_executable(eva
    src/eva.h src/Logger.h src/LoggerInterface.h src/Drone.h
    src/init.cpp src/Logger.cpp src/Drone.cpp
    src/Agents/AgentInterface.h src/Agents/AgentClientInterface.h
    src/Agents/AgentManager.h src/Agents/AgentManager.cpp
    src/Agents/Wifi/WifiAgent.h src/Agents/Wifi/WifiAgent.cpp
    src/Agents/Wifi/WifiAgentClient.h src/Agents/Wifi/WifiAgentClient.cpp
    src/Hardware/SpeedControllers/SpeedControllerInterface.h src/Hardware/SpeedControllers/SpeedControllerManager.h
    src/Hardware/SpeedControllers/SpeedControllerManager.cpp
    src/Hardware/SpeedControllers/Mystery/MysterySpeedController.h src/Hardware/SpeedControllers/Mystery/MysterySpeedController.cpp
)
