project(YACHT_DICE_C)
SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_FLAGS "-pthread")

SET (CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
SET (CMAKE_CXX_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )

ADD_EXECUTABLE(Yacht_Dice_Client
				main.cpp
				network.cpp
				../common/user.cpp
				game.cpp)