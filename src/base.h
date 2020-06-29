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
#pragma once
// BASE definitions (perhaps this should be broken up some more

/* ChangeLog
	buffers: 7/31/02: *C++ style includes for string and fstream
			: *deleted some redundant headers
			: *added math.h,ctype.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
#include <ctype.h>
#include "sounds.h"
#include <SDL.h>
#include "input.h"
#include "util.h"
#include "gparser.h"
#include "pal32.h"
#include "pixdefs.h"
#include "soundob.h" // sound defines

class video;
class screen;
class viewscreen;
class pixie;
class pixieN;

class walker;
class living;
class weap;
class treasure;
class effect;

class text;
class loader;
class statistics;
class command;
class guy;
class radar;

class soundob;
class smoother;

#define DIFFICULTY_SETTINGS 3

Uint32 random(Uint32 x);

#define VIDEO_ADDRESS 0xA000	//old crap, still used
#define VIDEO_LINEAR ( (VIDEO_ADDRESS) << 4) //old crap, still used

#define DPMI_INT        0x31
/*struct meminfo			// OLD CRAP but still used in screen.cpp:1374
{
	unsigned LargestBlockAvail;
	unsigned MaxUnlockedPage;
	unsigned LargestLockablePage;
	unsigned LinAddrSpace;
	unsigned NumFreePagesAvail;
	unsigned NumPhysicalPagesFree;
	unsigned TotalPhysicalPages;
	unsigned FreeLinAddrSpace;
	unsigned SizeOfPageFile;
	unsigned Reserved[3];
};*/

extern screen* myscreen; // global, availible to anyone

#define MAX_LEVELS 500 // Maximum number of scenarios allowed ..
//#define GRID_SIZE 16
const int GRID_SIZE = 16; //screw your lack of define debug symbols

#define PROT_MODE 1  // comment this out when not in protected mode
#ifdef PROT_MODE
  #define init_sound(x,y,z)  while (0)
//#define play_sound(x)      while (0)
#endif

// Used for the help-text system:
#define MAX_LINES 100   // maximum number of lines in helpfile
#define HELP_WIDTH 100   // maximum length of display line
short   fill_help_array(char somearray[HELP_WIDTH][MAX_LINES], SDL_RWops *infile);
short   read_campaign_intro(screen *myscreen);
short   read_scenario(screen  *myscreen);
char* read_one_line(SDL_RWops *infile, short length);

//color defines:
#define DEFAULT_TEXT_COLOR 88

#define PURE_WHITE   15
#define PURE_BLACK   0
#define WHITE        24
#define BLACK        160
#define GREY         23
#define YELLOW       88
#define RED          40
#define DARK_BLUE    72
#define LIGHT_BLUE   120
#define DARK_GREEN   63
#define LIGHT_GREEN  56

// Color cycling:
#define WATER_START  208
#define WATER_END    223
#define ORANGE_START 224
#define ORANGE_END   231

// Random defines:
//#define PROFILING
//#include "profiler.h"
#define CHEAT_MODE 1  // set to 0 for no cheats..
// Picture Object class defs

// HP BAR COLOR DEFINES
#define BAR_BACK_COLOR 11
#define BOX_COLOR 0
#define LOW_HP_COLOR 42
#define MID_HP_COLOR 237
#define HIGH_HP_COLOR 61
#define MAX_HP_COLOR 56 // When hp's are over max :)

// MP BAR COLOR DEFINES
#define LOW_MP_COLOR 42
#define MID_MP_COLOR 108
#define HIGH_MP_COLOR 72
#define MAX_MP_COLOR 64 // When mp's are over max :)

// Generators are limited by this number
#define MAXOBS 150



// Act types
#define ACT_RANDOM 0
#define ACT_FIRE 1
#define ACT_CONTROL 2
#define ACT_GUARD 3
#define ACT_GENERATE 4
#define ACT_DIE 5
#define ACT_SIT 6

// Team types

//              //#define MY_TEAM 0
//              #define ELF_TEAM 1
//              #define KNIGHT_TEAM 2
//              #define MAX_TEAM 2

#define MAX_TEAM 7

// Other screen-type things
#define NUM_SPECIALS 6

