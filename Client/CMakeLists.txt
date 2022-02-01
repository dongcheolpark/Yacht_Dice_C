cmake_minimum_required(VERSION 3.11)
project(YACHT_DICE_C)

SET( BINARY ${CMAKE_PROJECT_NAME} )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )

SET (CMAKE_CXX_FLAGS "-pthread")

SET (CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
SET (CMAKE_CXX_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )

SET (SRC_FILES
	main.cpp
	network.cpp
	game.cpp
	graphic.cpp
	../common/user.cpp
	../common/Room.cpp
	../common/dice_game.cpp
	../common/scoreboard.cpp
    )
ADD_EXECUTABLE(${BINARY}_Client  ${SRC_FILES})

if(WIN32)
	target_link_libraries(Yacht_Dice_Client wsock32 ws2_32)
endif()