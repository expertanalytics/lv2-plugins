# Utiltity functions for building and installing LV2 plugins.

function(add_plugin plugin_name)
        # Set bundle path
        set(bundle ${plugin_name}.lv2)

        get_filename_component(build_bundle ${bundle}
                        REALPATH
                        BASE_DIR ${CMAKE_BINARY_DIR})
        file(MAKE_DIRECTORY ${build_bundle})
        # Files in bundle
        set(source ${plugin_name}/${plugin_name}.c)
        set(target ${plugin_name})
        set(turtle ${plugin_name}/${plugin_name}.ttl)
        set(manifest ${plugin_name}/manifest.ttl)

        # Get version:
        file(READ ${plugin_name}/version.txt
                version)
        message(STATUS "Version is ${version}")
        string(STRIP ${version} version) # Strip trailing whitespaces
        # Parse into major- and minor version
        string(REPLACE "." ";" vrs_list ${version})
        list(GET vrs_list 0 majV)
        list(GET vrs_list 1 minV)
        
        # Add and link library
        add_library(${target} SHARED ${source})
        target_link_libraries(${target} PUBLIC ${LV2_LIBRARIES})
        set_target_properties(${target} PROPERTIES 
                        PREFIX ""
                        SUFFIC ".${LIB_EXT}"
                        VERSION ${version}
                        LIBRARY_OUTPUT_DIRECTORY ${build_bundle})
        # Make main turtle file
        execute_process(COMMAND bash "-c"
                        "cat ${PROJECT_SOURCE_DIR}/${turtle} |
                        sed 's/@VERSION@/lv2:minorVersion ${majV} ;\\\n\
                        lv2:microVersion ${minV} ; /g'"
                        OUTPUT_FILE ${build_bundle}/${plugin_name}.ttl)

        # And install:
        set(root ${LV2_INSTALL_DIR})
        install(FILES ${manifest}
                DESTINATION ${root}/${bundle})
        install(FILES ${build_bundle}/${plugin_name}.ttl
                DESTINATION ${root}/${bundle})
        install(TARGETS ${target}
                DESTINATION ${root}/${bundle})
endfunction()
