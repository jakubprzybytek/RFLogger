########################################################################
# Build RFLogger
########################################################################
cmake_minimum_required(VERSION 2.8.7)
project(RFLogger CXX)

find_package(SoapySDR "0.4.0" NO_MODULE REQUIRED)
if (NOT SoapySDR_FOUND)
	message(FATAL_ERROR "Soapy SDR development files not found...")
endif ()

find_package(Boost "1.55" COMPONENTS serialization REQUIRED)

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16")

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

add_executable(RFLogger
	common/Timestamp.hpp
	common/Timestamp.cpp
	common/stdUtils.hpp
	common/stdUtils.cpp
	output/ostream.hpp
	output/ostream.cpp
	output/WaterfallImage.hpp
	output/WaterfallImage.cpp
	output/ColorPalette.hpp
	output/ColorPalette.cpp
	storage/Storage.hpp
	storage/Storage.cpp
	sdr/SDR.hpp
	sdr/SDR.cpp
	sdr/SDRDevice.hpp
	sdr/SDRDevice.cpp
	fft/FFT.hpp
	fft/kissfft.hh
	RFLogger.hpp
	RFLogger.cpp
	ReadSamples.cpp
)

add_executable(FFTTests
	sdr/SDR.hpp
	sdr/SDR.cpp
	common/Timestamp.hpp
	common/Timestamp.cpp
	common/stdUtils.hpp
	common/stdUtils.cpp
	output/ostream.hpp
	output/ostream.cpp
	fft/FFTTests.cpp
	fft/FFT.hpp
	fft/kissfft.hh
)

add_executable(StorageTest
	common/Timestamp.hpp
	common/Timestamp.cpp
	storage/Storage.hpp
	storage/Storage.cpp
	storage/StorageTest.cpp
)

add_executable(ImagesTest
	sdr/SDR.hpp
	sdr/SDR.cpp
	output/WaterfallImage.hpp
	output/WaterfallImage.cpp
	output/ColorPalette.hpp
	output/ColorPalette.cpp
	output/ImagesTest.cpp
)

target_link_libraries(RFLogger SoapySDR ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES})
target_link_libraries(StorageTest ${Boost_LIBRARIES})
target_link_libraries(ImagesTest ${ImageMagick_LIBRARIES})
