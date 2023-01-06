# Scan *.cc files in subdirectories and build a target for each
file(
        GLOB_RECURSE subdirectories
        CONFIGURE_DEPENDS
        LIST_DIRECTORIES true
        ${CMAKE_CURRENT_SOURCE_DIR}/**
)
# Filter out files
foreach(entry ${subdirectories})
    if(NOT (IS_DIRECTORY ${entry}))
        list(REMOVE_ITEM subdirectories ${entry})
    endif()
endforeach()

foreach(subdir ${subdirectories})
    if(EXISTS ${subdir}/CMakeLists.txt)
        # If the subdirectory contains a CMakeLists.txt file
        # we let the CMake file manage the source files
        #
        # Use this if you want to link to external libraries
        # without creating a module
        add_subdirectory(${subdir})
    endif()
endforeach()