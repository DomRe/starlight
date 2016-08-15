//
//  RenderSystem.hpp
//  REngine3
//
//  Created by reworks on 6/08/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef RENGINE3_RENDERSYSTEM_HPP_
#define RENGINE3_RENDERSYSTEM_HPP_


#include "re/graphics/Group.hpp"
#include "re/systems/System.hpp"

namespace re
{
	class RenderSystem : public System
	{
	public:
		/*
		* IMPORTS: Number of groups. Think "layers". Each group is a layer of entitys to render.
		* EXPORTS: none
		* PURPOSE: Construct the system.
		*/
		RenderSystem(int numOfGroups);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean up the renderer.
		*/
		~RenderSystem() override;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Submit all entitys to the system.
		*/
		void Submit();
		
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Update the system. Mainly for animations
		*/
		void Update();

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean up the entitys.
		*/
		void Render();

	private:
		std::vector<std::unique_ptr<Group>> m_groups;
	};
}

#endif