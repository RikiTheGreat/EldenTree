add_library(EldenTree EldenTree.cpp
        logger.cpp)

# Specify include directories for the library
target_include_directories(EldenTree PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

# specify other properties like version
set_target_properties(EldenTree PROPERTIES VERSION ${PROJECT_VERSION})

if(DO_FORMAT)
    message("formating")
    include(ClangFormat)
    add_clangformat(format)
    add_dependencies(EldenTree format)
endif ()

