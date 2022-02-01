CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

SET(proj_name "Yacht_Dice")
PROJECT( ${proj_name} )

# C++ settings
SET(CMAKE_CXX_STANDARD 11)

add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(tests)
add_subdirectory(extern/googletest)