///
/// Text.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_MAP_TYPES_TEXT_HPP_
#define GALAXY_MAP_TYPES_TEXT_HPP_

#include <nlohmann/json_fwd.hpp>

namespace galaxy
{
	namespace map
	{
		///
		/// Data structure on a Text type object.
		///
		class Text final
		{
		public:
			///
			/// Default constructor.
			///
			Text();

			///
			/// Parse constructor.
			///
			/// \param json JSON structure/array containing ObjectLayer->Object->Text.
			///
			explicit Text(const nlohmann::json& json);

			///
			/// Default destructor.
			///
			~Text() = default;

			///
			/// Parse text level json.
			///
			/// \param json JSON structure/array containing ObjectLayer->Object->Text.
			///
			void parse(const nlohmann::json& json);

			///
			/// Get bold flag.
			///
			/// \return True if text is bolded.
			///
			[[nodiscard]] const bool is_bold() const;

			///
			/// Get colour as hex string.
			///
			/// \return String in format RRGGBB or AARRGGBB.
			///
			[[nodiscard]] std::string get_colour() const;

			///
			/// Get font family.
			///
			/// \return Font type in format: sans-serif (for example).
			///
			[[nodiscard]] std::string get_font_family() const;

			///
			/// Get horizontal alignment value.
			///
			/// \return String in format: center, right, justify or left.
			///
			[[nodiscard]] std::string get_h_align() const;

			///
			/// Get italics flag.
			///
			/// \return True if text is italic.
			///
			[[nodiscard]] const bool is_italic() const;

			///
			/// Gets kerning flag.
			///
			/// \return True if using kerning to place characters.
			///
			[[nodiscard]] const bool is_using_kerning() const;

			///
			/// Get pixel (font) size of text.
			///
			/// \return Const int. Pixel size - you will need to convert to font point size.
			///
			[[nodiscard]] const int get_pixel_size() const;

			///
			/// Get strikeout flag.
			///
			/// \return True if text has been struck out.
			///
			[[nodiscard]] const bool is_striked_out() const;

			///
			/// Get the text.
			///
			/// \return Actual text as a string.
			///
			[[nodiscard]] std::string get_text() const;

			///
			/// Get underline flag.
			///
			/// \return True if text is underlined.
			///
			[[nodiscard]] const bool is_underlined() const;

			///
			/// Get vertical alignment.
			///
			/// \return String in format: center, bottom or top.
			///
			[[nodiscard]] std::string get_v_align() const;

			///
			/// Get wrapped flag.
			///
			/// \return True if text is wrapped within object bounds.
			///
			[[nodiscard]] const bool is_wrapped() const;

		private:
			///
			/// Whether to use a bold font.
			///
			bool m_bold;

			///
			/// Hex-formatted color (#RRGGBB or #AARRGGBB) (default: #000000).
			///
			std::string m_color;

			///
			/// Font family.
			///
			std::string m_font_family;

			///
			/// Horizontal alignment.
			///
			std::string m_halign;

			///
			/// Whether to use an italic font.
			///
			bool m_italic;

			///
			/// Whether to use kerning when placing characters.
			///
			bool m_kerning;

			///
			/// Pixel size of font.
			///
			int m_pixel_size;

			///
			/// Whether to strike out the text.
			///
			bool m_strike_out;

			///
			/// Text.
			///
			std::string m_text;

			///
			/// Whether to underline the text.
			///
			bool m_underline;

			///
			/// Vertical alignment.
			///
			std::string m_valign;

			///
			/// Whether the text is wrapped within the object bounds.
			///
			bool m_wrap;
		};
	} // namespace map
} // namespace galaxy

#endif