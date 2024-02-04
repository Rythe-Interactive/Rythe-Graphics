#pragma once
#include <application/application.hpp>
#include <graphics/data/buffer.hpp>

/**@file vertexarray.hpp
 */

namespace rythe::rendering
{
	/**@class vertexarray
	 * @brief Low level vertexarray object.
	 * @note Read more at <a href="https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object">khronos.org wiki.</a>
	 */
	struct vertexarray
	{
	private:
		// Managed resource with the VAO id, also has the responsibility of deleting the VAO after all copies of this renderbuffer have been destroyed.
		common::managed_resource<app::gl_id> m_id = common::managed_resource<app::gl_id>(nullptr);

	public:
		/**@brief Faux constructor. To prevent unnecessary GPU allocations the default constructor doesn't actually create a VAO.
		 *        This means that default initialized vertexarrays are invalid temporary objects until they get properly initialized.
		 */
		vertexarray() = default;

		/**@brief Main allocating constructor. This constructor actually creates the GPU side renderbuffer.
		 * @param t temporary message value that tells the compiler to use the right constructor.
		 */
		explicit vertexarray([[maybe_unused]] std::nullptr_t t);

		/**@brief Static function to generate a VAO. Alternative to the vertexarray(std::nullptr_t) constructor.
		 * @return vertexarray Newly created VAO.
		 */
		static vertexarray generate();

		void setAttribPointer(const buffer& buf, rsl::uint index, rsl::size_type size, GLenum type, bool normalized, rsl::size_type stride, rsl::size_type offset);

		void setAttribDivisor(rsl::uint index, rsl::uint divisor);

		/**@brief Bind the vertexarray to the current context. Useful for low level native rendering.
		 */
		void bind() const;

		/**@brief Release the vertexarray from the current context. Useful for low level native rendering.
		 */
		static void release();
	};
} // namespace rythe::rendering
