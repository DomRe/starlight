///
/// SpriteBatch.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_SPRITE_SPRITEBATCH_HPP_
#define GALAXY_GRAPHICS_SPRITE_SPRITEBATCH_HPP_

#include "galaxy/graphics/sprite/BatchedSprite.hpp"
#include "galaxy/graphics/texture/BaseTexture.hpp"

namespace galaxy
{
	namespace graphics
	{
		///
		/// Everything you need to draw a SpriteBatch.
		///
		class SpriteBatch final : public VertexData
		{
		public:
			///
			/// Argument constructor.
			///
			/// \param max_quads Maximum number of quads allowed for this spritebatch.
			///
			explicit SpriteBatch(const unsigned int max_quads);

			///
			/// Copy constructor.
			///
			SpriteBatch(const SpriteBatch&) = delete;

			///
			/// Move constructor.
			///
			SpriteBatch(SpriteBatch&&) = delete;

			///
			/// Copy assignment operator.
			///
			SpriteBatch& operator=(const SpriteBatch&) = delete;

			///
			/// Move assignment operator.
			///
			SpriteBatch& operator=(SpriteBatch&&) = delete;

			///
			/// Destructor.
			///
			virtual ~SpriteBatch();

			///
			/// Set the texture to use.
			///
			/// \param texture Texture to use when drawing batched sprites. Must not be nullptr.
			///
			void set_texture(BaseTexture* texture);

			///
			/// Add a batched sprite to the spritebatch.
			///
			/// \param sprite Sprite to add. Must not be nullptr.
			///
			void add(BatchedSprite* sprite);

			///
			/// Update spritebatch vertexs.
			///
			void update();

			///
			/// \brief Update spritebatch vertexs.
			///
			/// Apply a transform to all batched sprites. Checks if transform is dirty first.
			///
			/// \param transform Provide a global transform to apply to all batched sprites ontop of their transforms.
			///
			void update(Transform* transform);

			///
			/// Clears the spritebatch of data.
			///
			void clear();

			///
			/// Bind to OpenGL.
			///
			void bind();

			///
			/// Unbind from OpenGL.
			///
			void unbind();

			///
			/// Gets the number of actual used indicies in a spritebatch.
			///
			/// \return Const uint.
			///
			[[nodiscard]] const unsigned int get_used_index_count() const;

			///
			/// Get width.
			///
			/// \return Const uint.
			///
			[[nodiscard]] const unsigned int get_width() const;

			///
			/// Get height.
			///
			/// \return Const uint.
			///
			[[nodiscard]] const unsigned int get_height() const;

		private:
			///
			/// Constructor.
			///
			SpriteBatch() = delete;

			///
			/// \brief Sort sprites by z level.
			///
			/// Sprites are sorted according to z level.
			/// Those with same level are left in the order that they are in when they are added with begin().
			///
			void sort();

			///
			/// Flag to update renderdata if there are changes.
			///
			bool m_update_renderdata;

			///
			/// Offset tracker.
			///
			unsigned int m_offset;

			///
			/// Max # of quads.
			///
			unsigned int m_max_quads;

			///
			/// Max # of vertexs.
			///
			unsigned int m_max_vertexs;

			///
			/// Max # of indexs.
			///
			unsigned int m_max_indexs;

			///
			/// Index count.
			///
			unsigned int m_used_indexs;

			///
			/// Pointer to texture to use.
			///
			BaseTexture* m_texture;

			///
			/// Array of batched sprites.
			///
			std::vector<BatchedSprite*> m_sprites;

			///
			/// Vertexs of spritebatch.
			///
			std::vector<BatchedVertex> m_vertexs;
		};
	} // namespace graphics
} // namespace galaxy

#endif