########################################################################
# Build RFLogger
########################################################################
cmake_minimum_required(VERSION 2.8.7)
project(RFLogger CXX)

find_package(SoapySDR "0.4.0" NO_MODULE REQUIRED)
if (NOT SoapySDR_FOUND)
    message(FATAL_ERROR "Soapy SDR development files not found...")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#enable c++11 features
if(CMAKE_COMPILER_IS_GNUCXX)

    #C++11 is a required language feature for this project
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_STD_CXX11)
    if(HAS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else(HAS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    endif()

endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(RFLogger
	stdUtils.hpp
	stdUtils.cpp
        SDRDevice.hpp
        SDRDevice.cpp
	RFLogger.cpp
)

target_link_libraries(RFLogger SoapySDR)