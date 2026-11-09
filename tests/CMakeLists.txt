add_executable(filecheck_tests test_checker.cpp)
target_link_libraries(filecheck_tests PRIVATE filecheck_lib)
add_test(NAME filecheck_tests COMMAND filecheck_tests)

