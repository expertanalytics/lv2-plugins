set(source simple_delay.c)
set(turtles manifest.ttl.in simple_delay.ttl)

add_library(simple_delay SHARED ${source})
target_link_libraries(simple_delay PUBLIC ${LV2_LIBARIES})
set_target_properties(simple_delay PROPERTIES PREFIX ""
                        VERSION "2.0")

# And install
set(simple_delay_root ${LV2_INSTALL_DIR}/simple_delay.lv2/)
install(TARGETS simple_delay
        DESTINATION ${simple_delay_root})
install(FILES ${turtles}
        DESTINATION ${simple_delay_root})
