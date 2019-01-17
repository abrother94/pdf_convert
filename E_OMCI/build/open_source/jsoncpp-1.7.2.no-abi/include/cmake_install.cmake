# Install script for directory: /home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/json/value.h;/usr/local/include/json/config.h;/usr/local/include/json/assertions.h;/usr/local/include/json/json.h;/usr/local/include/json/allocator.h;/usr/local/include/json/forwards.h;/usr/local/include/json/version.h;/usr/local/include/json/writer.h;/usr/local/include/json/features.h;/usr/local/include/json/autolink.h;/usr/local/include/json/reader.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/json" TYPE FILE FILES
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/value.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/config.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/assertions.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/json.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/allocator.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/forwards.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/version.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/writer.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/features.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/autolink.h"
    "/home/abrother/pdf_convert/E_OMCI/open_source/jsoncpp-1.7.2.no-abi/include/json/reader.h"
    )
endif()

