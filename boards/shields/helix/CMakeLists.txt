if (CONFIG_SHIELD_HELIX)
    target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/dpi_hook.c)
endif()
