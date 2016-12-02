//
//  AnimationSystem.cpp
//  REngine3
//
//  Created by reworks on 10/11/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//  Code modified from: https://github.com/miguelmartin75/anax/blob/master/examples/common/include/Systems/AnimationSystem.hpp
//  See original file for details.

#include "re/app/World.hpp"
#include "re/component/SpriteComponent.hpp"
#include "re/component/AnimationComponent.hpp"

#include "AnimationSystem.hpp"

namespace re
{
	AnimationSystem::~AnimationSystem()
	{
		m_entitys.clear();
	}

	void AnimationSystem::AutoSubmit(World* world)
	{
		for (auto& it : world->GetAlive())
		{
			if (it.second.Has<AnimationComponent>())
			{
				AddEntity(&it.second);
			}
		}
	}

	void AnimationSystem::AddEntity(Entity* e)
	{
		e->m_systemIds.emplace("AnimationSystem", std::type_index(typeid(AnimationSystem)));
		// we also want to adjust the first texture rectangle so it doesn't get missed out on...
		e->Get<SpriteComponent>()->setTextureRect(e->Get<AnimationComponent>()->m_animations[e->Get<AnimationComponent>()->m_activeAnimation][e->Get<AnimationComponent>()->m_currentFrame]);
		m_entitys.emplace(e->m_name, e);
	}

	void AnimationSystem::RemoveEntity(const std::string& name)
	{
		m_entitys.erase(name);
	}

	void AnimationSystem::Update(sf::Time dt)
	{
		for (auto& e : m_entitys)
		{
			auto animation = e.second->Get<AnimationComponent>();
			auto sprite = e.second->Get<SpriteComponent>();

			if (!animation->m_isPaused)
			{
				// add delta time
				animation->m_currentTime += dt;

				// if current time is bigger then the frame time advance one frame
				if (animation->m_currentTime >= animation->m_frameTime)
				{
					// reset time, but keep the remainder
					animation->m_currentTime = sf::milliseconds(animation->m_currentTime.asMilliseconds() % animation->m_frameTime.asMilliseconds());

					// get next Frame index
					if (animation->m_currentFrame + 1 < animation->m_animations[animation->m_activeAnimation].size())
						animation->m_currentFrame++;
					else
					{
						// animation has ended
						animation->m_currentFrame = 0; // reset to start

						if (!animation->m_isLooped)
						{
							animation->m_isPaused = true;
						}

					}

					sprite->setTextureRect(animation->m_animations[animation->m_activeAnimation][animation->m_currentFrame]);
				}
			}
		}
	}

	void AnimationSystem::Clean()
	{
		m_entitys.clear();
	}
}