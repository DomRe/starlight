///
/// SpriteBatchComponent.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_SPRITEBATCHCOMPONENT_HPP_
#define GALAXY_SPRITEBATCHCOMPONENT_HPP_

#include <nlohmann/json_fwd.hpp>
#include <qs/sprite/BatchedSprite.hpp>

///
/// Core namespace.
///
namespace galaxy
{
	///
	/// Component for a spritebatch.
	///
	class SpriteBatchComponent final
	{
	public:
		///
		/// Constructor.
		///
		SpriteBatchComponent();

		///
		/// JSON constructor.
		///
		/// \param json JSON defining object.
		///
		SpriteBatchComponent(const nlohmann::json& json);

		///
		/// Copy constructor.
		///
		SpriteBatchComponent(const SpriteBatchComponent&) noexcept = delete;

		///
		/// Move constructor.
		///
		SpriteBatchComponent(SpriteBatchComponent&&);

		///
		/// Copy assignment operator.
		///
		SpriteBatchComponent& operator=(const SpriteBatchComponent&) noexcept = delete;

		///
		/// Move assignment operator.
		///
		SpriteBatchComponent& operator=(SpriteBatchComponent&&);

		///
		/// Destructor.
		///
		~SpriteBatchComponent() noexcept = default;

		///
		/// Batched sprite object.
		///
		qs::BatchedSprite m_bs;
	};
} // namespace galaxy

#endif