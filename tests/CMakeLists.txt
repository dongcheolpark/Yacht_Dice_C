SET(BINARY ${CMAKE_PROJECT_NAME}_test)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
SET(SOURCES
	${TEST_SOURCES} 
	../common/user.cpp
	../common/Room.cpp
	../common/dice_game.cpp
	../common/scoreboard.cpp
)

add_executable(${BINARY} ${SOURCES})
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC gtest)
