cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

#-------------------------------------------------------------------------------
# User configuration
#-------------------------------------------------------------------------------
# Set Arduino sketchbook directory
if(WIN32)
    set(SKETCHBOOK_DIR  C:/Users/$ENV{USERNAME}/Documents/Arduino)
elseif(UNIX)
    set(SKETCHBOOK_DIR  $ENV{HOME}/Arduino/libraries)
endif()

# Configure one sketch
set(SKETCH      examples/ContinuesMode/BH1750ContinuesAsynchronous/BH1750ContinuesAsynchronous.ino)
#set(SKETCH      examples/ContinuesMode/BH1750ContinuesBasic/BH1750ContinuesBasic.ino)
#set(SKETCH      examples/ContinuesMode/BH1750ContinuesHighResolution/BH1750ContinuesHighResolution.ino)
#set(SKETCH      examples/ContinuesMode/BH1750ContinuesLowResolution/BH1750ContinuesLowResolution.ino)
#set(SKETCH      examples/ContinuesMode/BH1750ContinuesPowerMgt/BH1750ContinuesPowerMgt.ino)

#set(SKETCH      examples/OneTimeMode/BH1750OneTimeBasic/BH1750OneTimeBasic.ino)
#set(SKETCH      examples/OneTimeMode/BH1750OneTimeHighResolution/BH1750OneTimeHighResolution.ino)
#set(SKETCH      examples/OneTimeMode/BH1750OneTimeLowResolution/BH1750OneTimeLowResolution.ino)
#set(SKETCH      examples/OneTimeMode/BH1750OneTimePowerMgt/BH1750OneTimePowerMgt.ino)

# Configure board, default Arduino UNO
set(BOARD       uno)
#set(BOARD       nano)

if(${BOARD} STREQUAL nano)
    set(nano.upload.maximum_size 30720)
    set(nano.upload.maximum_data_size 2048)
    set(nano.upload.speed 57600)
    set(nano.build.mcu atmega328p)
endif()

# Configure serial port:
if(WIN32)
    set(SERIAL_PORT     COM6)
elseif(UNIX)
    set(SERIAL_PORT     /dev/ttyUSB0)
endif()

#-------------------------------------------------------------------------------
# Project configuation
#-------------------------------------------------------------------------------
# Project name
set(PROJECT_NAME        ErriezBH1750)

# Set library directory
set(ROTARY_SRC_DIR      ${SKETCHBOOK_DIR}/libraries/${PROJECT_NAME}/src)

# Configure project
project(${PROJECT_NAME})

# Configure include directories
include_directories(${ROTARY_SRC_DIR})

# Generate library
generate_arduino_library(
        RotaryLib
        SRCS
            ${ROTARY_SRC_DIR}/BH1750.cpp
        HDRS
            ${ROTARY_SRC_DIR}/BH1750.h
            ${ROTARY_SRC_DIR}/BH1750_priv.h
)

# Configure project
set(${CMAKE_PROJECT_NAME}_SKETCH    ${SKETCH})
set(${CMAKE_PROJECT_NAME}_LIBS      RotaryLib)
set(${CMAKE_PROJECT_NAME}_BOARD     ${BOARD})
set(${CMAKE_PROJECT_NAME}_PORT      ${SERIAL_PORT})
generate_arduino_firmware(${CMAKE_PROJECT_NAME})
