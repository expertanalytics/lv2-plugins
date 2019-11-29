# Utiltity functions for building and installing LV2 plugins.

function(add_plugin plugin_name)
        set(bundle ${plugin_name}.lv2)
        file(MAKE_DIRECTORY ${bundle})
        set(source ${plugin_name}/${plugin_name}.c)
        set(target ${plugin_name})
        add_library(${target} SHARED ${source})
        target_link_libraries(${target} PUBLIC ${LV2_LIBRARIES})
        set_target_properties(${target} PROPERTIES 
                        PREFIX ""
                        SUFFIC ".${LIB_EXT}"
                        VERSION "1.0")

        # And install:
        set(root ${LV2_INSTALL_DIR})
        # Then we install the turtle 
        # TODO: The main turtle has to insert version number.
        # Make manifest file:
        execute_process(COMMAND bash "-c" 
                       "cat ${PROJECT_SOURCE_DIR}/plugin_template/manifest.ttl.in | 
                        sed 's/@PLUGIN_NAME@/${plugin_name}/g;s/\@LIB_EXT\@/${LIB_EXT}/g'"
                        OUTPUT_FILE ${bundle}/manifest.ttl)
        install(DIRECTORY ${bundle} 
                DESTINATION ${root})
#install(CODE "execute_process(COMMAND deploy_turtle.sh -m ${plugin_name} dylib
#               OUTPUT_FILE ${root}/manifest.ttl)")
#execute_process(COMMAND ....
#                        INPUT_FILE plugin_template/manifest.ttl.in
#                        OUTPUT_FILE ${root}/manifest.ttl)
        # TODO: The manifest file should add plugin_name appropriately and LIB_EXT suffix
        #execute_process(COMMAND ....
#                INPUT_FILE ${plugin_name}/${plugin_name}.ttl
#                        OUTPUT_FILE ${root}/${plugin_name}.ttl)
        # TODO: Process manifest.ttl.in file (basically a template)
        # TODO: Process .ttl file (insert version)

endfunction()
