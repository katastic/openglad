/* Copyright (C) 2002  Kari Pahula
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

#if defined(_MSC_VER)
	#pragma warning(disable : 4786)
#endif

#include "version.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "gparser.h"
#include "util.h"
#include "yam.h"

// TODO: Move overscan setting and toInt() to this file.
#include "input.h"
int toInt(const std::string& s);

using namespace std;

cfg_store cfg;

void cfg_store::apply_setting(const std::string& category, const std::string& setting, const std::string& value)
{
    data[category][setting] = value;
}

std::string cfg_store::get_setting(const std::string& category, const std::string& setting)
{
	map<string, map<string, string> >::iterator a1 = data.find(category);
	if(a1 != data.end())
	{
		map<string, string>::iterator a2 = a1->second.find(setting);
		if(a2 != a1->second.end())
			return a2->second;
	}
	
	return "";
}

#include "common.h"

bool cfg_store::load_settings()
{
    // Load defaults
    apply_setting("", "version", "1");
    apply_setting("sound", "sound", "on");

    apply_setting("graphics", "render", "normal");
    apply_setting("graphics", "fullscreen", "off");
    apply_setting("graphics", "overscan_percentage", "0");
    
    apply_setting("effects", "gore", "on");
    apply_setting("effects", "mini_hp_bar", "on");
    apply_setting("effects", "hit_flash", "on");
    apply_setting("effects", "hit_recoil", "off");
    apply_setting("effects", "attack_lunge", "on");
    apply_setting("effects", "hit_anim", "on");
    apply_setting("effects", "damage_numbers", "off");
    apply_setting("effects", "heal_numbers", "on");
    
    Log("Loading settings\n");
    SDL_RWops* rwops = open_read_file("cfg/openglad.yaml");
    if(rwops == NULL)
	{
		Log("Could not open config file. Using defaults.");
		return false;
	}
    
    Yam yam;
    yam.set_input(rwops_read_handler, rwops);
    
    std::string last_scalar;
    std::string current_category;
    
    Yam::ParseResultEnum parse_result;
    while((parse_result = yam.parse_next()) == Yam::OK)
    {
        switch(yam.event.type)
        {
            case Yam::BEGIN_SEQUENCE:
                break;
            case Yam::END_SEQUENCE:
                break;
            case Yam::BEGIN_MAPPING:
                current_category = last_scalar;
                break;
            case Yam::END_MAPPING:
                break;
            case Yam::ALIAS:
                break;
            case Yam::PAIR:
                apply_setting(current_category, yam.event.scalar, yam.event.value);
                break;
            case Yam::SCALAR:
                last_scalar = yam.event.scalar;
                break;
            default:
                break;
        }
    }
    
    if(parse_result == Yam::ERROR)
        Log("Parsing error.\n");
    
    yam.close_input();
    SDL_RWclose(rwops);
    
    // Update game stuff from these settings
    overscan_percentage = toInt(get_setting("graphics", "overscan_percentage"))/100.0f;
    update_overscan_setting();
    
    char player_string[] = "player#";
    for(int i=1; i <= 4; ++i)
        {
        player_string[6] = i+'0';

        player_keys[i-1][KEY_UP] = toInt(get_setting(player_string, "up"));
        player_keys[i-1][KEY_UP_RIGHT] = toInt(get_setting(player_string, "up-right"));
        player_keys[i-1][KEY_RIGHT] = toInt(get_setting(player_string, "right"));
        player_keys[i-1][KEY_DOWN_RIGHT] = toInt(get_setting(player_string, "down-right"));
        player_keys[i-1][KEY_DOWN] = toInt(get_setting(player_string, "down"));  
        player_keys[i-1][KEY_DOWN_LEFT] = toInt(get_setting(player_string, "down-left"));
        player_keys[i-1][KEY_LEFT] = toInt(get_setting(player_string, "left"));
        player_keys[i-1][KEY_UP_LEFT] = toInt(get_setting(player_string, "up-left"));
        
        player_keys[i-1][KEY_FIRE] = toInt(get_setting(player_string, "fire"));
        printf("%s fire key: [[%s]]\n", player_string, get_setting(player_string, "fire").c_str());        
        
        player_keys[i-1][KEY_SPECIAL] = toInt(get_setting(player_string, "special"));
        player_keys[i-1][KEY_SWITCH] = toInt(get_setting(player_string, "switch"));
        player_keys[i-1][KEY_SPECIAL_SWITCH] = toInt(get_setting(player_string, "special-switch"));
        player_keys[i-1][KEY_YELL] = toInt(get_setting(player_string, "yell"));
        player_keys[i-1][KEY_SHIFTER] = toInt(get_setting(player_string, "shifter"));
        player_keys[i-1][KEY_PREFS] = toInt(get_setting(player_string, "prefs"));
        player_keys[i-1][KEY_CHEAT] = toInt(get_setting(player_string, "cheat"));

        
        }
   /*
   #define KEY_UP                  0
#define KEY_UP_RIGHT            1
#define KEY_RIGHT               2
#define KEY_DOWN_RIGHT          3
#define KEY_DOWN                4
#define KEY_DOWN_LEFT           5
#define KEY_LEFT                6
#define KEY_UP_LEFT             7
#define KEY_FIRE                8
#define KEY_SPECIAL             9
#define KEY_SWITCH              10
#define KEY_SPECIAL_SWITCH      11
#define KEY_YELL                12
#define KEY_SHIFTER             13
#define KEY_PREFS               14
#define KEY_CHEAT               15
#define NUM_KEYS                16
*/



	return true;
}


