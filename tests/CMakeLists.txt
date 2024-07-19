# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()
include(CTest)

find_package(GTest CONFIG REQUIRED)

add_executable(
        test1
        test1.cpp
)
target_link_libraries(
        test1
        PRIVATE GTest::gtest GTest::gtest_main EldenTree

)

add_test(NAME AllTestsInTest1 COMMAND test1)
