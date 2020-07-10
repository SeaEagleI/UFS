project(UFS)

cmake_minimum_required(VERSION 3.16.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        INode.h INode.cpp
        Buffer.h Buffer.cpp
        BufferManager.h BufferManager.cpp
        DeviceDriver.h DeviceDriver.cpp
        File.h File.cpp
        FileManager.h FileManager.cpp
        FileSystem.h FileSystem.cpp
        OpenFileManager.h OpenFileManager.cpp
        User.h User.cpp
        Utility.h Utility.cpp
        )

add_executable(UFS main.cpp ${SOURCE_FILES})
