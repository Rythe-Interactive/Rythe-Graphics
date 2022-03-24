project(graphics LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}/src")
add_library(graphics ${RYTHE_LIBRARY_TYPE} ${sources})

rythe_add_third_party(
	CURRENT graphics
	LIBRARY glfw
	PATH "${RYTHE_DIR_ENGINE}/graphics/third_party/glfw"
	INCLUDE "${RYTHE_DIR_ENGINE}/graphics/third_party/glfw/include"
	FOLDER "third_party/glfw3"
	FOLDER_TARGETS glfw
)

rythe_add_third_party(
	CURRENT graphics
	LIBRARY imgui
	PATH "${RYTHE_DIR_ENGINE}/graphics/third_party/imgui"
	INCLUDE "${RYTHE_DIR_ENGINE}/graphics/third_party/"
	FOLDER "third_party"
	FOLDER_TARGETS imgui
)

rythe_configure_module(graphics)
rythe_copy_module_output(graphics rythe/engine/graphics)
