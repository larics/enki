/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2005 Stephane Magnenat <nct@ysagoon.com>
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

#ifndef __SBOTCAM_H
#define __SBOTCAM_H

#include <enki/Interaction.h>
#include <enki/PhysicalEngine.h>
#include <enki/interactions/CircularCam.h>

#include <valarray>

/*!	\file SbotCam.h
	\brief Header of the Sbot 1D circular camera 
*/
namespace Enki
{
	class Sbot;
	
	//! 1D 360 circular camera for the Sbot, based on 2 180 CircularCam
	/*! \ingroup interaction */
	class SbotCam : public LocalInteraction
	{
	public:
		//! zbuffer (array of size pixelCount of double)
		std::valarray<double> zbuffer;
		//! Image (array of size pixelCount of Color)
		std::valarray<An::Color> image;
		
	protected:
		//! Cameras doing the real job, first part
		CircularCam cam0;
		//! Cameras doing the real job, second part
		CircularCam cam1;

	public :
		//! Constructor, r is the vision radius and owner is the Sbot the camera belongs to
		SbotCam(Sbot *owner, unsigned halfPixelCount); 
		//! Destructor
		virtual ~SbotCam(){}
		virtual void init();
		virtual void objectStep (double dt, PhysicalObject *po, World *w);
		virtual void wallsStep(World *w);
		virtual void finalize(double dt);
		//! Change the fog condition for this camera. If useFog is true, an exponential fog with density will be used. Additionally, a threshold can be applied on the resulting color
		void setFogConditions(bool useFog, double density = 0.0, An::Color threshold = An::Color::black);
		//! Change the sight range of this interaction
		void setRange(double range);
		//! Change the pixel operation functor
		void setPixelOperationFunctor(PixelOperationFunctor *pixelOperationFunctor);
	};
}
#endif
