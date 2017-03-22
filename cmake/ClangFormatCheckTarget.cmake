# Run clang-format on all given source files
foreach(source_file ${source_files})
    execute_process(
        COMMAND ${clangformat} -output-replacements-xml ${source_file}
        OUTPUT_VARIABLE replacements)
    if(replacements MATCHES "replacement ")
        list(APPEND unclean_files ${source_file})
    endif()
endforeach()

# Report unclean files (if any)
if(unclean_files)
    list(REMOVE_DUPLICATES unclean_files)
    string(REPLACE ";" "\n    " file_list "${unclean_files}")
    message(FATAL_ERROR
        "The following files do not adhere to the format:\n    ${file_list}")
endif()
