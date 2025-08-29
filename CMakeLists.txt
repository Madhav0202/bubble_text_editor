cmake_minimum_required(VERSION 3.9.1)
project(TEXT_EDITOR)

#Specify C++ standard
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(text_editor src/main.c)

if(UNIX)
	target_link_libraries(text_editor pthread)
endif()



