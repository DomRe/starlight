///
/// Character.cpp
/// quasar
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#include <glad/glad.h>

#include "Character.hpp"

///
/// Core namespace.
///
namespace qs
{
	Character::Character() noexcept
		:m_bearingX(0), m_bearingY(0), m_advance(0)
	{
	}

	Character::Character(const int bx, const int by, const unsigned int advance) noexcept
		:m_bearingX(bx), m_bearingY(by), m_advance(advance)
	{
	}

	Character::~Character() noexcept
	{
	}
}