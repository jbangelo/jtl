add_subdirectory(googletest)

add_executable(test-jtl
    test_main.cpp
    test_type_trait_constants.cpp
    )
target_link_libraries(test-jtl
    jtl
    gtest
    stdc++
    )
set_property(TARGET test-jtl PROPERTY CXX_STANDARD 17)
set_property(TARGET test-jtl PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET test-jtl PROPERTY CXX_EXTENSIONS OFF)
