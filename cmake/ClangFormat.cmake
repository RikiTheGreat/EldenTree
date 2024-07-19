function(add_clangformat TARGET_NAME)
    find_program(CLANG_FORMAT_PATH clang-format REQUIRED)

    file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)
    file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
    set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})



    add_custom_target(${TARGET_NAME}
            COMMAND ${CLANG_FORMAT_PATH} -i ${ALL_FILES} -style=file
            COMMENT "Running clang-format on ${ALL_FILES} files"
    )

endfunction()