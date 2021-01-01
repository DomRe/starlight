///
/// World.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_CORE_WORLD_HPP_
#define GALAXY_CORE_WORLD_HPP_

#include <bitset>

#include <nlohmann/json_fwd.hpp>

#include "galaxy/ecs/ComponentSet.hpp"
#include "galaxy/ecs/System.hpp"
#include "galaxy/meta/UniqueID.hpp"

namespace galaxy
{
	///
	/// Predefinition of unique id structure for components.
	///
	using CUniqueID = meta::UniqueID<struct ComponentUniqueID>;

	///
	/// Predefinition of unique id structure for systems.
	///
	using SUniqueID = meta::UniqueID<struct SystemUniqueID>;

	///
	/// Container for retrieval of entities in operate() function.
	///
	using EntitysWithCounters = robin_hood::unordered_map<ecs::Entity, int>;

	///
	/// Shorthand for component factory map.
	///
	using ComponentFactory = robin_hood::unordered_map<std::string, std::function<void(const ecs::Entity, const nlohmann::json&)>>;

	///
	/// Concept to ensure a system is actually derived from a System.
	///
	template<typename Type>
	concept is_system = std::derived_from<Type, ecs::System>;

	namespace core
	{
		///
		/// Manages the entities and systems and other library stuff, like the main lua state,
		/// and the physics world.
		///
		class World final
		{
		public:
			///
			/// Constructor.
			///
			World();

			///
			/// Copy constructor.
			///
			World(const World&) = delete;

			///
			/// Move constructor.
			///
			World(World&&) = delete;

			///
			/// Copy assignment operator.
			///
			World& operator=(const World&) = delete;

			///
			/// Move assignment operator.
			///
			World& operator=(World&&) = delete;

			///
			/// Destructor.
			///
			~World();

			///
			/// Process system events.
			///
			void events();

			///
			/// Update all systems.
			///
			/// \param dt "Lag" time to pass to systems.
			///
			void update(const double dt);

			///
			/// Create an entity.
			///
			/// \return An entity with a creation bit flag.
			///
			[[maybe_unused]] const ecs::Entity create();

			///
			/// Create an entity with a name.
			///
			/// \param debug_name Debug name for identification purposes.
			///
			/// \return An entity with a creation bit flag.
			///
			[[maybe_unused]] const ecs::Entity create(std::string_view debug_name);

			///
			/// \brief Create an entity from a JSON file.
			///
			/// If your using this make sure you have called register_component().
			///
			/// \param file Filepath to the json.
			///
			/// \return Created entity.
			///
			const ecs::Entity create_from_json(std::string_view file);

			///
			/// Set a flag on a component.
			///
			/// \param entity Entity to set flag on.
			///
			template<meta::is_flag Flag>
			void set_flag(const ecs::Entity entity);

			///
			/// UNset a flag on a component.
			///
			/// \param entity Entity to unset flag on.
			///
			template<meta::is_flag Flag>
			void unset_flag(const ecs::Entity entity);

			///
			/// Registers a component definition.
			///
			/// \param name Name of component class in string format i.e. "graphics::AnimatedBatchSprite".
			///
			template<meta::is_class Component>
			void register_component(std::string_view name);

			///
			/// Add (construct) a component for an entity.
			/// Use template to specify type of component being created.
			///
			/// \param entity ecs::Entity to assossiate the component with.
			/// \param args Constructor arguments for the component.
			///
			/// \return Pointer to newly added component.
			///
			template<meta::is_class Component, typename... Args>
			Component* create_component(const ecs::Entity entity, Args&&... args);

			///
			/// Retrieve a component assosiated with an entity.
			/// Template type is type of component to get.
			///
			/// \param entity ecs::Entity component is assosiated with.
			///
			/// \return Pointer to component of type Component.
			///
			template<meta::is_class Component>
			Component* get(const ecs::Entity entity);

			///
			/// Remove a component assosiated with an entity.
			/// Template type is type of component to remove.
			///
			/// \param entity ecs::Entity component is assosiated with.
			///
			template<meta::is_class Component>
			void remove(const ecs::Entity entity);

			///
			/// Destroys an entity and all associated components.
			///
			/// \param entity ecs::Entity to destroy.
			///
			void destroy(const ecs::Entity entity);

			///
			/// Check if an entity exists.
			///
			/// \param entity ecs::Entity to verify.
			///
			/// \return True if entity does exist.
			///
			[[nodiscard]] const bool has(const ecs::Entity entity);

