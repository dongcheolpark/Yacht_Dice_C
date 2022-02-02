SET (CMAKE_CXX_STANDARD 11)

SET( BINARY ${CMAKE_PROJECT_NAME} )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )

SET (SRC_FILES
	main.cpp
	server.cpp
	../common/user.cpp
	game_server.cpp
	../common/Room.cpp
	game_server_parse.cpp
	../common/scoreboard.cpp
	../common/dice_game.cpp
)

ADD_EXECUTABLE(${BINARY}_Server  ${SRC_FILES})