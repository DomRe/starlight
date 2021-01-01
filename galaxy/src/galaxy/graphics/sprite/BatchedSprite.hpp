///
/// BatchedSprite.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_SPRITE_BATCHEDSPRITE_HPP_
#define GALAXY_GRAPHICS_SPRITE_BATCHEDSPRITE_HPP_

#include <nlohmann/json_fwd.hpp>

#include "galaxy/graphics/shapes/Rect.hpp"
#include "galaxy/graphics/Transform.hpp"
#include "galaxy/graphics/vertex/VertexData.hpp"

namespace galaxy
{
	namespace graphics
	{
		///
		/// A sprite that does not contain a texture. Useful for when working with batches and texture atlas'.
		///
		class BatchedSprite : public Transform
		{
			friend class SpriteBatch;
			friend class Text;

		public:
			///
			/// Constructor.
			///
			BatchedSprite();

			///
			/// JSON constructor.
			///
			/// \param json JSON defining object.
			///
			BatchedSprite(const nlohmann::json& json);

			///
			/// Copy constructor.
			///
			BatchedSprite(const BatchedSprite&) = delete;

			///
			/// Move constructor.
			///
			BatchedSprite(BatchedSprite&&) = default;

			///
			/// Copy assignment operator.
			///
			BatchedSprite& operator=(const BatchedSprite&) = delete;

			///
			/// Move assignment operator.
			///
			BatchedSprite& operator=(BatchedSprite&&) = default;

			///
			/// Destructor.
			///
			virtual ~BatchedSprite();

			///
			/// Sets the texture region for the batched sprite.
			///
			/// \param region Region defined on the texture.
			/// \param z_level Z-Level of sprite.
			///
			void create(const graphics::Rect<float>& region, const unsigned int z_level);

			///
			/// Set opacity.
			///
			/// \param opacity Opacity range is from 0.0f (transparent) to 1.0f (opaque).
			///
			void set_opacity(const float opacity);

			///
			/// Set z-level.
			///
			/// \param z_level New z-level of sprite.
			///
			void set_z_level(const unsigned int z_level);

			///
			/// Update texquad region.
			///
			/// \param x New x position.
			///
			void update_x_region(const float x);

			///
			/// Update texquad region.
			///
			/// \param y New y position.
			///
			void update_y_region(const float y);

			///
			/// Update texquad region.
			///
			/// \param w Width.
			///
			void update_w_region(const float w);

			///
			/// Update texquad region.
			///
			/// \param h Height.
			///
			void update_h_region(const float h);

			///
			/// Update texquad region.
			///
			/// \param x New x position.
			/// \param y New y position.
			/// \param w Width.
			/// \param h Height.
			///
			void update_region(const float x, const float y, const float w, const float h);

			///
			/// Update texquad region.
			///
			/// \param quad New quad region.
			///
			void update_region(const graphics::Rect<float>& quad);

			///
			/// Get opacity.
			///
			/// \return Const float.
			///
			[[nodiscard]] const float opacity() const;

			///
			/// Get z-level.
			///
			/// \return Const unsigned int.
			///
			[[nodiscard]] const unsigned int z_level() const;

			///
			/// \brief Get texture width.
			///
			/// Is cached for performance.
			///
			/// \return Width as int. int over unsigned for compat with float.
			///
			[[nodiscard]] const int get_width() const;

			///
			/// \brief Get texture height.
			///
			/// Is cached for performance.
			///
			/// \return Height as int. int over unsigned for compat with float.
			///
			[[nodiscard]] const int get_height() const;

			///
			/// Get region.
			///
			/// \return Reference to a rectangle of floats.
			///
			[[nodiscard]] const graphics::Rect<float>& get_region() const;

		protected:
			///
			/// Opacity of BatchedSprite.
			///
			float m_opacity;

			///
			/// Z-Level
			///
			unsigned int m_z_level;

			///
			/// Offset of vertexs in a spritebatch.
			///
			unsigned int m_offset;

			///
			/// Region of texture used.
			///
			graphics::Rect<float> m_region;
		};
	} // namespace graphics
} // namespace galaxy

#endif