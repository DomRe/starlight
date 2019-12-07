///
/// RenderSystem.hpp
/// galaxy
///
/// Created by reworks on 06/08/2016.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_RENDERSYSTEM_HPP_
#define GALAXY_RENDERSYSTEM_HPP_

#include "galaxy/types/System.hpp"
#include "galaxy/math/QuadTree.hpp"

galaxy
{
	///
	/// System that handles rendering of entities with a RenderComponent.
	///
	class RenderSystem final : public System
	{
	public:
		///
		/// Constructor.
		///
		/// \param quadTreeLevels Maximum depth of a quadtree.
		/// \param quadtreeMaxObjects Maximim number of entitys in a node.
		///
		RenderSystem(int quadTreeLevels = 5, int quadtreeMaxObjects = 10);

		///
		/// Destructor.
		///
		~RenderSystem() noexcept override;

		///
		/// Render entitys.
		/// 
		void render();

	private:
		///
		/// Default Constructor.
		/// Deleted.
		///
		RenderSystem() = delete;

		///
		/// \brief Update the system.
		///
		/// Dont actually call this, this is called by the world automatically.
		///
		/// \param dt Delta Time from update loop.
		/// \param registry Default entity registry.
		///
		void update(const double dt, entt::DefaultRegistry& registry) override;

	private:
		///
		/// Maximum number of levels the quadtree should have.
		///
		int m_quadTreeLevels;

		///
		/// Maximum number of renderable objects each node in the quadtree can have.
		///
		int m_quadTreeMaxObjects;

		///
		/// This is used to sort entities by Z-layer after figuring out which ones to render with the quadtree.
		///
		std::vector<entt::DefaultRegistry::entity_type> m_entitys;

		///
		/// The quadtree to process 2D screenspace with.
		///
		std::unique_ptr<QuadTree> m_quadtree;
	};
}

#endif