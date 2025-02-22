/* Copyright (C) 1995-2002  FSGames. Ported by Sean Ford and Yan Shosh
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef HEADER_WEAP
#define HEADER_WEAP
// Definition of WEAP class

#include "base.h"
#include "walker.h"

class weap : public walker
{
	public:
		explicit weap(const PixieData& data);
		virtual ~weap() override;

		short act() override;
		short animate() override;
		short death() override; // called on destruction
		short setxy(short x, short y) override;
		char  query_order() override 
		{
			return ORDER_WEAPON;
		}

		// Weapons-only related variables; use with care
		Sint32 do_bounce; // do we bounce?

};




#endif