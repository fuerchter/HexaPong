cmake_minimum_required(VERSION 2.8)

project(HexaPong)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(RAPIDXML REQUIRED)

if(RAPIDXML_FOUND)
	include_directories(${RAPIDXML_INCLUDE_DIRS})
endif()

find_package(SFML REQUIRED COMPONENTS system window graphics audio)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	set(LIBRARIES ${LIBRARIES} ${SFML_LIBRARIES})
endif()

#Folders to be searched
set(FOLDERS "src" "src/engine" "src/game" "src/game/entities" "src/menu")

#Adding source files in each of the FOLDERS to EXECUTABLES
foreach(FOLDER ${FOLDERS})
	file(GLOB GLOBFILES "${FOLDER}/*.cpp")
	set(EXECUTABLES ${EXECUTABLES} ${GLOBFILES})
endforeach(FOLDER)

add_executable(HexaPong ${EXECUTABLES})
target_link_libraries(HexaPong ${LIBRARIES})

install(TARGETS HexaPong DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY "assets" DESTINATION ${CMAKE_INSTALL_PREFIX})