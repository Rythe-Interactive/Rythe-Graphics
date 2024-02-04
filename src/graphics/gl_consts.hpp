#pragma once

#include <application/application.hpp>

namespace rythe::rendering::detail
{
	constexpr const rsl::uint64 gl_mask = 0xFFFFFFFF;
	constexpr const rsl::uint64 ryt_mask = ~gl_mask;

#define ryt_VERTEX_SHADER 1
#define ryt_FRAGMENT_SHADER 2
#define ryt_GEOMETRY_SHADER 3
#define ryt_TESS_EVALUATION_SHADER 4
#define ryt_TESS_CONTROL_SHADER 5

	const rsl::uint64 gl_ryt_vertex_shader = GL_VERTEX_SHADER + (static_cast<rsl::uint64>(ryt_VERTEX_SHADER) << 32);
	const rsl::uint64 gl_ryt_fragment_shader = GL_FRAGMENT_SHADER + (static_cast<rsl::uint64>(ryt_FRAGMENT_SHADER) << 32);
	const rsl::uint64 gl_ryt_geometry_shader = GL_GEOMETRY_SHADER + (static_cast<rsl::uint64>(ryt_GEOMETRY_SHADER) << 32);
	const rsl::uint64 gl_ryt_tess_evaluation_shader = GL_TESS_EVALUATION_SHADER + (static_cast<rsl::uint64>(ryt_TESS_EVALUATION_SHADER) << 32);
	const rsl::uint64 gl_ryt_tess_control_shader = GL_TESS_CONTROL_SHADER + (static_cast<rsl::uint64>(ryt_TESS_CONTROL_SHADER) << 32);

#define GL_ryt_VERTEX_SHADER rythe::rendering::detail::gl_ryt_vertex_shader
#define GL_ryt_FRAGMENT_SHADER rythe::rendering::detail::gl_ryt_fragment_shader
#define GL_ryt_GEOMETRY_SHADER rythe::rendering::detail::gl_ryt_geometry_shader
#define GL_ryt_TESS_EVALUATION_SHADER rythe::rendering::detail::gl_ryt_tess_evaluation_shader
#define GL_ryt_TESS_CONTROL_SHADER rythe::rendering::detail::gl_ryt_tess_control_shader

	inline unsigned long get_gl_type(unsigned long long v)
	{
		return static_cast<int>(v & gl_mask);
	}

	inline unsigned long get_ryt_type(unsigned long long v)
	{
		return static_cast<int>((v & ryt_mask) >> 32);
	}
} // namespace rythe::rendering::detail
