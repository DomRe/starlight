///
/// BaseTexture.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_TEXTURE_BASETEXTURE_HPP_
#define GALAXY_GRAPHICS_TEXTURE_BASETEXTURE_HPP_

#include <string_view>

#include "galaxy/graphics/texture/Filters.hpp"

namespace galaxy
{
	namespace graphics
	{
		class BaseTexture
		{
		public:
			///
			/// Move constructor.
			///
			BaseTexture(BaseTexture&&) noexcept;

			///
			/// Move assignment operator.
			///
			BaseTexture& operator=(BaseTexture&&) noexcept;

			///
			/// Virtual destructor.
			///
			virtual ~BaseTexture() noexcept;

			///
			/// Saves texture to file on disk.
			///
			/// \param file Path (including filename) to save file to.
			///
			void save(std::string_view file);

			///
			/// Activate texture context.
			///
			virtual void bind() noexcept = 0;

			///
			/// Deactivate texture context.
			///
			virtual void unbind() noexcept = 0;

			///
			/// \brief Clamps texture to edges.
			///
			/// Clamps the coordinates between 0 and 1.
			/// The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
			///
			void clamp_to_edge() noexcept;

			///
			/// \brief Clamps to the border.
			///
			/// Coordinates outside the range are now given a user-specified border color.
			///
			void clamp_to_border() noexcept;

			///
			/// Makes the texture repeat over its verticies.
			///
			void set_repeated() noexcept;

			///
			/// Mirrors the texture.
			///
			void set_mirrored() noexcept;

			///
			/// Set ansiotropic filtering level.
			///
			/// \param level 2, 4, 8, etc...
			///
			void set_anisotropy(const unsigned int level) noexcept;

			///
			/// Set filter when texture is downscaled in OpenGL.
			///
			template<min_filter Filter>
			void set_minify_filter() noexcept;

			///
			/// Set filter when texture would be scaled up in OpenGL.
			///
			template<mag_filter Filter>
			void set_magnify_filter() noexcept;

			///
			/// \brief Get texture width.
			///
			/// Is cached for performance.
			///
			/// \return Width as int. int over unsigned for compat with float.
			///
			[[nodiscard]] const int get_width() const noexcept;

			///
			/// \brief Get texture height.
			///
			/// Is cached for performance.
			///
			/// \return Height as int. int over unsigned for compat with float.
			///
			[[nodiscard]] const int get_height() const noexcept;

			///
			/// Get Textures current Ansiotrophy level.
			///
			/// \return Const int.
			///
			[[nodiscard]] const int get_aniso_level() noexcept;

			///
			/// Gets internal OpenGL id.
			///
			/// \return Const unsigned int.
			///
			[[nodiscard]] const unsigned int gl_texture() const noexcept;

		protected:
			///
			/// Constructor.
			///
			BaseTexture() noexcept;

		protected:
			///
			/// OpenGL texture handle.
			///
			unsigned int m_texture;

			///
			/// Cached texture width.
			///
			int m_width;

			///
			/// Cached texture height.
			///
			int m_height;

		private:
			///
			/// Copy constructor.
			///
			BaseTexture(const BaseTexture&) = delete;

			///
			/// Copy assignment operator.
			///
			BaseTexture& operator=(const BaseTexture&) = delete;
		};

		template<min_filter Filter>
		inline void BaseTexture::set_minify_filter() noexcept
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter::value);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		template<mag_filter Filter>
		inline void BaseTexture::set_magnify_filter() noexcept
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter::value);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	} // namespace graphics
} // namespace galaxy

#endif