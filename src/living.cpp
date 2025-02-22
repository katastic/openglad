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
//
// Living; derived class of walker
//

#include "graph.h"
#include "smooth.h"
#include <cstring>

// From picker
extern Sint32 difficulty_level[DIFFICULTY_SETTINGS];
extern Sint32 current_difficulty;

living::living(const PixieData& data)
    : walker(data)
{
	current_special = 1;
	lifetime = 0;
}

living::~living()
{}

short living::act()
{
	if (bonus_rounds>0 && !dead)  // we get extra rounds to act this cycle
	{
		bonus_rounds--;
		act();
	}
	if (dead)
		return 0;

	// Make sure everyone we're pointing to is valid
	if (foe && (foe->dead || (random(foe->invisibility_left/20) > 0) ) )
		foe = NULL;
	if (is_friendly(foe))
		foe = NULL;
	if (leader && leader->dead)
		leader = NULL;
	if (owner && owner->dead)
	{
		//owner = NULL;
		// A living who had an owner who is now dead, dies as well
		dead = 1;
		death();
		return 0;
	}

	if (lifetime)
	{
		if (!owner || owner->dead) // our owner gone?
		{
			dead = 1;
			death();
			return 0;
		}
		if (--lifetime < 1) //KAT: bug this would just go to zero, right? It was a POST-INCREMENT bug.
		{
			dead = 1;
			return death();
		}
		// Do other things based on our type ..
		switch (family)
		{
			case GUY_FIREELEMENTAL: // we take a toll from our mage ..
				if (stats->hitpoints < stats->max_hitpoints) // we're hurt
				{
					// Take a 'toll' of one health and 3 mp of mage, if there
					Sint32 temp = 0;
					if (owner->stats->hitpoints >= (owner->stats->max_hitpoints/3) )
					{
						temp = 1;
						owner->stats->hitpoints--;
					}
					if (temp && (owner->stats->magicpoints >= 3) )
					{
						temp += 1;
						owner->stats->magicpoints -= 3;
					}
					if (temp == 2) // had both MP and HP, so heal 1 unit
						stats->hitpoints++;
					else // else go down one more unit of lifetime
						lifetime--;
				} // end of hurt elemental
				break;  // end of elemental drain
			default:
				break;
		} // end of special stuff for summoned guys
	}  // end of summoned monster stuff


	collide_ob = NULL; // always start with no collison..

	/*
	  if (ignore)
	  {
	         Log("ignoring living\n");
	         return 0;
	  }
	*/

	// Regenerate magic
	if (stats->magicpoints < stats->max_magicpoints &&
	        !(myscreen->enemy_freeze || bonus_rounds) )
	{
		stats->magicpoints += stats->magic_per_round;
		stats->current_magic_delay++;
		if (stats->current_magic_delay >= stats->max_magic_delay)
		{
			stats->magicpoints++;
			stats->current_magic_delay = 0;
		}
		if (stats->magicpoints > stats->max_magicpoints)
			stats->magicpoints = stats->max_magicpoints;
	} // end magic increment section

	//Regenerate hitpoints
	if(regen_delay > 0)  // Delay after being hit
        regen_delay--;
    else
    {
        if (stats->hitpoints < stats->max_hitpoints &&
                !(myscreen->enemy_freeze || bonus_rounds))
        {
            stats->hitpoints += stats->heal_per_round;
            stats->current_heal_delay++;
            if (stats->current_heal_delay >= stats->max_heal_delay)
            {
                stats->hitpoints++;
                stats->current_heal_delay = 0;
            }
            if (stats->hitpoints > stats->max_hitpoints)
                stats->hitpoints = stats->max_hitpoints;
        } // end hitpoint increment section
    }

	// Special-viewing
	if (view_all > 0)
		view_all--;

	// Invulnerability
	if (invulnerable_left > 0)
		invulnerable_left--;

	// Invisibility
	if (invisibility_left > 0)
		invisibility_left--;
	else
		outline = 0;

	// Flight
	if (flight_left > 0)
		flight_left--;
	if (!myscreen->query_grid_passable(xpos, ypos, this) && !flight_left)
	{
		flight_left++;
		stats->hitpoints--;
		if(cfg.is_on("effects", "damage_numbers"))
            damage_numbers.push_back(DamageNumber(xpos + sizex/2, ypos, 1, RED));
		
		if (stats->hitpoints <= 0)
		{
			dead = 1;
			death();
		}
	}

	// Charmed-ness
	if (charm_left > 1)
		charm_left--;
	else
	{
		charm_left = 0;
		if (real_team_num != 255)
		{
			team_num = real_team_num;
			real_team_num = 255;
		}
	}

	if ( stats->query_bit_flags(BIT_FORESTWALK) &&
	        (
	            myscreen->level_data.mysmoother.query_genre_x_y( xpos/GRID_SIZE, ypos/GRID_SIZE) == TYPE_TREES
	            || myscreen->level_data.mysmoother.query_genre_x_y( (xpos+sizex)/GRID_SIZE, ypos/GRID_SIZE) == TYPE_TREES
	            || myscreen->level_data.mysmoother.query_genre_x_y( (xpos+sizex)/GRID_SIZE, (ypos+sizey)/GRID_SIZE) == TYPE_TREES
	            || myscreen->level_data.mysmoother.query_genre_x_y( xpos/GRID_SIZE, (ypos+sizey)/GRID_SIZE) == TYPE_TREES
	        )
	   )
	{
		// charge us a point of magic ..
		if (stats->magicpoints > 0.0f && stats->current_magic_delay == 0)
        {
            stats->magicpoints--;
        }

        float temp;
		if (myguy)
			temp = (4 - myguy->dexterity/10.0f);
		else
			temp = (4 - stats->level/2.0f);
		if (temp < 0)
			temp = 0;
		stepsize -= temp;
		if (stepsize < 1)
			stepsize = 1;
	}  // end of forestwalk check
	else
		stepsize = normal_stepsize;

	// Speed bonus
	if (speed_bonus_left > 1)
	{
		speed_bonus_left--;
		stepsize += speed_bonus;
	}
	
	
	if(attack_lunge > 0.0f)
    {
        attack_lunge -= 0.4f;
        if(attack_lunge < 0.0f)
            attack_lunge = 0.0f;
    }
	
	if(hit_recoil > 0.0f)
    {
        hit_recoil -= 0.6f;
        if(hit_recoil < 0.0f)
            hit_recoil = 0.0f;
    }

	// Special things for various different living types
	switch (family)
	{
		case GUY_ARCHMAGE:  // gets bonus viewing, at times
		    {
		        Sint32 temp;
                if (stats->level >= 40)
                    temp = 1;
                else
                    temp = 40 - stats->level;
                if (!(drawcycle%temp)) // then we get to see..
                    view_all += 1;
		    }
			break;
		default:
			break;
	}  // end of special family auto-powers

	// Complete previous animations (like firing)
	if (ani_type != ANI_WALK)
		return animate();

	// Are we frozen?
	if (stats->frozen_delay)
	{
		stats->frozen_delay--;
		return 1;
	}

	if (busy > 0)
		busy--; // This allows busy to be our FIRING delay.
	// Find new action

	// Turn if you want to (...turn, around the world...)
	if (curdir != enddir && query_order() == ORDER_LIVING)
		return turn(enddir);


	// Are we performing some action?
	if (stats->has_commands())
	{
		Sint32 temp = stats->do_command();
		if (temp)
			return 1;
	}

	if (skip_exit > 0)
		skip_exit--;

	// Do we have a generic action-type set?
	if (action  && (user == -1) )
	{
		Sint32 temp = do_action();
		if (temp)
			return temp;
	}

	switch (act_type)
	{
			// We are the control character
		case ACT_CONTROL:
			{
				return 1;

				//break;
			}
			// We are a generator
		case ACT_GENERATE:
			{
				Log("LIVING Generator?\n");
				//              act_generate();
				break;
			}
			// We are a weapon
		case ACT_FIRE:
			{
				Log("Living think's it's a weapon (act_fire)\n");
				//              act_fire();
				return 1;
				//break;
			}
		case ACT_GUARD:
			{
				act_guard();
				break;
			}
		case ACT_DIE:
			{
				this->dead = 1;
				return 1;
			}
			// We are randomly walking toward enemy
		case ACT_RANDOM:
			{
				if (!random(5) ) //1 in 5 to do our special
				{
					// Should we do our special? Are we full of magic?
					if (stats->magicpoints >= stats->special_cost[1])
					{
						current_special = (char) (random((stats->level+2)/3) + 1);
						if ( (current_special > 4) ||
						        (!strcmp(myscreen->special_name[(int)family][(int)current_special], "NONE"))
						   )
							current_special = 1;
						if (check_special() )
							return special();
					}
					else       // do random walking ..
					{
						act_random();
						return 1;
					}
				}
				else if (!random(5) ) //1 in 5 to do act_random() function
					act_random();
				else // 4 of 5 times
				{
					if (!foe)
					{
						foe = myscreen->find_near_foe(this);
					}
					if (foe) // && random(2) )
					{
						curdir = enddir = (char) ((enddir/2) * 2);
						//stats->try_command(COMMAND_SEARCH, 40, 0, 0);
						stats->try_command(COMMAND_SEARCH, 300, 0, 0);
					}
					//else if (foe)
					//  stats->try_command(COMMAND_RIGHT_WALK,40,0,0);
					else if (!random(2))
						foe = myscreen->find_far_foe(this);
					else
						stats->try_command(COMMAND_RANDOM_WALK,20);

					return 1;
				}
			}  // END RANDOM
			break;
		default:
			{
				Log("No act type set.\n");
				return 0;
			}
	}  // END SWITCH
	return 0;
}

