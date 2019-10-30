add_executable(RPNapp main.cpp)

target_link_libraries(RPNapp RPN)
target_include_directories(RPNapp PUBLIC ${RPN_INCLUDE_DIR})
