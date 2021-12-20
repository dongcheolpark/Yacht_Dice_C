project(YACHT_DICE_C)
SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_FLAGS "-pthread")
ADD_EXECUTABLE(Yacht_Dice_Client main.cpp network.cpp ../common/user.cpp game.cpp)