short living::shove(walker  *target, short x, short y)
{
	//return 0; //debug memory

	if (target && !target->dead && (query_order()==ORDER_LIVING) &&  //we are alive
	        (is_friendly(target)) // we are allied
	   )
		// Make sure WE don't get shoved
		if (random(3) && target->query_act_type() != ACT_CONTROL)
		{
			// We have to prevent a build-up of shoves which is
			//   caused by a blocked target.  We do so for now by clearing
			//   all commands
			target->stats->clear_command();
			if (target->query_family()==GUY_CLERIC)
			{
				target->current_special = 1; // healing
				target->special();
			}
			target->stats->set_command(COMMAND_WALK,4,x ,y );
			return 1;
		}
	return 0;
}

bool living::walk(float x, float y)
{
	short dir;
	//  short newdir, newcurdir;
	//  short distance; // distance between current and desired facings

	// Repeat last walk.
	//  lastx = x;
	//  lasty = y;

	dir = facing(x, y);

	if (curdir == dir)  // if continue direction
	{
		// check if off map
		if (x+xpos < 0 ||
		        x+xpos >= myscreen->level_data.grid.w*GRID_SIZE ||
		        y+ypos < 0 ||
		        y+ypos >= myscreen->level_data.grid.h*GRID_SIZE)
		{
			return 0;
		}

		// Here we check if the move is valid
		// Normally we would check if the object at this grid point
		//    is passable (I cheated for now)
		// FIXME: These additional checks are a hack for the corner clipping bug (you could get into trees, etc.)
		if (myscreen->query_passable(xpos+x, ypos+y,this) && myscreen->query_passable(xpos+ceilf(x), ypos+ceilf(y),this) && myscreen->query_passable(xpos+floorf(x), ypos+floorf(y),this))
		{
			// Control object does complete redraw anyway
			worldmove(x,y);
			cycle++;
			//if (!ani || (curdir*cycle > sizeof(ani)) )
			//  Log("WALKER::WALK: Bad ani!\n");
			if (ani[curdir][cycle] == -1)
				cycle = 0;
			set_frame(ani[curdir][cycle]);
			return 1;
		}
		else //Invalid move?
		{
			if (collide_ob && !collide_ob->dead)
			{
				if (collide_ob->query_order() == ORDER_LIVING && is_friendly(collide_ob) )
				{
					shove(collide_ob, x, y);
				}
			}  // end hit some object
			if (stats->query_bit_flags(BIT_ANIMATE) )  // animate regardless..
			{
				cycle++;
				if (ani[curdir][cycle] == -1)
					cycle = 0;
				set_frame(ani[curdir][cycle]);
			}

			return 0;
		}
	}
	else // Just changing direction
	{
		enddir = (char) dir;

		// Technically, control gets and EXTRA call to TURN
		//   because first we call WALK, then ACT, whereas
		//   other walkers call ACT.  This would cause control
		//   to turn TWICE on the first call to walk, which is bad.
		//   So we stop that behavior here.
		if (this->query_act_type() != ACT_CONTROL || stats->has_commands())
			turn(enddir);
	}
	return 1;
}

