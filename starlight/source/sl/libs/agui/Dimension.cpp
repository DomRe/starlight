/*   _____                           
 * /\  _  \                     __    
 * \ \ \_\ \      __    __  __ /\_\   
 *  \ \  __ \   /'_ `\ /\ \/\ \\/\ \  
 *   \ \ \/\ \ /\ \_\ \\ \ \_\ \\ \ \ 
 *    \ \_\ \_\\ \____ \\ \____/ \ \_\
 *     \/_/\/_/ \/____\ \\/___/   \/_/
 *                /\____/             
 *                \_/__/              
 *
 * Copyright (c) 2011 Joshua Larouche
 * 
 *
 * License: (BSD)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Agui nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sl/libs/agui/Dimension.hpp"
namespace agui
{

	int Dimension::getWidth() const
	{
		return width;
	}

	int Dimension::getHeight() const
	{
		return height;
	}

	void Dimension::setWidth( int width )
	{
		this->width = width;
	}

	void Dimension::setHeight( int height )
	{
		this->height = height;
	}

	void Dimension::set( int width, int height )
	{
		this->width = width;
		this->height = height;
	}

	void Dimension::set( float width, float height )
	{
		this->width = (int)width;
		this->height = (int)height;
	}

	Dimension::Dimension( int width, int height )
	{
		set(width,height);
	}

	Dimension::Dimension()
	{
		width = 0;
		height = 0;
	}

	std::string Dimension::toString() const
	{
		std::stringstream result;
		result << "{";
		result << width;
		result << ",";
		result << height;
		result << "}";

		return result.str();
	}

	std::string Dimension::widthToString() const
	{
		std::stringstream result;
		result << width;
		return result.str();
	}

	std::string Dimension::heightToString() const
	{
		std::stringstream result;
		result << height;
		return result.str();
	}

}
