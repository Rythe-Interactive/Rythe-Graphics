#pragma once
#include <application/application.hpp>
#include <graphics/data/buffer.hpp>
#include <graphics/data/material.hpp>
#include <graphics/data/vertexarray.hpp>
#include <graphics/util/bindings.hpp>

#include <set>
#include <unordered_map>
#include <vector>

/**
 * @file model.hpp
 */

namespace rythe::rendering
{
	/**@class model
	 * @brief Struct containing all the buffer ids and the VAO needed for rendering.
	 */
	struct model
	{
		bool buffered;
		vertexarray vertexArray;
		buffer vertexBuffer;
		buffer colorBuffer;
		buffer normalBuffer;
		buffer uvBuffer;
		buffer tangentBuffer;
		buffer indexBuffer;

		std::vector<material_handle> materials;

		std::vector<sub_mesh> submeshes;
	};

	/**@class model_handle
	 * @brief Save to pass around handle to a model in the model cache.
	 */
	struct model_handle
	{
		rsl::id_type id;

		bool operator==(const model_handle& other) const { return id == other.id; }
		bool is_buffered() const;
		void buffer_data(const buffer& matrixBuffer) const;
		void overwrite_buffer(buffer& newBuffer, rsl::uint bufferID, bool perInstance = false) const;

		assets::asset<mesh> get_mesh() const;
		const model& get_model() const;
	};

	constexpr model_handle invalid_model_handle{invalid_id};

	class ModelCache
	{
		friend class renderer;
		friend struct model_handle;

	private:
		static sparse_map<rsl::id_type, model> m_models;
		static async::rw_spinlock m_modelLock;

		static async::rw_spinlock m_modelNameLock;
		static std::unordered_map<rsl::id_type, std::string> m_modelNames;

		static const model& get_model(rsl::id_type id);

	public:
		static std::string get_model_name(rsl::id_type id);

		static void overwrite_buffer(rsl::id_type id, buffer& newBuffer, rsl::uint bufferID, bool perInstance = false);
		static void buffer_model(rsl::id_type id, const buffer& matrixBuffer);
		static model_handle create_model(const std::string& name, const fs::view& file, assets::import_settings<mesh> settings = {});
		static model_handle create_model(const std::string& name);
		static model_handle create_model(const std::string& name, rsl::id_type meshId);
		static model_handle create_model(rsl::id_type meshId);
		static model_handle create_model(const std::string& name, assets::asset<mesh> mesh);
		static model_handle create_model(assets::asset<mesh> mesh);
		static model_handle get_handle(const std::string& name);
		static model_handle get_handle(rsl::id_type id);
		static assets::asset<mesh> get_mesh(const std::string& name);
		static assets::asset<mesh> get_mesh(rsl::id_type id);

		static void destroy_model(const std::string& name);
	};
} // namespace rythe::rendering

#if !defined(DOXY_EXCLUDE)
namespace std
{
	template <>
	struct hash<rythe::rendering::model_handle>
	{
		std::size_t operator()(rythe::rendering::model_handle const& handle) const noexcept
		{
			return static_cast<std::size_t>(handle.id);
		}
	};
} // namespace std
#endif
