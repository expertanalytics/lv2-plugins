set(source simple_delay.c)
set(turtles manifest.ttl.in simple_delay.ttl)

add_library(simple_delay SHARED ${source})
target_link_libraries(simple_delay PUBLIC ${LV2_LIBARIES})
set_target_properties(simple_delay PROPERTIES PREFIX ""
                        VERSION "2.0"
                        SUFFIX ".so")

# And install
set(root ${LV2_INSTALL_DIR}/simple_delay.lv2/)
install(TARGETS simple_delay
        DESTINATION ${root})
install(FILES ${turtles}
        DESTINATION ${root})
