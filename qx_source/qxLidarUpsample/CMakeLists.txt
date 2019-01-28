cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#set(CMAKE_BUILD_TYPE debug)


project(qxLidarUpsample)

if(UNIX)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -g -Wall ${CMAKE_CXX_FLAGS}")

endif(UNIX)


######## Boost
find_package(Boost COMPONENTS system filesystem REQUIRED)

######### Code Source
set( UPSAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set( QX_BASIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../basic/)
set( TEST_PROGRAM ${PROJECT_NAME}Tool)


INCLUDE_DIRECTORIES (${UPSAMPLE_DIR})
INCLUDE_DIRECTORIES (${QX_BASIC_DIR})

aux_source_directory(${UPSAMPLE_DIR} UPSAMPLE_DIR_SRCS)
aux_source_directory(${QX_BASIC_DIR} QX_BASIC_DIR_SRCS)

LIST (APPEND FULL_SRC
   ${UPSAMPLE_DIR_SRCS}
   ${QX_BASIC_DIR_SRCS}
)


# add_definitions(-DRESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resource/")

######## Compile and linking
add_library(${PROJECT_NAME} SHARED ${FULL_SRC})

target_link_libraries(${PROJECT_NAME}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

add_executable(${TEST_PROGRAM} ${TEST_PROGRAM}.cpp)

target_link_libraries(${TEST_PROGRAM}
  ${PROJECT_NAME}
)



