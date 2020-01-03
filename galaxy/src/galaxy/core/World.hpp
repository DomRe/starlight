///
/// World.hpp
/// galaxy
///
/// Created by reworks on 09/07/2016.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_WORLD_HPP_
#define GALAXY_WORLD_HPP_

#include <typeindex>
#include <functional>
#include <unordered_map>

#include "galaxy/types/System.hpp"
#include "galaxy/libs/sol2/sol.hpp"
#include "galaxy/libs/loguru/loguru.hpp"

#include "galaxy/libs/entt/core/hashed_string.hpp"

namespace galaxy
{
	///
	/// The World class. Contains the entitys and systems and other library stuff, like the main lua state.
	///
	class World final
	{
	public: 
		///
		/// Construct World.
		///
		World();

		///
		/// Cleans up world.
		///
		~World() noexcept;

		///
		/// Register an entity.
		///
		/// \param script Script file in the VirtualFS.
		///
		/// \return Entity created.
		///
		entt::DefaultRegistry::entity_type createEntity(const std::string& script);

		///
		/// Automatically create a batch of entitys from a script.
		///
		/// \param script Script file containing all the entity/script (k/v) to register.
		///
		void createEntities(const std::string& script);

		///
		/// \brief Create a batch of entities that all use one type of script.
		///
		/// Script is the same as a normal entity script but it also has an entityCount =;
		///
		/// \param script Script file containing entities information.
		///
		void createDuplicateEntities(const std::string& script);
		
		///
		/// Update the world.
		///
		/// \param dt timePerFrame from application loop, or delta time.
		/// 
		void update(const double dt);

		///
		/// Registers a tag with the world.
		///
		/// \param name - Name of tag in string format i.e. "PlayerTag".
		///
		template<typename Tag>
		void registerTag(const std::string& name);

		///
		/// Registers a component with the world.
		///
		/// \param name - Name of component class in string format i.e. "AnimationComponent".
		///
		template<typename Component>
		void registerComponent(const std::string& name);

		///
		/// Registers a system with the world.
		///
		/// \param args Argument(s) for system contructor.
		///
		template<typename System, typename... Args>
		void registerSystem(Args&&... args);

		///
		/// Retrieve a system.
		///
		/// \return Returns a pointer to the system object.
		///
		template<typename System>
		System* getSystem();

		///
		/// \brief Remove a system.
		///
		/// This de-registers the system, so you will need to call World::registerSystem to use it again.
		///
		template<typename System>
		void remove();

	public:
		///
		/// The registry containing all the game entities.
		///
		entt::DefaultRegistry m_registry;

		///
		/// The path to the folder containing game scripts.
		///
		std::string m_scriptFolderPath;

		///
		/// The path to the folder containing game textures.
		///
		std::string m_textureFolderPath;

		///
		/// The path to the folder containing game music.
		///
		std::string m_musicFolderPath;

		///
		/// The path to the folder containing game sound effects.
		///
		std::string m_soundFolderPath;

		///
		/// The path to the folder containing game font files.
		std::string m_fontFolderPath;

	private:
		///
		/// Used to allow for tag assigning without having to know the tag type.
		///
		std::unordered_map<entt::HashedString::hash_type, std::function<void(const entt::DefaultRegistry::entity_type, const sol::table&)>> m_tagAssign;

		///
		/// Used to allow for component assigning without having to know the tag type.
		///
		std::unordered_map<entt::HashedString::hash_type, std::function<void(const entt::DefaultRegistry::entity_type, const sol::table&)>> m_componentAssign;

		///
		/// Systems storage.
		///
		std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;
	};

	template<typename Tag>
	inline void World::registerTag(const std::string& name)
	{
		// Create hashed string to use.
		entt::HashedString hs(name.c_str());

		// Make sure there are no duplicate tags before registering.
		if (m_tagAssign.find(hs) != m_tagAssign.end())
		{
			LOG_S(WARNING) << "Attempted to register duplicate tag: " << name;
		}
		else
		{
			m_tagAssign.emplace(hs, [this](const entt::DefaultRegistry::entity_type entity, const sol::table& table)
			{
				m_registry.assign<Tag>(entt::tag_t{}, entity, table);
			});
		}
	}

	template<typename Component>
	inline void World::registerComponent(const std::string& name)
	{
		// Create hashed string to use.
		entt::HashedString hs(name.c_str());

		// Make sure there are no duplicate components for the hashmap before registering.
		if (m_componentAssign.find(hs) != m_componentAssign.end())
		{
			LOG_S(WARNING) << "Attempted to register duplicate component: " << name;
		}
		else
		{
			m_componentAssign.emplace(hs, [this](const entt::DefaultRegistry::entity_type entity, const sol::table& table)
			{
				m_registry.assign<Component>(entity, table);
			});
		}
	}

	template<typename System, typename... Args>
	inline void World::registerSystem(Args&&... args)
	{
		// Get type index to use as key.
		std::type_index t(typeid(System));

		// Make sure no duplicate systems when registering.
		if (m_systems.find(t) != m_systems.end())
		{
			LOG_S(WARNING) << "Attempted to register duplicate system!";
		}
		else
		{
			// Create system at system type by forwarding arguments.
			m_systems[t] = std::make_unique<System>(std::forward<Args>(args)...);
		}
	}

	template<typename System>
	inline System* World::getSystem()
	{
		// Return a pointer to the system of the type System.
		return dynamic_cast<System*>(m_systems[typeid(System)].get());
	}

	template<typename System>
	inline void World::remove()
	{
		// Get type index to use as key.
		std::type_index t(typeid(System));

		// Check to make sure system exists.
		if (m_systems.find(t) != m_systems.end())
		{
			// Then call the systems destructor and erase it from the map.
			m_systems[t].reset();
			m_systems.erase(t);
		}
		else
		{
			LOG_S(WARNING) << "Attempted to remove non-existent system id: " << std::string(t.name);
		}
	}
}

#endif