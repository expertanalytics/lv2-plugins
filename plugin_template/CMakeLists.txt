set(source plugin_name_placeholder.c)
set(turtles manifest.ttl.in plugin_name_placeholder.ttl)

add_library(plugin_name_placeholder SHARED ${source})
target_link_libraries(plugin_name_placeholder PUBLIC ${LV2_LIBARIES})
set_target_properties(plugin_name_placeholder PROPERTIES PREFIX ""
                        VERSION "1.0")

# And install
set(instroot ${LV2_INSTALL_DIR}/plugin_name_place_holder.lv2/)
install(TARGETS plugin_name_placeholder
        DESTINATION ${instroot})
install(FILES ${turtles}
        DESTINATION ${instroot})