			///
			/// Check if an entity is enabled.
			///
			/// \param entity ecs::Entity to check.
			///
			/// \return True if entity is enabled.
			///
			[[nodiscard]] const bool is_enabled(const ecs::Entity entity);

			///
			/// Assign a name to an entity.
			///
			/// \param entity ecs::Entity to assign name to.
			/// \param debug_name Name to assign to entity.
			///
			/// \return True if successful.
			///
			[[maybe_unused]] bool assign_name(const ecs::Entity entity, std::string_view debug_name);

			///
			/// Get entity fropm debug name.
			///
			/// \param debugName Name of entity to retrieve.
			///
			/// \return The entity.
			///
			[[nodiscard]] ecs::Entity find_from_name(std::string_view debug_name);

			///
			/// Retrieve multiple components assosiated with an entity.
			/// Template type is type of components to get.
			///
			/// \param entity ecs::Entity components are assosiated with.
			///
			/// \return Tuple of pointers to components.
			///
			template<meta::is_class... Component>
			std::tuple<Component*...> get_multi(const ecs::Entity entity);

			///
			/// \brief Iterate over a set of components of a set of types and manipulate their data.
			///
			/// The components to manipulate are specified in the template parameter.
			///
			/// \param lambda A lambda function that manipulates the components.
			///		          For example:
			/*
								manager.operate<a, b>([](const ecs::Entity entity, a* ca, b* cb)
								{
									cb->var = 500;
								});
								*/
			///
			template<meta::is_class... Components, typename Lambda>
			void operate(Lambda&& func);

			///
			/// \brief Add a system to the manager.
			///
			/// Template parameter to speficy type of system to create.
			/// Systems will be updated in the order in which they are created.
			///
			/// \param args Constructor arguments for the system.
			///
			template<is_system System, typename... Args>
			void create_system(Args&&... args);

			///
			/// Get a system. Type is template parameter.
			///
			/// \return Pointer to the system.
			///
			template<is_system System>
			System* get_system();

			///
			/// Clear all data from World and reset.
			///
			void clear();

			///
			/// Get all debug names in unordered_map.
			///
			/// \return Const unordered_map reference.
			///
			const robin_hood::unordered_map<std::string, ecs::Entity>& get_debug_name_map();

		private:
			///
			/// Called by operate().
			///
			template<meta::is_class Component>
			void internal_operate(EntitysWithCounters& entities);

			///
			/// Counter for free entity ids.
			///
			std::uint64_t m_next_id;

			///
			/// Stores entitys.
			///
			std::vector<ecs::Entity> m_entities;

			///
			/// Stores invalid entities.
			///
			std::vector<ecs::Entity> m_invalid_entities;

			///
			/// Stores entity flags.
			///
			robin_hood::unordered_flat_map<ecs::Entity, std::bitset<8>> m_flags;

			///
			/// Debug entity names.
			///
			robin_hood::unordered_map<std::string, ecs::Entity> m_debug_names;

			///
			/// Stores polymorphic ComponentSets.
			///
			std::vector<std::unique_ptr<ecs::Set>> m_data;

			///
			/// Stores systems.
			///
			std::vector<std::unique_ptr<ecs::System>> m_systems;

			///
			/// Used to allow for component creation without having to know the compile time type.
			///
			ComponentFactory m_component_factory;
		};

		template<meta::is_flag Flag>
		inline void World::set_flag(const ecs::Entity entity)
		{
			if (has(entity))
			{
				m_flags[entity].set(Flag::value);
			}
			else
			{
				GALAXY_LOG(GALAXY_ERROR, "Failed to set flag: {0} for entity: {1}.", Flag::value, entity);
			}
		}

		template<meta::is_flag Flag>
		inline void World::unset_flag(const ecs::Entity entity)
		{
			if (has(entity))
			{
				m_flags[entity].reset(Flag::value);
			}
			else
			{
				GALAXY_LOG(GALAXY_ERROR, "Failed to unset flag: {0} for entity: {1}.", Flag::value, entity);
			}
		}

		template<meta::is_class Component>
		inline void World::register_component(std::string_view name)
		{
			// Make sure there are no duplicate components for the hashmap before registering.
			const auto str = static_cast<std::string>(name);
			if (m_component_factory.contains(str))
			{
				GALAXY_LOG(GALAXY_WARNING, "Attempted to register duplicate component: {0}.", str);
			}
			else
			{
				m_component_factory.emplace(name, [&](const ecs::Entity e, const nlohmann::json& json) {
					create_component<Component>(e, json);
				});
			}
		}

