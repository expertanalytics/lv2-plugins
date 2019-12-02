# Utiltity functions for building and installing LV2 plugins.

function(add_plugin plugin_name)
        set(bundle ${plugin_name}.lv2)

        get_filename_component(build_bundle ${bundle}
                        REALPATH
                        BASE_DIR ${CMAKE_BINARY_DIR})

        file(MAKE_DIRECTORY ${build_bundle})

        set(source ${plugin_name}/${plugin_name}.c)
        set(target ${plugin_name})

        add_library(${target} SHARED ${source})
        target_link_libraries(${target} PUBLIC ${LV2_LIBRARIES})
        set_target_properties(${target} PROPERTIES 
                        PREFIX ""
                        SUFFIC ".${LIB_EXT}"
                        VERSION "1.0"
                        LIBRARY_OUTPUT_DIRECTORY ${build_bundle})
        # And install:
        set(root ${LV2_INSTALL_DIR})
        # Then we install the turtle 
        # Make manifest file:
        execute_process(COMMAND bash "-c" 
                       "cat ${PROJECT_SOURCE_DIR}/plugin_template/manifest.ttl.in | 
                        sed 's/@PLUGIN_NAME@/${plugin_name}/g;s/\@LIB_EXT\@/${LIB_EXT}/g'"
                        OUTPUT_FILE ${build_bundle}/manifest.ttl)
        # TODO: Make main turtle file:

        # Install files:
        install(DIRECTORY ${bundle} 
                DESTINATION ${root})
        install(FILES ${build_bundle}/manifest.ttl
                DESTINATION ${root}/${bundle})
        install(TARGETS ${target}
                DESTINATION ${root}/${bundle})
endfunction()
