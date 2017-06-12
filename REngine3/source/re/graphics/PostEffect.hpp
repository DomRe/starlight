//
//  PostEffect.hpp
//  REngine3
//
/*
#####################
SFML Game Development
License
#####################

This file describes the licenses for material accompanying the book "SFML Game Development".
Copyright(c) 2013 Artur Moreira, Henrik Vogelius Hansson, Jan Haller



========== =
Source code
========== =

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
excluding commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. Redistributions may not be sold, nor may they be used in a commercial
product or activity.

4. This notice may not be removed or altered from any source distribution.
*/

// ALTERED SOURCE

#ifndef RENGINE3_POSTEFFECT_HPP_
#define RENGINE3_POSTEFFECT_HPP_

namespace sf
{
	class RenderTarget;
	class RenderTexture;
	class Shader;
}

namespace re
{
	class PostEffect : sf::NonCopyable
	{
	public:
		virtual					~PostEffect();
		virtual void			apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;

	protected:
		static void				applyShader(const sf::Shader& shader, sf::RenderTarget& output);
	};

}

#endif