bool walkerIsAutoAttackable(walker* ob)
{
    return (ob->query_order() == ORDER_LIVING
             || ob->query_family() == GEN_TENT
             || ob->query_family() == GEN_TOWER
             || ob->query_family() == GUY_TOWER1
             || ob->query_family() == GEN_TREEHOUSE
             || ob->query_family() == GEN_BONES
             || ob->query_family() == WEAP_GLOW
             || ob->query_family() == WEAP_TREE
             || ob->query_family() == WEAP_DOOR);
}

short living::collide(walker  *ob)
{
	collide_ob = ob;
	//return 1; // debug
	if ( ob && walkerIsAutoAttackable(ob) && (is_friendly(ob) == 0)
	        && !ob->dead && !dead)
		init_fire();
	return 1;
}

walker * living::do_summon(char whatfamily, unsigned short lifetime)
{
	walker  *newob;

	newob = myscreen->level_data.add_ob(ORDER_LIVING, whatfamily);
	newob->owner = this;
	newob->lifetime = lifetime;
	newob->transform_to(ORDER_LIVING, whatfamily);	
	newob->is_a_summon = true;
	//  Log("\n\nSummoned %d, life %d\n", whatfamily, lifetime);

	return newob;
}

// Returns true or false on whether it's good to do
// the special or not ..
short living::check_special()
{
	Uint32 distance, myrange;
	short howmany;

	shifter_down = random(2); // on or off, randomly ..

	// Make sure we have enough ..
	if (stats->magicpoints < stats->special_cost[(int)current_special])
		current_special = 1; // make us do default ..

	switch (family)
	{
		case GUY_SOLDIER:   // Check for foe in range x
			if (foe) // already have a foe ..
			{
				distance = (Uint32) distance_to_ob(foe);//Sint32 (deltax*deltax) + Sint32 (deltay*deltay);
				if (distance < 75 && distance > 20) // about 3 squares max, 1 square min
					return 1;
				return 0;
			}
			else // get a new foe ..
			{
				foe = myscreen->find_near_foe(this);
				if (!foe)
					return 0;
				distance = (Uint32) distance_to_ob(foe); // (deltax*deltax) + Sint32 (deltay*deltay);
				if (distance < 75 && distance > 20) // about 3 squares max, 1 min
					return 1;
				return 0;
			}
			//break; // end of fighter case
		case GUY_FIREELEMENTAL:     // Check for foe in range x
		case GUY_ARCHER:
		case GUY_GHOST:
		case GUY_ORC:
			if (foe) // already have a foe ..
			{
				distance = (Uint32) distance_to_ob(foe); //Sint32 (deltax*deltax) + Sint32 (deltay*deltay);
				if (distance < 130) // about 6 squares
					return 1;
				return 0;
			}
			else // get a new foe ..
			{
				foe = myscreen->find_near_foe(this);
				if (!foe)
					return 0;
				distance = (Uint32) distance_to_ob(foe); //Sint32 (deltax*deltax) + Sint32 (deltay*deltay);
				if (distance < 130) // about 6 squares
					return 1;
				return 0;
			}
			//break; // end of fighter case
		case GUY_THIEF:
			if (current_special == 1) // drop bomb
			{
				if (foe) // already have a foe ..
				{
					distance = (Uint32) distance_to_ob(foe); // (deltax*deltax) + Sint32 (deltay*deltay);
					if (distance < 130 && distance > 35) // about 6 squares max, 2 min
						return 0;
				}
				else // get a new foe ..
				{
					myscreen->find_foes_in_range(myscreen->level_data.oblist,
					                                        110, &howmany, this);

					if (howmany < 3)
						return 0;
					return 1;
				}
				break; // end of thief case
			} // end of bomb
			else if (current_special == 3)
			{
				if (!shifter_down) // taunt
					myrange = 80 + 4*stats->level;
				else               // charm
					myrange = 16 + 4*stats->level;

				myscreen->find_foes_in_range(myscreen->level_data.oblist,
				                                        myrange, &howmany, this);
				if (howmany < 1)
					return 0;
				else
					return 1;
			}
			else
				return 1;  // default is go for it
		case GUY_MAGE:  // TP if  away from guys ..
			howmany = 0;
			myscreen->find_foes_in_range(myscreen->level_data.oblist,
			                                        110, &howmany, this);

			if (howmany < 1) //  away from anybody ..
				return 1;
			if (howmany > 3) // too many enemies!
				return 1;
			return 0;
		case GUY_SUMMONER:  // TP if  away from guys ..
			howmany = 0;
			myscreen->find_foes_in_range(myscreen->level_data.oblist,
			                                        110, &howmany, this);

			if (howmany < 1) //  away from anybody ..
				return 1;
			if (howmany > 3) // too many enemies!
				return 1;
			return 0;
		case GUY_BUILDER:  // TP if  away from guys ..
			howmany = 0;
			myscreen->find_foes_in_range(myscreen->level_data.oblist,
			                                        110, &howmany, this);

			if (howmany < 1) //  away from anybody ..
				return 1;
			if (howmany > 3) // too many enemies!
				return 1;
			return 0;






			//break; // end of fighter case
		case GUY_SLIME:
			if (myscreen->level_data.numobs < MAXOBS)
				return 1;
			else
				return 0;
		case GUY_CLERIC: // any friends?
			if (current_special == 1) // healing
			{
				myscreen->find_friends_in_range(myscreen->level_data.oblist,
				            60, &howmany, this);

				if (howmany > 1) // other than ourselves?
				{
					shifter_down = 0; // we're HEALING
					return 1;
				}
				else if (stats->magicpoints >= (stats->max_magicpoints/2) )
				{
					// Do mace ...
					shifter_down = 1;
					return 1;
				}
				else
					return 0;
			}  // end of healing/mace
			else
				return 1;
			//break;
		case GUY_SKELETON:  // Tunnel if no foes near ..
			howmany = 0;
			myscreen->find_foes_in_range(myscreen->level_data.oblist,
			                                        5*GRID_SIZE, &howmany, this);

			if (howmany < 1) //  away from anybody ..
				return 1;      //  so tunnel
			return 0;
			//break; // end of skeleton case
		default :
			return 1;
	}

	return 1; //unreachable?
}

