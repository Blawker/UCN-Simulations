# Cmake version required
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT(Beamline)

# Path to the directory that contain the head files
INCLUDE_DIRECTORIES( src/include )


# ROOT installation path
list(APPEND CMAKE_PREFIX_PATH /opt/local/libexec/root6/share/root)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Hist)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})


# Path to the binary files
SET( EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE} )

# Option for compiler to support C++ 2011
SET( CMAKE_CXX_FLAGS "-std=c++11" )

# Create the executables
ADD_EXECUTABLE( createHistogram src/createHistogram.cpp )
ADD_EXECUTABLE( convertCsvToRoot src/convertCsvToRoot.cpp )
ADD_EXECUTABLE( convertRootToCsv src/convertRootToCsv.cpp )
ADD_EXECUTABLE( conversion src/conversion.cxx )

# Link the Root libraries
target_link_libraries(createHistogram ${ROOT_LIBRARIES})
target_link_libraries(convertCsvToRoot ${ROOT_LIBRARIES})
target_link_libraries(convertRootToCsv ${ROOT_LIBRARIES})

# Talking make
set( CMAKE_VERBOSE_MAKEFILE off )
