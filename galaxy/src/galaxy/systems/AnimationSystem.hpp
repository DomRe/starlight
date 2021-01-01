///
/// AnimationSystem.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_SYSTEMS_ANIMATIONSYSTEM_HPP_
#define GALAXY_SYSTEMS_ANIMATIONSYSTEM_HPP_

#include "galaxy/ecs/System.hpp"
#include "galaxy/graphics/Camera.hpp"

namespace galaxy
{
	class core::World;

	namespace systems
	{
		///
		/// System that handles rendering of entities with a graphics::Sprite, TransformComponent, etc.
		///
		class AnimationSystem final : public ecs::System
		{
		public:
			///
			/// Constructor.
			///
			AnimationSystem();

			///
			/// Destructor.
			///
			virtual ~AnimationSystem();

			///
			/// Abstract implementation for processing events.
			///
			void events() override;

			///
			/// Abstract implementation for updating the system. Use the manager to retreive your components.
			///
			/// \param dt DeltaTime from gameloop.
			///
			void update(const double dt) override;

			///
			/// Render sprites / textures to screen.
			///
			/// \param camera Camera used for rendering.
			///
			void render(graphics::Camera& camera);

		private:
			///
			/// Pointer to entities.
			///
			core::World* m_world;
		};
	} // namespace systems
} // namespace galaxy

#endif