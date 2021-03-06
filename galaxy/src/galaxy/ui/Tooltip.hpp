///
/// Tooltip.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_UI_TOOLTIP_HPP_
#define GALAXY_UI_TOOLTIP_HPP_

#include "galaxy/components/Text.hpp"
#include "galaxy/components/Transform.hpp"
#include "galaxy/graphics/Camera.hpp"
#include "galaxy/graphics/texture/Texture.hpp"
#include "galaxy/ui/Theme.hpp"

namespace galaxy
{
	namespace ui
	{
		///
		/// Tooltip for widgets.
		///
		class Tooltip final
		{
			friend class GUI;

		public:
			///
			/// Constructor.
			///
			Tooltip() noexcept;

			///
			/// Move constructor.
			///
			Tooltip(Tooltip&&) noexcept;

			///
			/// Move assignment operator.
			///
			Tooltip& operator=(Tooltip&&) noexcept;

			///
			/// Destructor.
			///
			~Tooltip() noexcept;

			///
			/// Create the tooltip.
			///
			/// \param text Text to draw on the tooltip.
			/// \param font Font to use.
			///
			void create(std::string_view text, std::string_view font);

			///
			/// Render the tooltip.
			///
			///
			void render();

			///
			/// Update the text.
			///
			/// \param text New text to display.
			///
			void update_text(std::string_view text);

			///
			/// Update tooltip position.
			///
			/// \param x Update tooltip x pos. Has mouse cursor width subtracted.
			/// \param y Update tooltip y pos. Has mouse cursor height subtracted.
			///
			void update_pos(double x, double y) noexcept;

			///
			/// Draw tooltip toggle.
			///
			/// \param can_draw True to allow tooltip to be drawn.
			///
			void can_draw(const bool can_draw) noexcept;

			///
			/// Can draw the tooltip.
			///
			/// \return Const boolean. True if tooltip is visible.
			///
			[[nodiscard]] const bool can_draw() const noexcept;

		private:
			///
			/// Copy constructor.
			///
			Tooltip(const Tooltip&) = delete;

			///
			/// Copy assignment operator.
			///
			Tooltip& operator=(const Tooltip&) = delete;

		private:
			///
			/// Draw tooltip toggle.
			///
			bool m_draw;

			///
			/// Text to display.
			///
			components::Text m_text;

			///
			/// Text transform.
			///
			components::Transform m_text_transform;

			///
			/// UI theme for tooltip.
			///
			Theme* m_theme;

			///
			/// Text shader cache.
			///
			graphics::Shader* m_text_shader;

			///
			/// Cursor size.
			///
			glm::vec2 m_cursor_size;
		};
	} // namespace ui
} // namespace galaxy

#endif