///
/// TextureFilters.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_TEXTURE_TEXTUREFILTERS_HPP_
#define GALAXY_GRAPHICS_TEXTURE_TEXTUREFILTERS_HPP_

namespace galaxy
{
	namespace graphics
	{
		///
		/// Enum contaning GL texture filtering options.
		///
		enum class TextureFilter : int
		{
			///
			/// Produces blocky/pixellated texture patterns.
			/// Think 8-bit.
			///
			NEAREST,

			///
			/// Attempts to smooth texture pattern. Less visible pixels.
			///
			LINEAR,

			///
			/// Takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
			///
			NEAREST_MIPMAP_NEAREST,

			///
			/// Takes the nearest mipmap level and samples that level using linear interpolation.
			///
			LINEAR_MIPMAP_NEAREST,

			///
			/// Linearly interpolates between the two mipmaps that most closely match the size of a pixel
			/// and samples the interpolated level via nearest neighbor interpolation.
			///
			NEAREST_MIPMAP_LINEAR,

			///
			/// Linearly interpolates between the two closest mipmaps and samples the interpolated
			/// level via linear interpolation.
			///
			LINEAR_MIPMAP_LINEAR
		};
	} // namespace graphics
} // namespace galaxy

#endif