void living::set_difficulty(Uint32 whatlevel)
{
	//  Sint32 calcdelay,calcrate;  // apparently not used anymore
	Uint32 dif1 = difficulty_level[current_difficulty];
	Uint32 levmult = (Uint32) whatlevel*(Uint32) whatlevel;

	switch (family)
	{
		case GUY_ARCHER:
			stats->max_hitpoints   += 11*levmult;
			stats->max_magicpoints += 12*levmult;
			damage += 4*whatlevel;
			stats->armor += levmult;
			break;
		case GUY_MAGE:
			stats->max_hitpoints   += 7*levmult;
			stats->max_magicpoints += 14*levmult;
			damage += 3*whatlevel;
			stats->armor += levmult/2.0f;
			break;
		case GUY_CLERIC:
		case GUY_DRUID:
			stats->max_hitpoints   += 9*levmult;
			stats->max_magicpoints += 12*levmult;
			damage += 4*whatlevel;
			stats->armor += levmult/2.0f;
			break;
		case GUY_SOLDIER:  // default as soldier
			stats->max_hitpoints   += 13*levmult;
			stats->max_magicpoints += 8*levmult;
			weapons_left = (short) ((whatlevel+1) / 2);
			damage += 5*whatlevel;
			stats->armor += 2*levmult;
			break;
		case GUY_ORC:
			stats->max_hitpoints   += 14*levmult;
			stats->max_magicpoints += 7*levmult;
			damage += 6*whatlevel;
			stats->armor += 3*levmult;
			break;
		case GUY_GOLEM:
			stats->max_hitpoints   += 18*levmult;
			stats->max_magicpoints += 5*levmult;
			damage += 7*whatlevel;
			stats->armor += 4*levmult;
			break;
		default:
			stats->max_hitpoints   += 11*levmult;
			stats->max_magicpoints += 11*levmult;
			damage += (short) 4*whatlevel;
			stats->armor += 2*levmult;
			break;
	}

	// Adjust for difficulty settings now...
	if (team_num != 0)  // do all EXCEPT player characters
	{
		stats->max_hitpoints = (stats->max_hitpoints*dif1) / 100.0f;
		stats->max_magicpoints = (stats->max_magicpoints*dif1) / 100.0f;
		damage = (damage * dif1) / 100.0f;
	}

	stats->hitpoints = stats->max_hitpoints;
	stats->magicpoints = stats->max_magicpoints;

	stats->max_heal_delay = REGEN; //defined in graph.h
	stats->current_heal_delay =
	    (levmult * 4); //for purposes of calculation only

	while (stats->current_heal_delay > REGEN)
	{
		stats->current_heal_delay -= REGEN;
		stats->heal_per_round++;
	} // this takes care of the integer part, now calculate the fraction

	if (stats->current_heal_delay > 1)
	{
		stats->max_heal_delay /=
		    (Sint32) (stats->current_heal_delay + 1);
	}
	stats->current_heal_delay = 0; //start off without healing

	//make sure we have at least a 2 wait, otherwise we should have
	//calculated our heal_per_round as one higher, and the math must
	//have been screwed up some how
	if (stats->max_heal_delay < 2)
		stats->max_heal_delay = 2;



	// Set the magic delay ..
	stats->max_magic_delay = REGEN;
	stats->current_magic_delay = (Sint32) (levmult*30);//for calculation only

	while (stats->current_magic_delay > REGEN)
	{
		stats->current_magic_delay -= REGEN;
		stats->magic_per_round++;
	} // this takes care of the integer part, now calculate the fraction

	if (stats->current_magic_delay > 1)
	{
		stats->max_magic_delay /=
		    (Sint32) (stats->current_magic_delay + 1);
	}
	stats->current_magic_delay = 0; //start off without magic regen

	//make sure we have at least a 2 wait, otherwise we should have
	//calculated our magic_per_round as one higher, and the math must
	//have been screwed up some how
	if (stats->max_magic_delay < 2)
		stats->max_magic_delay = 2;

}