// Animation Types : Livings
#define ANI_WALK 0
#define ANI_ATTACK 1
#define ANI_TELE_OUT 2
#define ANI_SKEL_GROW 3
#define ANI_TELE_IN 3
#define ANI_SLIME_SPLIT 4

// Animations types : weapons
#define ANI_GROW 1 // Trees have no attack animation
#define ANI_GLOWGROW 1 // Neither do sparkles
#define ANI_GLOWPULSE 2 // sparkles cycling

// These are for effect objects ..
#define ANI_EXPAND_8 1 //1
#define ANI_DOOR_OPEN 1 // Door opening
#define ANI_SCARE    1 // 2 ghost scare
#define ANI_BOMB     1 // 3 thief's bomb
#define ANI_EXPLODE  1 // 4
#define ANI_SPIN     1 // for the marker

// Orders
#define ORDER_LIVING 0
#define ORDER_WEAPON 1
#define ORDER_TREASURE 2
#define ORDER_GENERATOR 3
#define ORDER_FX 4
#define ORDER_SPECIAL 5
#define ORDER_BUTTON1 6

// Living families
#define GUY_SOLDIER 0
#define GUY_ELF 1
#define GUY_ARCHER 2
#define GUY_MAGE 3
#define GUY_SKELETON 4
#define GUY_CLERIC 5
#define GUY_FIREELEMENTAL 6
#define GUY_FAERIE 7
#define GUY_SLIME 8
#define GUY_SMALL_SLIME 9
#define GUY_MEDIUM_SLIME 10
#define GUY_THIEF 11
#define GUY_GHOST 12
#define GUY_DRUID 13
#define GUY_ORC   14
#define GUY_BIG_ORC 15
#define GUY_BARBARIAN 16
#define GUY_SUMMONER 17 //HAS TO BE right BEFORE ARCHMAGE. looks like there's a bug if you add a character after empty data (like tower) with no picker stats
// See [guy.cpp:84]
#define GUY_BUILDER 18
#define GUY_ARCHMAGE 19 	//17
#define GUY_GOLEM 20 	//18
#define GUY_GIANT_SKELETON 21 //19
#define GUY_TOWER1 22 //20

#define NUM_GUYS 23  // # of families; make sure to change the
// SIZE_FAMILIES in loader.cpp as well
// (or your code will act weird)

#define PIX(a,b) (NUM_GUYS*a+b)

//Weapon families
#define WEAP_KNIFE 0
#define WEAP_ROCK 1
#define WEAP_ARROW 2
#define WEAP_FIREBALL 3
#define WEAP_TREE 4
#define WEAP_METEOR 5
#define WEAP_SPRINKLE 6
#define WEAP_BONE 7
#define WEAP_BLOOD 8
#define WEAP_BLOB 9
#define WEAP_FIRE_ARROW 10
#define WEAP_LIGHTNING 11
#define WEAP_GLOW 12
#define WEAP_WAVE 13
#define WEAP_WAVE2 14
#define WEAP_WAVE3 15
#define WEAP_CIRCLE_PROTECTION 16
#define WEAP_HAMMER 17
#define WEAP_DOOR 18
#define WEAP_BOULDER 19
#define NUM_WEAPONS 20

// Treasure families
#define TRES_STAIN 0
#define TRES_DRUMSTICK 1
#define TRES_GOLD_BAR 2
#define TRES_SILVER_BAR 3
#define TRES_MAGIC_POTION 4
#define TRES_INVIS_POTION 5
#define TRES_INVULNERABLE_POTION 6
#define TRES_FLIGHT_POTION 7
#define TRES_EXIT 8
#define TRES_TELEPORTER 9
#define TRES_LIFE_GEM 10 // generated upon death
#define TRES_KEY 11
#define TRES_SPEED_POTION 12
#define MAX_TREASURE 12   // # of biggest treasure..  (why not +1?!?!?!?!)
#define NUM_TREASURES 13 //kat

// Generator families
#define GEN_TENT 0  // skeletons
#define GEN_TOWER 1 // mages
#define GEN_BONES 2 // ghosts
#define GEN_TREEHOUSE 3 // elves :)

