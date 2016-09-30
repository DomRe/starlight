//
//  System.hpp
//  REngine3
//
//  Created by reworks on 10/07/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef RENGINE3_SYSTEM_HPP_
#define RENGINE3_SYSTEM_HPP_

#include <map>

#include "re/types/Types.hpp"
#include "re/entity/Entity.hpp"

namespace re
{
	class System
	{
	public:
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Virtual destructor for systems.
		*/
		virtual ~System();

		/*
		* IMPORTS: id of entity to remove
		* EXPORTS: none
		* PURPOSE: Remove an entitys components from the system.
		*/
		virtual void RemoveEntity(sf::Uint64 e) = 0;

		/*
		* IMPORTS: id of entity to add and its component list.
		* EXPORTS: none
		* PURPOSE: Add an entitys components from the system. YOU NEED to call entitys list of system ids and push back the type id of the system your adding the entity to.
		*/
		virtual void AddEntity(Entity* e) = 0;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Get stored components.
		*/
		std::map<sf::Uint64, Entity*>& GetEntitys();

	protected:
		std::map<sf::Uint64, Entity*> m_entitys;
	};
}

#endif