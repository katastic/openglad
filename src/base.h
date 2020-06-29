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

const unsigned int DIFFICULTY_SETTINGS = 3;

Uint32 random(Uint32 x);

const unsigned int VIDEO_ADDRESS = 0xA000;	//old crap, still used
const unsigned int VIDEO_LINEAR = ( (VIDEO_ADDRESS) << 4); //old crap, still used

const unsigned int DPMI_INT = 0x31;
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

const unsigned int MAX_LEVELS = 500; // Maximum number of scenarios allowed ..
//const unsigned int GRID_SIZE 16
const int GRID_SIZE = 16; //screw your lack of define debug symbols

const unsigned int PROT_MODE = 1;  // comment this out when not in protected mode
#ifdef PROT_MODE
  #define init_sound(x,y,z)  while (0)
//#define play_sound(x)      while (0)
#endif

// Used for the help-text system:
const unsigned int MAX_LINES = 100;   // maximum number of lines in helpfile
const unsigned int HELP_WIDTH = 100;   // maximum length of display line
short   fill_help_array(char somearray[HELP_WIDTH][MAX_LINES], SDL_RWops *infile);
short   read_campaign_intro(screen *myscreen);
short   read_scenario(screen  *myscreen);
char* read_one_line(SDL_RWops *infile, short length);

//color defines:
const unsigned int DEFAULT_TEXT_COLOR = 88;

const unsigned int PURE_WHITE   = 15;
const unsigned int PURE_BLACK   = 0;
const unsigned int WHITE        = 24;
const unsigned int BLACK        = 160;
const unsigned int GREY         = 23;
const unsigned int YELLOW       = 88;
const unsigned int RED          = 40;
const unsigned int DARK_BLUE    = 72;
const unsigned int LIGHT_BLUE   = 120;
const unsigned int DARK_GREEN   = 63;
const unsigned int LIGHT_GREEN  = 56;

// Color cycling:
const unsigned int WATER_START  = 208;
const unsigned int WATER_END    = 223;
const unsigned int ORANGE_START = 224;
const unsigned int ORANGE_END   = 231;

// Random defines:
//const unsigned int PROFILING
//#include "profiler.h"
const unsigned int CHEAT_MODE = 1;  // set to 0 for no cheats..
// Picture Object class defs

// HP BAR COLOR DEFINES
const unsigned int BAR_BACK_COLOR = 11;
const unsigned int BOX_COLOR = 0;
const unsigned int LOW_HP_COLOR = 42;
const unsigned int MID_HP_COLOR = 237;
const unsigned int HIGH_HP_COLOR = 61;
const unsigned int MAX_HP_COLOR = 56; // When hp's are over max :)

// MP BAR COLOR DEFINES
const unsigned int LOW_MP_COLOR = 42;
const unsigned int MID_MP_COLOR = 108;
const unsigned int HIGH_MP_COLOR = 72;
const unsigned int MAX_MP_COLOR = 64; // When mp's are over max :)

// Generators are limited by this number
const unsigned int MAXOBS = 150;



// Act types
const unsigned int ACT_RANDOM = 0;
const unsigned int ACT_FIRE = 1;
const unsigned int ACT_CONTROL = 2;
const unsigned int ACT_GUARD = 3;
const unsigned int ACT_GENERATE = 4;
const unsigned int ACT_DIE = 5;
const unsigned int ACT_SIT = 6;

// Team types

//              //const unsigned int MY_TEAM 0
//              const unsigned int ELF_TEAM 1
//              const unsigned int KNIGHT_TEAM 2
//              const unsigned int MAX_TEAM 2

const unsigned int MAX_TEAM = 7;

// Other screen-type things
const unsigned int NUM_SPECIALS = 6;

// Animation Types : Livings
const unsigned int ANI_WALK = 0;
const unsigned int ANI_ATTACK = 1;
const unsigned int ANI_TELE_OUT = 2;
const unsigned int ANI_SKEL_GROW = 3;
const unsigned int ANI_TELE_IN = 3;
const unsigned int ANI_SLIME_SPLIT = 4;

// Animations types : weapons
const unsigned int ANI_GROW = 1; // Trees have no attack animation
const unsigned int ANI_GLOWGROW = 1; // Neither do sparkles
const unsigned int ANI_GLOWPULSE = 2; // sparkles cycling

