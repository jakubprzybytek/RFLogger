########################################################################
# Build RFLogger
########################################################################
cmake_minimum_required(VERSION 2.8.7)
project(RFLogger C CXX)

find_package(SoapySDR "0.4.0" NO_MODULE REQUIRED)
if (NOT SoapySDR_FOUND)
	message(FATAL_ERROR "Soapy SDR development files not found...")
endif ()

find_package(Boost "1.55" COMPONENTS serialization REQUIRED)

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16")

find_package (Threads REQUIRED)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIR}
	${ImageMagick_INCLUDE_DIRS}
)

#enable c++11 features
if (CMAKE_COMPILER_IS_GNUCXX)

	#C++11 is a required language feature for this project
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_STD_CXX11)
	if (HAS_STD_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	else (HAS_STD_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	endif ()

endif(CMAKE_COMPILER_IS_GNUCXX)

add_library(SDR
	sdr/SDR.hpp
	sdr/SDR.cpp
	sdr/SDRDevice.hpp
	sdr/SDRDevice.cpp
)

add_library(Common
	common/stdUtils.hpp
	common/stdUtils.cpp
	common/Timestamp.hpp
	common/Timestamp.cpp
	common/Timer.hpp
	common/Timer.cpp
)

add_library(FFT
	fft/FFT.hpp
	fft/FFT.cpp
	fft/kissfft.hh
)

add_library(Output
	output/ostream.hpp
	output/ostream.cpp
	output/WaterfallImage.hpp
	output/WaterfallImage.cpp
	output/ColorPalette.hpp
	output/ColorPalette.cpp
)

add_library(Storage
	storage/Storage.hpp
	storage/Storage.cpp
)

add_executable(RFLogger
	RFLogger.hpp
	RFLogger.cpp
	ReadSamples.cpp
)

add_executable(FFTTest
	fft/FFTTest.cpp
)

add_executable(StorageTest
	storage/StorageTest.cpp
)

add_executable(ImagesTest
	output/ImagesTest.cpp
)

target_link_libraries(RFLogger Storage FFT Output SDR Common SoapySDR ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(FFTTest FFT Output SDR Common)
target_link_libraries(StorageTest Storage Common ${Boost_LIBRARIES})
target_link_libraries(ImagesTest Output SDR ${ImageMagick_LIBRARIES})
