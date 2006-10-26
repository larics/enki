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

#include "SbotObject.h"
#include "Sbot.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>

/*!	\file SbotObject.cpp
	\brief Implementation of the Sbot Active Object
*/
namespace Enki
{
	using namespace An;
	
	SbotFeeding::SbotFeeding(double r, Robot *owner)
	{
		this->r = r;
		this->owner = owner;
		
		activeColor = Color(255, 0, 0);
		inactiveColor = Color(0, 0, 0);
		owner->color = activeColor;
		
		actualEnergy = 1000;
		actualTime = 0;
		//set to -1 to make feeding infinitely active or inactive
		inactiveDuration = 0;
		activeDuration = -1;
		
		consumeEnergy = false;
		dEnergyActive = 1;
		dEnergyInactive = 0;
	}
	
	void SbotFeeding::objectStep(double dt, PhysicalObject *po, World *w)
	{
		FeedableSbot *sbot = dynamic_cast<FeedableSbot *>(po);
		if (sbot) {
			if (actualTime < activeDuration || activeDuration == -1)
			{
				if ((actualEnergy > 0) || (dEnergyActive < 0))
				{
					sbot->dEnergy += dEnergyActive;
					if ((consumeEnergy) && (dEnergyActive > 0))
						actualEnergy -= dEnergyActive*dt;
				}
			}
			else
			{
				if ((actualEnergy > 0) || (dEnergyInactive < 0))
				{
					sbot->dEnergy += dEnergyInactive;
					if ((consumeEnergy) && (dEnergyInactive > 0))
						actualEnergy -= dEnergyInactive*dt;
				}
			}
		}
	}

	void SbotFeeding::finalize(double dt)
	{
		if ( activeDuration == -1 ) { 
			owner->color = activeColor; 
			return; 
		}
		else if ( inactiveDuration == -1 ) { 
			owner->color = inactiveColor; 
			return; 
		}

		actualTime += dt;
		
		double totalTime = activeDuration+inactiveDuration;
		while (actualTime > totalTime)
			actualTime -= totalTime;
		
		owner->color = (actualTime < activeDuration) ? activeColor : inactiveColor;
	}

	SbotActiveObject::SbotActiveObject(double objectRadius, double actionRange) :
		feeding(actionRange, this)
	{
		addLocalInteraction(&feeding);
		mass = -1;
		r = objectRadius;
	}

	SbotActiveSoundObject::SbotActiveSoundObject(double objectRadius, double actionRange) :
		SbotActiveObject(objectRadius, actionRange),
		speaker(this, actionRange, 25)
	{
		addLocalInteraction(&speaker);
		mass = -1;
		r = objectRadius;
	}

	void SbotActiveSoundObject::setSoundRange(double soundRange) {
		speaker.setSoundRange(soundRange);
	}
}
