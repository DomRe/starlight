///
/// Grid.hpp
/// starmap
///
/// Refer to LICENSE.txt for more details.
///

#ifndef STARMAP_GRID_HPP_
#define STARMAP_GRID_HPP_

#include "nlohmann/json_fwd.hpp"

///
/// Core namespace.
///
namespace starmap
{
	///
	/// This element is only used in case of isometric orientation, and determines how tile overlays for terrain and collision information are rendered.
	///
	class Grid final
	{
	public:
		///
		/// Default constructor.
		///
		Grid() noexcept;

		///
		/// \brief Parse constructor.
		///
		/// Can throw exceptions.
		///
		/// \param json JSON structure/array containing Grid.
		///
		explicit Grid(const nlohmann::json& json);

		///
		/// Copy constructor.
		///
		Grid(const Grid&) = default;

		///
		/// Move constructor.
		///
		Grid(Grid&&) = default;

		///
		/// Destructor.
		///
		~Grid() = default;

		///
		/// \brief Parses json structure to member values; etc.
		///
		/// Can throws exceptions.
		///
		/// \param json JSON structure containing chunk array from root->layer.
		///
		void parse(const nlohmann::json& json);

		///
		/// Get cell height of tile grid.
		///
		/// \return Const int.
		///
		const int getHeight() const noexcept;

		///
		/// Get the orientation of the grid.
		///
		/// \return String, format: orthogonal (default) or isometric.
		///
		const std::string& getOrientation() const noexcept;

		///
		/// Get cell width of tile grid.
		///
		/// \return Const int.
		///
		const int getWidth() const noexcept;

	private:
		///
		/// Cell height of tile grid.
		///
		int m_height;

		///
		/// Orientation of the grid for the tiles in this tileset.
		///
		std::string m_orientation;

		///
		/// Cell width of tile grid.
		///
		int m_width;
	};
}

#endif