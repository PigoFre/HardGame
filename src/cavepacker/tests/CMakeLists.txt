set(NAME cavepacker)
project(tests_${NAME})
SET(${PROJECT_NAME}_SRC
	BoardStateTest.cpp
	MapManagerTest.cpp
	ProtocolTest.cpp
	SokobanMapContextTest.cpp
	SokobanMapTest.cpp
	CampaignTest.cpp
	PathfindingTest.cpp
	SolutionUtilTest.cpp
	../main/CavePacker.cpp
	../../tests/TestAll.cpp
	../../tests/TestShared.cpp
	../../tests/NetworkTest.cpp
	../../tests/NoNetworkTest.cpp
)
cp_add_executable(TARGET ${PROJECT_NAME} SRCS ${${PROJECT_NAME}_SRC} APPNAME ${PROJECT_NAME} VERSION 1.0 VERSION_CODE 1)
cp_target_link_libraries(TARGET ${PROJECT_NAME} LIBS ${NAME}-client ${NAME}-server ${NAME}-shared gtest)
if (MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE -bigobj)
endif()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
