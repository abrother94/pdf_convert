PROJECT (E_OMCI C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#
# Need add below or appear many error while compile CXX of JSONCXX
#
SET (CMAKE_CXX_STANDARD 11)

#
# You need put this module in front of the module that you use lib/incldue later
# 
ADD_SUBDIRECTORY(open_source)

INCLUDE_DIRECTORIES (
include
)

INCLUDE_DIRECTORIES (
    ${JSONCXX_INCLUDE_DIRS}
)

INCLUDE_DIRECTORIES (
    ${JSONCPP_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MY_FILE__='\"$(notdir $(abspath $<))\"'")

FILE(GLOB E_OMCI_SOURCES "src/*.cpp")

ADD_EXECUTABLE (e_omci ${E_OMCI_SOURCES})

TARGET_LINK_LIBRARIES(e_omci
    ${JSONCXX_LIBRARIES}
    ${JSONCPP_LIBRARIES}
)

