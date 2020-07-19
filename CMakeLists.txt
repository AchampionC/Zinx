cmake_minimum_required(VERSION 3.16)
project(prj2_zinx_study)

set(CMAKE_CXX_STANDARD 14)

#set(INC_DIR /usr/inlcude)
#set(LINK_DIR /usr/lib)
#include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
link_libraries(zinx)

add_executable(prj2_zinx_study main.cpp StdinOutchannel.h StdinOutchannel.cpp CmdCheck.cpp CmdCheck.h CmdMsg.cpp CmdMsg.h EchoRole.cpp EchoRole.h ZinxTimer.cpp ZinxTimer.h)
target_link_libraries(prj2_zinx_study zinx)