// These are for effect objects ..
const unsigned int ANI_EXPAND_8 = 1; //1
const unsigned int ANI_DOOR_OPEN = 1; // Door opening
const unsigned int ANI_SCARE    = 1; // 2 ghost scare
const unsigned int ANI_BOMB     = 1; // 3 thief's bomb
const unsigned int ANI_EXPLODE  = 1; // 4
const unsigned int ANI_SPIN     = 1; // for the marker

// Orders
const unsigned int ORDER_LIVING = 0;
const unsigned int ORDER_WEAPON = 1;
const unsigned int ORDER_TREASURE = 2;
const unsigned int ORDER_GENERATOR = 3;
const unsigned int ORDER_FX = 4;
const unsigned int ORDER_SPECIAL = 5;
const unsigned int ORDER_BUTTON1 = 6;

// Living families
const unsigned int GUY_SOLDIER = 0;
const unsigned int GUY_ELF = 1;
const unsigned int GUY_ARCHER = 2;
const unsigned int GUY_MAGE = 3;
const unsigned int GUY_SKELETON = 4;
const unsigned int GUY_CLERIC = 5;
const unsigned int GUY_FIREELEMENTAL = 6;
const unsigned int GUY_FAERIE = 7;
const unsigned int GUY_SLIME = 8;
const unsigned int GUY_SMALL_SLIME = 9;
const unsigned int GUY_MEDIUM_SLIME = 10;
const unsigned int GUY_THIEF = 11;
const unsigned int GUY_GHOST = 12;
const unsigned int GUY_DRUID = 13;
const unsigned int GUY_ORC   = 14;
const unsigned int GUY_BIG_ORC = 15;
const unsigned int GUY_BARBARIAN = 16;
const unsigned int GUY_SUMMONER = 17; //HAS TO BE right BEFORE ARCHMAGE. looks like there's a bug if you add a character after empty data (like tower) with no picker stats
// See [guy.cpp:84]
const unsigned int GUY_BUILDER = 18;
const unsigned int GUY_ARCHMAGE = 19; 	//17
const unsigned int GUY_GOLEM = 20; 	//18
const unsigned int GUY_GIANT_SKELETON = 21; //19
const unsigned int GUY_TOWER1 = 22; //20

const unsigned int NUM_GUYS = 23;  // # of families; make sure to change the
// SIZE_FAMILIES in loader.cpp as well
// (or your code will act weird)

#define PIX(a,b) (NUM_GUYS*a+b)



//Weapon families
const unsigned int WEAP_KNIFE = 0;
const unsigned int WEAP_ROCK = 1;
const unsigned int WEAP_ARROW = 2;
const unsigned int WEAP_FIREBALL = 3;
const unsigned int WEAP_TREE = 4;
const unsigned int WEAP_METEOR = 5;
const unsigned int WEAP_SPRINKLE = 6;
const unsigned int WEAP_BONE = 7;
const unsigned int WEAP_BLOOD = 8;
const unsigned int WEAP_BLOB = 9;
const unsigned int WEAP_FIRE_ARROW = 10;
const unsigned int WEAP_LIGHTNING = 11;
const unsigned int WEAP_GLOW = 12;
const unsigned int WEAP_WAVE = 13;
const unsigned int WEAP_WAVE2 = 14;
const unsigned int WEAP_WAVE3 = 15;
const unsigned int WEAP_CIRCLE_PROTECTION = 16;
const unsigned int WEAP_HAMMER = 17;
const unsigned int WEAP_DOOR = 18;
const unsigned int WEAP_BOULDER = 19;
const unsigned int NUM_WEAPONS = 20;

// Treasure families
const unsigned int TRES_STAIN = 0;
const unsigned int TRES_DRUMSTICK = 1;
const unsigned int TRES_GOLD_BAR = 2;
const unsigned int TRES_SILVER_BAR = 3;
const unsigned int TRES_MAGIC_POTION = 4;
const unsigned int TRES_INVIS_POTION = 5;
const unsigned int TRES_INVULNERABLE_POTION = 6;
const unsigned int TRES_FLIGHT_POTION = 7;
const unsigned int TRES_EXIT = 8;
const unsigned int TRES_TELEPORTER = 9;
const unsigned int TRES_LIFE_GEM = 10; // generated upon death
const unsigned int TRES_KEY = 11;
const unsigned int TRES_SPEED_POTION = 12;
const unsigned int MAX_TREASURE = 12;   // # of biggest treasure..  (why not +1?!?!?!?!)
const unsigned int NUM_TREASURES = 13; //kat

// Generator families
const unsigned int GEN_TENT = 0;  // skeletons
const unsigned int GEN_TOWER = 1; // mages
const unsigned int GEN_BONES = 2; // ghosts
const unsigned int GEN_TREEHOUSE = 3; // elves :)

