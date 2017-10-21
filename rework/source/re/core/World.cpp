//
//  World.cpp
//  rework
//
//  Created by reworks on 9/07/2016.
//  Copyright (c) 2017 reworks. All rights reserved.
//

#include <map>

#include "re/utils/Log.hpp"
#include "re/services/VFS.hpp"
#include "re/services/ServiceLocator.hpp"
#include "re/components/AnimationComponent.hpp"
#include "re/components/CollisionComponent.hpp"
#include "re/components/LayerComponent.hpp"
#include "re/components/ParallaxComponent.hpp"
#include "re/components/PhysicsComponent.hpp"
#include "re/components/SpriteComponent.hpp"
#include "re/components/TextComponent.hpp"
#include "re/components/TransformComponent.hpp"

#include "World.hpp"

namespace re
{
	World::World()
	:m_entityManager(m_eventManager), m_systemManager(m_entityManager, m_eventManager)
	{
	}

	World::~World()
	{
	}

	void World::createEntity(const std::string& script)
	{
		std::string scrData = Locator::get<VFS>()->openAsString(script);

		sol::state lua;
		lua.script(scrData);
		sol::table components = lua.get<sol::table>("entity");
		
		ex::Entity e = m_entityManager.create();

		// Get key-value pairs from table
		std::map<std::string, sol::table> kvp;
		components.for_each([&](std::pair<sol::object, sol::object> pair) {
			kvp.insert({ pair.first.as<std::string>(), pair.second.as<sol::table>() });
		});

		if (components.get<bool>("special"))
		{
			m_entitys.emplace(components.get<std::string>("name"), e);
			kvp.erase("name");
			m_entityScripts.emplace(script, scrData);
		}
		
		kvp.erase("special");

		for (auto& it : kvp)
		{
			m_componentAssign[it.first](e, it.second);
		}
	}

	void World::createEntities(const std::string& batchScript)
	{
		sol::state lua;
		lua.script(Locator::get<VFS>()->openAsString(batchScript));

		sol::table world = lua.get<sol::table>("world");
		sol::table entitylist = world.get<sol::table>("entitys");

		// Get key-value pairs from table
		std::map <int, std::string> kvp;
		entitylist.for_each([&](std::pair<sol::object, sol::object> pair) {
			kvp.insert({ pair.first.as<int>(), pair.second.as<std::string>() });
		});

		if (kvp.empty())
		{
			BOOST_LOG_TRIVIAL(error) << "Attempted to register an empty entity script." << std::endl;
			return;
		}

		for (auto& it : kvp)
		{
			std::string scrData = Locator::get<VFS>()->openAsString(it.second);
			
			lua.script(scrData);
			sol::table components = lua.get<sol::table>("entity");

			ex::Entity e = m_entityManager.create();

			// Get key-value pairs from table
			std::map <std::string, sol::table> m_ekv;
			components.for_each([&](std::pair<sol::object, sol::object> pair) {
				m_ekv.insert({ pair.first.as<std::string>(), pair.second.as<sol::table>() });
			});

			if (components.get<bool>("special"))
			{
				m_entitys.emplace(components.get<std::string>("name"), e);
				m_ekv.erase("name");
				m_entityScripts.emplace(it.second, scrData);
			}

			m_ekv.erase("special");

			for (auto& eit : m_ekv)
			{
				m_componentAssign[eit.first](e, eit.second);
			}
		}
	}

	void World::update(double dt)
	{
		m_systemManager.update_all(dt);
	}
}