		template<meta::is_class Component, typename... Args>
		inline Component* World::create_component(const ecs::Entity entity, Args&&... args)
		{
			if (has(entity))
			{
				const auto type = CUniqueID::get<Component>();
				if (type >= m_data.size())
				{
					m_data.resize(type + 1);
				}

				// Ensure leftover references to unique pointer are destroyed.
				{
					// If null ptr, then no storage for this component exists.
					if (!m_data[type])
					{
						// Use polymorphism to ensure type erasure.
						m_data[type] = std::make_unique<ecs::ComponentSet<Component>>();
					}

					// Now convert the storage to the type we want to access.
					auto* derived = static_cast<ecs::ComponentSet<Component>*>(m_data[type].get());
					if (derived)
					{
						if (!derived->has(entity))
						{
							return derived->create(entity, std::forward<Args>(args)...);
						}
						else
						{
							GALAXY_LOG(GALAXY_WARNING, "Attempted to add a duplicate component.");
							return nullptr;
						}
					}
					else
					{
						return nullptr;
					}
				}
			}
			else
			{
				GALAXY_LOG(GALAXY_ERROR, "Attempted to create a component with an invalid entity.");
				return nullptr;
			}
		}

		template<meta::is_class Component>
		inline Component* World::get(const ecs::Entity entity)
		{
			Component* res = nullptr;

			if (!has(entity))
			{
				GALAXY_LOG(GALAXY_ERROR, "Attempted to get a component of an invalid entity.");
				res = nullptr;
			}
			else
			{
				const auto type = CUniqueID::get<Component>();

				if (!(type >= m_data.size() || m_data.size() == 0))
				{
					if (m_data[type] != nullptr)
					{
						auto* derived = static_cast<ecs::ComponentSet<Component>*>(m_data[type].get());
						if (derived->has(entity))
						{
							res = derived->get(entity);
						}
					}
				}
			}

			return res;
		}

		template<meta::is_class Component>
		inline void World::remove(const ecs::Entity entity)
		{
			if (!has(entity))
			{
				GALAXY_LOG(GALAXY_ERROR, "Attempted to get a component of an invalid entity.");
			}
			else
			{
				const auto type = CUniqueID::get<Component>();

				if (type >= m_data.size() || m_data.size() == 0)
				{
					GALAXY_LOG(GALAXY_ERROR, "Attempted to access a component type that doesnt exist.");
					GALAXY_LOG(GALAXY_ERROR, "Possible zero size component data detected.");
				}
				else
				{
					if (m_data[type] != nullptr)
					{
						auto* derived = static_cast<ecs::ComponentSet<Component>*>(m_data[type].get());
						derived->remove(entity);
					}
				}
			}
		}

		template<meta::is_class... Component>
		inline std::tuple<Component*...> World::get_multi(const ecs::Entity entity)
		{
			return std::make_tuple<Component*...>(get<Component>(entity)...);
		}

		template<meta::is_class... Components, typename Lambda>
		inline void World::operate(Lambda&& func)
		{
			// Ensure data is not empty.
			if (!m_data.empty())
			{
				constexpr auto length = sizeof...(Components);
				EntitysWithCounters entities;

				(internal_operate<Components>(entities), ...);

				for (const auto& [entity, count] : entities)
				{
					// Ensures that only entities that have all components are used.
					if (!(count < length))
					{
						if (is_enabled(entity))
						{
							func(entity, get<Components>(entity)...);
						}
					}
				}
			}
		}

		template<is_system System, typename... Args>
		inline void World::create_system(Args&&... args)
		{
			const auto type = SUniqueID::get<System>();
			if (type >= m_systems.size())
			{
				m_systems.resize(type + 1);
			}

			m_systems[type] = std::make_unique<System>(std::forward<Args>(args)...);
		}

		template<is_system System>
		inline System* World::get_system()
		{
			const auto type = SUniqueID::get<System>();
			if (type > m_systems.size())
			{
				GALAXY_LOG(GALAXY_FATAL, "Attempted to access a system type that doesnt exist!");
				return nullptr;
			}
			else
			{
				return static_cast<System*>(m_systems[type].get());
			}
		}

		template<meta::is_class Component>
		inline void World::internal_operate(EntitysWithCounters& entities)
		{
			const auto type = CUniqueID::get<Component>();

			if (type >= m_data.size())
			{
				GALAXY_LOG(GALAXY_ERROR, "Attempted to access a component type that doesnt exist!");
			}
			else
			{
				auto ptr = m_data[type].get();
				if (ptr != nullptr)
				{
					for (const auto& entity : ptr->m_entities)
					{
						entities[entity]++;
					}
				}
			}
		}
	} // namespace core
} // namespace galaxy

#endif