// FX families
//#define FX_STAIN 0
#define FX_EXPAND 0
#define FX_GHOST_SCARE 1
#define FX_BOMB 2
#define FX_EXPLOSION 3      // Bombs, etc.
#define FX_FLASH 4          // Used for teleporter effects
#define FX_MAGIC_SHIELD 5   // revolving protective shield
#define FX_KNIFE_BACK  6    // Returning blade
#define FX_BOOMERANG  7     // Circling boomerang
#define FX_CLOUD 8          // purple poison cloud
#define FX_MARKER 9         // Marker for Mages Teleport
#define FX_CHAIN 10         // 'Chain lightning' effect
#define FX_DOOR_OPEN 11     // The open door
#define FX_HIT 12           // Show when hit

// Special families
#define FAMILY_RESERVED_TEAM 0

// Button graphic families
#define FAMILY_NORMAL1 0
#define FAMILY_PLUS 1
#define FAMILY_MINUS 2
#define FAMILY_WRENCH 3

// Facings
#define FACE_UP 0
#define FACE_UP_RIGHT 1
#define FACE_RIGHT 2
#define FACE_DOWN_RIGHT 3
#define FACE_DOWN 4
#define FACE_DOWN_LEFT 5
#define FACE_LEFT 6
#define FACE_UP_LEFT 7
#define NUM_FACINGS 8

// Stats defines
#define COMMAND_WALK 1
#define COMMAND_FIRE 2
#define COMMAND_RANDOM_WALK 3   // walk random dir ..
#define COMMAND_DIE 4   // bug fixing ..
#define COMMAND_FOLLOW 5
#define COMMAND_RUSH 6  // Rush your enemy!
#define COMMAND_MULTIDO 7 // Do <com1> commands in one round
#define COMMAND_QUICK_FIRE 8 // Fires with no busy or animation
#define COMMAND_SET_WEAPON 9 // set weapon type
#define COMMAND_RESET_WEAPON 10 // restores weapon to default
#define COMMAND_SEARCH 11       // use right-hand rule to find foe
#define COMMAND_ATTACK 12       // attack / move to a close, current foe
#define COMMAND_RIGHT_WALK 13   // use right-hand rule ONLY; no direct walk
#define COMMAND_UNCHARM 14      // recover from being 'charmed'
#define REGEN (Sint32) 4000       // used to calculate time between heals

#define STANDARD_TEXT_TIME 75   // how many cycles to display text?
#define TEXT_1 "text.pix"       // standard text pixie
#define TEXT_BIG "textbig.pix"       // standard text pixie

#define DONT_DELETE 1

#ifndef PROT_MODE
// sound
extern "C" short init_sound(char *filename, short speed, short which);
extern "C" void play_sound(short which);
#endif

class PixieData;

//most of these are graphlib and are being ported to video
void load_map_data(PixieData* whereto);
char* get_cfg_item(char *section, char *item);

// Functions in game.cpp
short load_saved_game(const char *filename, screen  *myscreen);

#define NORMAL_MODE    0     // #defines for walkputbuffer mode type
#define INVISIBLE_MODE 1     //
#define PHANTOM_MODE   2     //
#define OUTLINE_MODE   3     //

#define SHIFT_LIGHTER      0  //  #defines for phantomputbuffer
#define SHIFT_DARKER       1  //
#define SHIFT_LEFT         2  //
#define SHIFT_RIGHT        3  //
#define SHIFT_RIGHT_RANDOM 4  //  shifts right 1 or 2 spaces (whole image)
#define SHIFT_RANDOM       5  //  shifts 1 or 2 right (on pixel x pixel basis)
#define SHIFT_BLOCKY       6  //  courtroom style


#define SCEN_TYPE_CAN_EXIT (char) 1 // make these go by power of 2, 1,2,4,8
#define SCEN_TYPE_GEN_EXIT (char) 2
#define SCEN_TYPE_SAVE_ALL (char) 4 // save named npc's

#define OUTLINE_NAMED         7              // #defines for outline colors
#define OUTLINE_INVULNERABLE  224            //
#define OUTLINE_FLYING        208            //
#define OUTLINE_INVISIBLE query_team_color() //

#define ACTION_FOLLOW (char) 1

#include "pixie_data.h"

PixieData read_pixie_file(const char  * filename);

// Some stuff for palette
typedef struct
{
	char r, g, b;
}rgb;

typedef rgb palette[256];

void set_vga_palette(palette p);
rgb set_rgb(char r, char g, char b);
short read_palette(FILE  *f, palette p);


