///
/// ShaderID.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_COMPONENTS_SHADERID_HPP_
#define GALAXY_COMPONENTS_SHADERID_HPP_

#include <string_view>

#include <nlohmann/json_fwd.hpp>

namespace galaxy
{
	namespace components
	{
		///
		/// Shader id component.
		///
		class ShaderID final
		{
		public:
			///
			/// Constructor.
			///
			ShaderID();

			///
			/// Argument constructor.
			///
			/// \param id ID of a shader in the shader resource cache.
			///
			ShaderID(std::string_view id);

			///
			/// JSON constructor.
			///
			/// \param json JSON defining object.
			///
			ShaderID(const nlohmann::json& json);

			///
			/// Move constructor.
			///
			ShaderID(ShaderID&&) noexcept;

			///
			/// Move assignment operator.
			///
			ShaderID& operator=(ShaderID&&) noexcept;

			///
			/// Destructor.
			///
			~ShaderID() noexcept = default;

		public:
			///
			/// ID of a shader in the shader resource cache.
			///
			std::string m_shader_id;

		private:
			///
			/// Copy assignment operator.
			///
			ShaderID& operator=(const ShaderID&) = delete;

			///
			/// Copy constructor.
			///
			ShaderID(const ShaderID&) = delete;
		};
	} // namespace components
} // namespace galaxy

#endif