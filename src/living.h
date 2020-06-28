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
#ifndef LIVING_HEADING
#define LIVING_HEADING

// Definition of LIVING class

#include "base.h"
#include "walker.h"

class living : public walker
{
	public:
		explicit living(const PixieData& data);
		virtual ~living();
		short          act() override;
		short          check_special() override; // determine if we should do special ..
		short          collide(walker  *ob) override;
		short          do_action(); // perform overriding action
		walker*        do_summon(char whatfamily, unsigned short lifetime) override;
		short          facing(short x, short y) override;
		void           set_difficulty(Uint32 whatlevel) override;
		short          shove(walker  *target, short x, short y) override;
		char           query_order() override
		{
			return ORDER_LIVING;
		}
		virtual bool walk(float x, float y) override;		
	protected:
		short act_random() override;
};

#endif

