///
///  PhysicsComponent.hpp
///  rework
///
///  Created by reworks on 10/11/2016.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#ifndef REWORK_PHYSICSCOMPONENT_HPP_
#define REWORK_PHYSICSCOMPONENT_HPP_

#include "cereal/access.hpp"
#include "sol2/sol_forward.hpp"

class b2Body;

namespace re
{
	class PhysicsComponent
	{
		friend class cereal::access;

	public:
		///
		/// Constructor.
		///
		/// \param table sol::table containing data.
		///
		PhysicsComponent(const sol::table& table);

		///
		/// Destructor.
		///
		~PhysicsComponent();

		///
		/// Calls imgui debug functions. Don't call this, done for you by debugmanager.
		///
		void debug();

	public:
		b2Body* m_body;

	private:
		/// This method lets cereal know which data members to save.
		template<class Archive>
		void save(Archive& archive) const
		{
			archive(m_body->GetPosition().x, m_body->GetPosition().y, m_body->GetAngle(), m_body->GetAngularVelocity(), m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
		}

		/// This method lets cereal know which data members to load.
		template<class Archive>
		void load(Archive& archive)
		{
			float32 x, y, angle, angleVel, linearX, linearY = 0.0f;

			archive(x, y, angle, angleVel, linearX, linearY);

			m_body->SetTransform(b2Vec2(x, y), angle);
			m_body->SetAngularVelocity(angleVel);
			m_body->SetLinearVelocity(b2Vec2(linearX, linearY));
		}

		///
		/// Default constructor.
		/// Deleted.
		///
		PhysicsComponent() = delete;

		///
		/// Copy Constructor.
		/// Deleted.
		///
		PhysicsComponent(const PhysicsComponent&) = delete;

		///
		/// Move Constructor.
		/// Deleted.
		///
		PhysicsComponent(PhysicsComponent&&) = delete;
	};
}

#endif