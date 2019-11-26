set(source lowpass.c)
set(turtles manifest.ttl.in lowpass.ttl)

add_library(lowpass SHARED ${source})
target_link_libraries(lowpass PUBLIC ${LV2_LIBARIES})
set_target_properties(lowpass PROPERTIES PREFIX ""
                        VERSION "2.0")

# And install
set(lowpass_root ${LV2_INSTALL_DIR}/lowpass.lv2/)
install(TARGETS lowpass
        DESTINATION ${lowpass_root})
install(FILES ${turtles}
        DESTINATION ${lowpass_root})
