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
#ifndef HEADER_TREASURE
#define HEADER_TREASURE
//#pragma once
// Definition of TREASURE class

#include "base.h"
#include "walker.h"

class treasure : public walker
{
	public:
		explicit treasure(const PixieData& data);
		virtual ~treasure() override;
		short act() override;
		//short                    death(); // called upon destruction
		short eat_me(walker  * eater) override;
		walker *find_teleport_target();
		void set_direct_frame(short whatframe) override;
		char query_order() override
		{
			return ORDER_TREASURE;
		}
};

#endif