bool cfg_store::save_settings()
{
    char buf[40];
    snprintf(buf, 40, "%.0f", 100*overscan_percentage);
    apply_setting("graphics", "overscan_percentage", buf);
    
    SDL_RWops* outfile = open_write_file("cfg/openglad.yaml");
    if(outfile != NULL)
    {
        Log("Saving settings\n");
        
        Yam yam;
        yam.set_output(rwops_write_handler, outfile);
        
        // Each category is a mapping that holds setting/value pairs
        for(auto e = data.begin(); e != data.end(); e++)
        {
            if(e->first.size() > 0)
            {
                yam.emit_scalar(e->first.c_str());
                yam.emit_begin_mapping();
            }
            
            for(auto f = e->second.begin(); f != e->second.end(); f++)
            {
                yam.emit_pair(f->first.c_str(), f->second.c_str());
            }
            
            if(e->first.size() > 0)
            {
                yam.emit_end_mapping();
            }
        }
        
        yam.close_output();
        SDL_RWclose(outfile);
        
        return true;
    }
    else
    {
        Log("Couldn't open cfg/openglad.yaml for writing.\n");
        return false;
    }
}

void cfg_store::commandline(const int &argc, char **&argv)
{
	const char helpmsg[] = 
"Usage: openglad [-d -f ...]\n"
"  -s		Turn sound on\n"
"  -S		Turn sound off\n"
"  -n		Run at 320x200 resolution\n"
"  -d		Double pixel size\n"
"  -e		Use eagle engine for pixel doubling\n"
"  -i		Use sai2x engine for pixel doubling\n"
"  -f		Use full screen\n"
"  -h		Print a summary of the options\n"
"  -v		Print the version number\n";

	const char versmsg[] = "openglad version " OPENGLAD_VERSION_STRING "\n";

	// Begin changes by David Storey (Deathifier)
	// FIX: Handle mutually exclusive arguments being used at the same time?
	// E.G. -s and -S

	// Iterate over arguments, ignoring the first (Program Name).
	for(int argnum = 1; argnum < argc; argnum++)
	{
		// Look for arguments of 2 chars only:
		if(argv[argnum][0] == '-' && strlen(argv[argnum]) == 2)
		{
			// To handle arguments which have aditional arguments attached
			// to them, take care of it within the case statement and
			// increment argnum appropriately.
			switch(argv[argnum][1])
			{
				case 'h':
					Log("%s", helpmsg);
					exit (0);
				case 'v':
					Log("%s", versmsg);
					exit (0);
				case 's':
					data["sound"]["sound"] = "on";
					Log("Sound is on.");
					break;
				case 'S':
					data["sound"]["sound"] = "off";
					Log("Sound is off.");
					break;
				case 'n':
					data["graphics"]["render"] = "normal";
					Log("Screen Resolution set to 320x200.");
					break;
				case 'd':
					data["graphics"]["render"] = "double";
					Log("Screen Resolution set to 640x400 (basic mode).");
					break;
				case 'e':
					data["graphics"]["render"] = "eagle";
					Log("Screen Resolution set to 640x400 (eagle mode).");
					break;
				case 'x':
					data["graphics"]["render"] = "sai";
					Log("Screen Resolution set to 640x400 (sai2x mode).");
					break;
				case 'f':
					data["graphics"]["fullscreen"] = "on";
					Log("Running in fullscreen mode.");
					break;
				default:
					Log("Unknown argument %s ignored.", argv[argnum]);
			}
		}
	}

	// End Changes
}


bool cfg_store::is_on(const std::string& category, const std::string& setting)
{
    return get_setting(category, setting) == "on";
}

