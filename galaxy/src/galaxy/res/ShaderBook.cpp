///
/// ShaderBook.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include <filesystem>

#include <nlohmann/json.hpp>

#include "galaxy/fs/FileSystem.hpp"
#include "galaxy/scripting/JSONUtils.hpp"

#include "ShaderBook.hpp"

namespace galaxy
{
	namespace res
	{
		ShaderBook::ShaderBook(std::string_view json)
		{
			create_from_json(json);
		}

		ShaderBook::~ShaderBook()
		{
			clear();
		}

		void ShaderBook::create_from_json(std::string_view json)
		{
			auto path        = fmt::format("{0}{1}{2}", fs::s_root, fs::s_json, json);
			nlohmann::json j = json::parse_from_disk(path);

			nlohmann::json arr = j.at("shaderbook");
			std::for_each(arr.begin(), arr.end(), [&](const nlohmann::json& shader) {
				auto vs = std::filesystem::path {fmt::format("{0}{1}{2}", fs::s_root, fs::s_shaders, shader[0].get<std::string>())};
				auto fs = std::filesystem::path {fmt::format("{0}{1}{2}", fs::s_root, fs::s_shaders, shader[1].get<std::string>())};
				create(vs.stem().string(), vs.string(), fs.string());
			});
		}

		void ShaderBook::clear()
		{
			m_resources.clear();
		}
	} // namespace res
} // namespace galaxy