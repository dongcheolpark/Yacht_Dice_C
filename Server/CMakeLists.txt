SET (CMAKE_CXX_STANDARD 11)
ADD_EXECUTABLE(Yacht_Dice_Server
				main.cpp
				server.cpp
				../common/user.cpp
				game_server.cpp
				../common/room.cpp
				game_server_parse.cpp
				)