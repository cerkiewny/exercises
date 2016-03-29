CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(SensationEditor)

IF(NOT WIN32)
  SET(CMAKE_CXX_FLAGS "-std=c++11 -g")
ENDIF()

FIND_PACKAGE(Boost COMPONENTS serialization REQUIRED) 
# Include qt5
#automocks are needed for qt5

FIND_PACKAGE(Qt5 COMPONENTS OpenGL Widgets Core Gui Quick)
SET(CMAKE_AUTOMOC ON)
# Find doxygen
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIRS})


# Include GTest
ADD_SUBDIRECTORY("thirdparty/googletest")
SET(GTEST_INCLUDE_DIR "${gtest_SOURCE_DIR}/include")
SET(GTEST_LIBRARIES "gtest")
INCLUDE_DIRECTORIES("${GTEST_INCLUDE_DIR}")

#Import the testable files
FILE(GLOB_RECURSE TESTABLE_SOURCES "src/*.cpp")

#add the test file for each testable source, also add them to source list exclude files named "main.cpp"
FOREACH(SOURCE_FILE IN LISTS TESTABLE_SOURCES)
  GET_FILENAME_COMPONENT(SOURCE_FILE_EXT ${SOURCE_FILE} EXT)
  IF("${SOURCE_FILE_EXT}" STREQUAL ".cpp")
    GET_FILENAME_COMPONENT(FILE_NAME ${SOURCE_FILE} NAME_WE)
    GET_FILENAME_COMPONENT(FILE_DIR ${SOURCE_FILE} DIRECTORY)
    STRING(REGEX REPLACE "src" "test/unit" FILE_DIR ${FILE_DIR})
    MESSAGE(STATUS "TEST FILE ADDED: test/unit/${FILE_DIR}/${FILE_NAME}.test.cpp")
    #exclude all main files.
    IF(NOT "${FILE_NAME}" STREQUAL "main")
      LIST(APPEND TEST_SOURCES "${FILE_DIR}/${FILE_NAME}.test.cpp")
        MESSAGE(STATUS "SOURCE FILE ADDED: ${SOURCE_FILE}")
      LIST(APPEND SOURCES "${SOURCE_FILE}")
      ENDIF()
    ENDIF()
ENDFOREACH()

#build the mars 
ADD_EXECUTABLE(sensation_editor src/main.cpp  ${SOURCES} ${MOCFILES})
QT5_USE_MODULES(sensation_editor Widgets OpenGL Core Gui Quick)
TARGET_LINK_LIBRARIES(sensation_editor ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})

INCLUDE_DIRECTORIES("src")

INCLUDE_DIRECTORIES("test/unit")
#build tests
ADD_EXECUTABLE(editor_unittest test/unit/main.cpp ${TEST_SOURCES} ${SOURCES} ${MOCFILES})
QT5_USE_MODULES(editor_unittest  Widgets OpenGL Core Gui Quick)
TARGET_LINK_LIBRARIES(editor_unittest ${GTEST_LIBRARIES} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})