short living::facing(short x, short y)
{
	Sint32 bigy = (Sint32) (y*1000);
	Sint32 slope;

	if (!x)
	{
		if (y>0)
			return FACE_DOWN;
		else
			return FACE_UP;
	}

	slope = bigy / x;

	if (x>0)
	{
		if (slope > 2414)
			return FACE_DOWN;
		if (slope > 414)
			return FACE_DOWN_RIGHT;
		if (slope > -414)
			return FACE_RIGHT;
		if (slope > -2414)
			return FACE_UP_RIGHT;
		return FACE_UP;
	}
	else
	{
		if (slope > 2414)
			return FACE_UP;
		if (slope > 414)
			return FACE_UP_LEFT;
		if (slope > -414)
			return FACE_LEFT;
		if (slope > -2414)
			return FACE_DOWN_LEFT;
		return FACE_DOWN;
	}
}

short living::act_random()
{
	//  short newx, newy; // apparently not used anymore
	short xdist, ydist;

	// Find our foe
	if (!random(80) || (!foe))
		foe = myscreen->find_near_foe(this);
	if (!foe)
		return stats->try_command(COMMAND_RANDOM_WALK,40);

	xdist = (short) (foe->xpos - xpos);
	ydist = (short) (foe->ypos - ypos);

	// If foe is in firing range, turn and fire
	if (abs(xdist) < lineofsight*GRID_SIZE &&
	        abs(ydist) < lineofsight*GRID_SIZE)
	{
		if (fire_check(xdist, ydist))
		{
			init_fire(xdist, ydist);
			stats->set_command(COMMAND_FIRE, (short) random(24), xdist, ydist);
			return 1;
		}
		else
			// Nearest foe is blocked
			turn(facing(xdist,ydist));
	}

	stats->try_command(COMMAND_SEARCH,200,0,0);
	//stats->try_command(COMMAND_RIGHT_WALK,50, 0, 0);
	return 1;

}

short living::do_action()
{

	if (!action)
		return 0;

	switch (action)
	{
		case ACTION_FOLLOW: // follow our leader, attack his targets ..
			if (foe)
				return 0;       // continue as normal
			leader = myscreen->find_nearest_player(this);
			if (!leader)
				return 0;       // continue as normal ... shouldn't happen
			if (leader->foe)
			{
				foe = leader->foe;
				return 0;       // continue from this point ..
			}
			// Else follow our leader
			stats->force_command(COMMAND_FOLLOW, 5, 0, 0);
			return 1;
		default:
			return 0;
	}
}



