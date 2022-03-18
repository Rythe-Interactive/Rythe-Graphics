project(graphics LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}/src")
add_library(graphics ${RYTHE_LIBRARY_TYPE} ${sources})

rythe_configure_module(graphics)
rythe_copy_module_output(graphics rythe/engine/graphics)
