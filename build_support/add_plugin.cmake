# Utiltity functions for building and installing LV2 plugins.

function(add_plugin plugin_name version)
        set(source ${plugin_name}/${plugin_name}.c)
        add_library(${plugin_name} SHARED ${source})
        target_link_libraries(${plugin_name} PUBLIC ${LV2_LIBRARIES})
        set_target_properties(${plugin_name} PROPERTIES PREFIX ""
                        VERSION ${version})

        # And install:
        set(root ${LV2_INSTALL_DIR}/${plugin_name}.lv2/)
        install(TARGETS ${plugin_name}
                DESTINATION ${root})
        # Then we install the turtle files:
        # TODO: The main turtle has to insert version number.
        install(CODE "")
        execute_process(COMMAND ....
                        INPUT_FILE plugin_template/manifest.ttl.in
                        OUTPUT_FILE ${root}/manifest.ttl)
        # TODO: The manifest file should add plugin_name appropriately and LIB_EXT suffix
        execute_process(COMMAND ....
                        INPUT_FILE ${plugin_name}/${plugin_name}.ttl
                        OUTPUT_FILE ${root}/${plugin_name}.ttl)
        # TODO: Process manifest.ttl.in file (basically a template)
        # TODO: Process .ttl file (insert version)

endfunction()