// FX families
//const unsigned int FX_STAIN 0
const unsigned int FX_EXPAND = 0;
const unsigned int FX_GHOST_SCARE = 1;
const unsigned int FX_BOMB = 2;
const unsigned int FX_EXPLOSION = 3;      // Bombs, etc.
const unsigned int FX_FLASH = 4;          // Used for teleporter effects
const unsigned int FX_MAGIC_SHIELD = 5;   // revolving protective shield
const unsigned int FX_KNIFE_BACK = 6;    // Returning blade
const unsigned int FX_BOOMERANG = 7;     // Circling boomerang
const unsigned int FX_CLOUD = 8;          // purple poison cloud
const unsigned int FX_MARKER = 9;         // Marker for Mages Teleport
const unsigned int FX_CHAIN = 10;         // 'Chain lightning' effect
const unsigned int FX_DOOR_OPEN = 11;     // The open door
const unsigned int FX_HIT = 12;           // Show when hit

// Special families
const unsigned int FAMILY_RESERVED_TEAM = 0;

// Button graphic families
const unsigned int FAMILY_NORMAL1 = 0;
const unsigned int FAMILY_PLUS = 1;
const unsigned int FAMILY_MINUS = 2;
const unsigned int FAMILY_WRENCH = 3;

// Facings
const unsigned int FACE_UP = 0;
const unsigned int FACE_UP_RIGHT = 1;
const unsigned int FACE_RIGHT = 2;
const unsigned int FACE_DOWN_RIGHT = 3;
const unsigned int FACE_DOWN = 4;
const unsigned int FACE_DOWN_LEFT = 5;
const unsigned int FACE_LEFT = 6;
const unsigned int FACE_UP_LEFT = 7;
const unsigned int NUM_FACINGS = 8;

// Stats defines
const unsigned int COMMAND_WALK = 1;
const unsigned int COMMAND_FIRE = 2;
const unsigned int COMMAND_RANDOM_WALK = 3;   // walk random dir ..
const unsigned int COMMAND_DIE = 4;   // bug fixing ..
const unsigned int COMMAND_FOLLOW = 5;
const unsigned int COMMAND_RUSH = 6;  // Rush your enemy!
const unsigned int COMMAND_MULTIDO = 7; // Do <com1> commands in one round
const unsigned int COMMAND_QUICK_FIRE = 8; // Fires with no busy or animation
const unsigned int COMMAND_SET_WEAPON = 9; // set weapon type
const unsigned int COMMAND_RESET_WEAPON = 10; // restores weapon to default
const unsigned int COMMAND_SEARCH = 11;       // use right-hand rule to find foe
const unsigned int COMMAND_ATTACK = 12;       // attack / move to a close, current foe
const unsigned int COMMAND_RIGHT_WALK = 13;   // use right-hand rule ONLY; no direct walk
const unsigned int COMMAND_UNCHARM = 14;      // recover from being 'charmed'
const Sint32 REGEN = 4000;       // used to calculate time between heals

const unsigned int STANDARD_TEXT_TIME = 75;   // how many cycles to display text?
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

const unsigned int NORMAL_MODE    =0;     // #defines for walkputbuffer mode type
const unsigned int INVISIBLE_MODE =1;     //
const unsigned int PHANTOM_MODE   =2;     //
const unsigned int OUTLINE_MODE   =3;     //

const unsigned int SHIFT_LIGHTER      =0;  //  #defines for phantomputbuffer
const unsigned int SHIFT_DARKER       =1;  //
const unsigned int SHIFT_LEFT         =2;  //
const unsigned int SHIFT_RIGHT        =3;  //
const unsigned int SHIFT_RIGHT_RANDOM =4;  //  shifts right 1 or 2 spaces (whole image)
const unsigned int SHIFT_RANDOM       =5;  //  shifts 1 or 2 right (on pixel x pixel basis)
const unsigned int SHIFT_BLOCKY       =6;  //  courtroom style


const char SCEN_TYPE_CAN_EXIT = 1; // make these go by power of 2, 1,2,4,8
const char SCEN_TYPE_GEN_EXIT = 2;
const char SCEN_TYPE_SAVE_ALL = 4; // save named npc's

const unsigned int OUTLINE_NAMED = 7;              // #defines for outline colors
const unsigned int OUTLINE_INVULNERABLE = 224;            //
const unsigned int OUTLINE_FLYING = 208;            //
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


