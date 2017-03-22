# - Try to find clang-format
# 
# Once done this will define
#  ClangFormat_FOUND      - System has clang-format
#  ClangFormat_VERSION    - Full version string
#  ClangFormat_EXECUTABLE - Full path to the executable
#
# The following hints are respected
#  CLANG_FORMAT_EXECUTABLE - Path to the executable (including the filename)
#  CLANG_FORMAT_PATH       - Path to the executable (excluding the filename)

include(FindPackageHandleStandardArgs)

set(file_extentions
    ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}
    ${CMAKE_C_SOURCE_FILE_EXTENSIONS}
    "h"
    "hh"
    "h++"
    "hm"
    "hpp"
    "hxx"
    "txx"
    )

# Take path to executable if given
set(executable_candidates ${CLANG_FORMAT_EXECUTABLE})

# Iterate over all paths to find additional candidates
string(REPLACE ":" ";" _PATH "${CLANG_FORMAT_PATH}:$ENV{PATH}")
foreach(p ${_PATH})
    file(GLOB cand_list ${p}/clang-format*)
    foreach(cand ${cand_list})
        if(cand)
            string(REGEX MATCH ".*/clang-format[-0-9.]*$" xx ${cand})
            if(NOT ${cand} MATCHES ".*/clang-format[-0-9.]*$")
                continue()
            endif()
            list(APPEND executable_candidates ${cand})
        endif()
    endforeach()
endforeach()

# Take the first candidate executable
foreach(cand ${executable_candidates})
    execute_process(COMMAND ${cand} -version OUTPUT_VARIABLE clang_out )
    string(REGEX MATCH "clang-format version \([0-9.]*\).*\n" version ${clang_out})
    set(ClangFormat_EXECUTABLE ${cand})
    set(ClangFormat_VERSION_STRING ${CMAKE_MATCH_1})
    break()
endforeach()

find_package_handle_standard_args(
    ClangFormat
    REQUIRED_VARS ClangFormat_EXECUTABLE
    FOUND_VAR ClangFormat_FOUND
    VERSION_VAR ClangFormat_VERSION_STRING
    )

# Function that sets up make targets
set(ClangFormat_CHECK_TARGET_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/ClangFormatCheckTarget.cmake)
function(enable_clang_format_targets)
    set(all_source_files)
    foreach(ext ${file_extentions})
        file(GLOB_RECURSE source_files "*.${ext}")
        list(APPEND all_source_files ${source_files})
    endforeach()
    list(REMOVE_DUPLICATES all_source_files)
    add_custom_target(
        fix-format
        COMMAND ${ClangFormat_EXECUTABLE} -i ${all_source_files}
        )

    add_custom_target(
        check-format
        COMMAND ${CMAKE_COMMAND}
            "'-Dsource_files=${all_source_files}'"
            "'-Dclangformat=${ClangFormat_EXECUTABLE}'"
            -P ${ClangFormat_CHECK_TARGET_SCRIPT}
        )
endfunction()
