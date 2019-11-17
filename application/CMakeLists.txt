file(GLOB_RECURSE app_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE app_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE app_inlines ${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

add_executable(RPNapp ${app_sources} ${app_headers} ${app_inlines})

target_link_libraries(RPNapp RPN)
target_include_directories(RPNapp PUBLIC ${RPN_INCLUDE_DIR})
