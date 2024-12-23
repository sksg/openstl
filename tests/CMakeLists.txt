project(OpenSTL-tests LANGUAGES CXX)

list(APPEND OPENSTL_CXX_VERSIONS "03" "11" "14" "17")

foreach(CXX_VERSION IN LISTS OPENSTL_CXX_VERSIONS)
    set(__CXX_VERSION_CMAKE ${CXX_VERSION})
    if(${CXX_VERSION} EQUAL "03")
        set(__CXX_VERSION_CMAKE "98")
    endif()
    add_executable(${PROJECT_NAME}-${CXX_VERSION} test_utils.cpp)
    target_compile_definitions(${PROJECT_NAME}-${CXX_VERSION} PRIVATE "OPENSTL_TEST_CXX_VERSION=(\"C++${CXX_VERSION}\")")
    target_link_libraries(${PROJECT_NAME}-${CXX_VERSION} PRIVATE Catch::CatchWithMain OpenSTL::OpenSTL)

    message(STATUS "Project: ${PROJECT_NAME}-${CXX_VERSION}; CXX_STANDARD = ${__CXX_VERSION_CMAKE} (required)")
    set_target_properties(${PROJECT_NAME}-${CXX_VERSION} PROPERTIES CXX_STANDARD ${__CXX_VERSION_CMAKE}, CMAKE_CXX_STANDARD_REQUIRED YES)
    unset(__CXX_VERSION_CMAKE)
endforeach()

set(ctest_tests_file "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_tests.cmake")

foreach(CXX_VERSION IN LISTS OPENSTL_CXX_VERSIONS)
  set(CATCH_EXECUTABLE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-${CXX_VERSION}")
  message(STATUS "Running ${CATCH_EXECUTABLE}")
  execute_process(
    COMMAND "${CATCH_EXECUTABLE}" --list-test-names-only
    OUTPUT_VARIABLE CATCH_TESTS
    RESULT_VARIABLE CATCH_TEST_RESULT
  )
  # Make sure to escape ; (semicolons) in test names first, because
  # that'd break the foreach loop for "Parse output" later and create
  # wrongly splitted and thus failing test cases (false positives)
  string(REPLACE ";" "\;" CATCH_TESTS "${CATCH_TESTS}")
  string(REPLACE "\n" ";" CATCH_TESTS "${CATCH_TESTS}")

  foreach(CATCH_TEST ${CATCH_TESTS})
    message(STATUS "${CATCH_TEST}")
    add_test(NAME "${CATCH_TEST}" COMMAND "${CATCH_EXECUTABLE}" "${CATCH_TEST}")
  endforeach()
endforeach()
