/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2005 Stephane Magnenat <nct@ysagoon.com>
    Copyright (C) 2004-2005 Markus Waibel <markus.waibel@epfl.ch>
    Copyright (C) 2005 Laboratory of Intelligent Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication 
    arising from research using this software are asked to add the 
    following reference:
    Enki - a fast 2D robot simulator part of the Teem framework
    http://teem.epfl.ch
    Stephane Magnenat <stephane.magnenat@a3.epfl.ch>,
    Markus Waibel <markus.waibel@epfl.ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __CAMERA_H
#define __CAMERA_H

#include <enki/Interaction.h>
#include <enki/PhysicalEngine.h>

/*! \file AliceCam.h
	\brief Header of the Alice 2 pixels camera interaction
*/

namespace Enki
{
	//!	Linear camera for the Alice.
	/*! The AliceCam is implemented as 2 rays and only returns two 1 bit values. They are only used to distinguish the wallcolours - the nest is white, the other walls are black. For now, noise is not implemented in the AliceCam.  
		\ingroup interaction
	*/
	class AliceCam : public GlobalInteraction
	{
	public :
		//! The right camera ray
		bool cvaluestarboard;
		//! The left camera ray
		bool cvalueport;

	public :
		//! Constructor
		AliceCam (Robot *me);
		//! Destructor
		~AliceCam(){}
		//! The AliceCam object step
		void step(double dt, World *w);
		//! Get value of the right camera ray
		double getCValueStarboard();
		//! Get value of the left camera ray
		double getCValuePort();
	};
}

#endif
