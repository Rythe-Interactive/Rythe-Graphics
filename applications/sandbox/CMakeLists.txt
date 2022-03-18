project(graphics_sandbox LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}")
add_executable(graphics_sandbox ${sources})
set_target_properties(graphics_sandbox PROPERTIES FOLDER applications)

rythe_configure_engine_application(graphics_sandbox)
