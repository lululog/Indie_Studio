cmake_minimum_required(VERSION 3.11)

# set the project name
project(indie_studio)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Irlicht
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Irrlicht/)
set(Irrlicht_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Irrlicht/)

# set include
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Irrlicht/include/
	${CMAKE_CURRENT_SOURCE_DIR}/Irrlicht/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
	)

#Source file
file(GLOB SOURCES ./src/*.cpp)

find_package(Irrlicht REQUIRED)


link_libraries(${Irrlicht_LIBRARIES})


IF (MSVC)     # Windows
	set(SFML_DIR SFML/lib/cmake/SFML/)
	find_package(SFML 2.5 COMPONENTS audio REQUIRED)
	add_executable(bomberman "${SOURCES}")
	target_link_libraries(bomberman "${IRRLICHT_LIBRARY}" sfml-audio)
	set(EXECUTABLE_OUTPUT_PATH bin/)
	add_custom_command (TARGET bomberman POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${Irrlicht_DIR}/Irrlicht.dll ${EXECUTABLE_OUTPUT_PATH}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy SFML/bin/sfml-audio-2.dll ${EXECUTABLE_OUTPUT_PATH}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy SFML/bin/sfml-audio-d-2.dll ${EXECUTABLE_OUTPUT_PATH}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy SFML/bin/sfml-system-2.dll ${EXECUTABLE_OUTPUT_PATH}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy SFML/bin/sfml-system-d-2.dll ${EXECUTABLE_OUTPUT_PATH}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy SFML/bin/openal32.dll ${EXECUTABLE_OUTPUT_PATH}/Debug
	)
ELSE (MSVC)   # Linux
	add_executable(bomberman "${SOURCES}")
	target_link_libraries(
					bomberman
					-L./Irrlicht/
					-lIrrlicht
					-std=c17
					-lsfml-audio
					)
ENDIF(MSVC)
