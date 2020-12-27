///
/// AABB.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include <algorithm>

#include "AABB.hpp"

namespace galaxy
{
	namespace physics
	{
		AABB::AABB()
		    : m_min {0.0f, 0.0f}, m_max {1.0f, 1.0f}
		{
		}

		AABB::AABB(const glm::vec2& min, const glm::vec2& max)
		    : m_min {min}, m_max {max}
		{
		}

		const bool AABB::overlaps(const AABB& b) const
		{
			return m_max.x > b.m_min.x && m_min.x < b.m_max.x && m_max.y > b.m_min.y && m_min.y < b.m_max.y;
		}

		const bool AABB::contains(const AABB& b) const
		{
			return b.m_min.x >= m_min.x && b.m_max.x <= m_max.x && b.m_min.y >= m_min.y && b.m_max.y <= m_max.y;
		}

		AABB AABB::merge(const AABB& b) const
		{
			// clang-format off
			return
			{
				{std::min(m_min.x, b.m_min.x), std::min(m_min.y, b.m_min.y)},
				{std::max(m_max.x, b.m_max.x), std::max(m_max.y, b.m_max.y)}
			};

		}

		AABB AABB::intersection(const AABB& b) const
		{
			return
			{
				{std::max(m_min.x, b.m_min.x), std::max(m_min.y, b.m_min.y)},
				{std::min(m_max.x, b.m_max.x), std::min(m_max.y, b.m_max.y)}
			};

			// clang-format on
		}

		const float AABB::surface_area() const
		{
			const glm::vec2 dim = m_max - m_min;
			return 2.0f * (dim.x * dim.y + dim.x + dim.y);
		}

	} // namespace physics
} // namespace galaxy