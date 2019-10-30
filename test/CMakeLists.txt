add_custom_target(buildtests)
add_custom_target(check COMMAND "ctest")
add_dependencies(check buildtests)

set(testing_include_dir ${CMAKE_CURRENT_SOURCE_DIR})

# Call exemple :
#   daftrays_add_test(
#       TARGET testName
#       SRC testName.cpp
#       LIBS libName )
# tests are generated in tests (not Bundle !)
function(rpn_add_test)
    set(_options "")
    set(_oneValueArgs TARGET)
    set(_multiValueArgs SRC LIBS)
    cmake_parse_arguments(_option "${_options}" "${_oneValueArgs}" "${_multiValueArgs}" ${ARGN})

    add_executable(test_${_option_TARGET} ${_option_SRC})
    set_property(TARGET test_${_option_TARGET} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    add_dependencies(buildtests test_${_option_TARGET})
    add_test(NAME test_${_option_TARGET}
            #CONFIGURATIONS Release
            COMMAND test_${_option_TARGET})
    target_link_libraries(test_${_option_TARGET} ${_option_LIBS})
    target_include_directories(test_${_option_TARGET} PUBLIC ${testing_include_dir} ${RPN_INCLUDE_DIR})
endfunction()

include_directories(${RPN_3RDPARTY}/acutest/include)

include(CTest)
configure_file(${CMAKE_BINARY_DIR}/DartConfiguration.tcl ${CMAKE_BINARY_DIR}/DartConfiguration.tcl)

rpn_add_test(
        TARGET rpn
        SRC ci_tests.cpp
        LIBS RPN
)