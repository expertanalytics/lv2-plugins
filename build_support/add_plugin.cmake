# Utiltity functions for building and installing LV2 plugins.

function(add_plugin plugin_name version)
        set(source ${plugin_name}/${plugin_name}.c)
        # TODO: Process manifest.ttl.in file (basically a template)
        # TODO: Process .ttl file (insert version)
        add_library(${plugin_name} SHARED ${source})
        target_link_libraries(${plugin_name} PUBLIC ${LV2_LIBRARIES})
        set_target_properties(${plugin_name} PROPERTIES PREFIX ""
                        VERSION ${version})

        # And install:
        set(root ${LV2_INSTALL_DIR}/${plugin_name}.lv2/)
        install(TARGETS ${plugin_name}
                DESTINATION ${root})
        install(FILES ${turtles}
                DESTINATION ${root})
endfunction()
