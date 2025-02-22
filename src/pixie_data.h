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

//#pragma once this blows up static analzers because they have HEADERS that include HEADERS.
//still compiles though.
#ifndef HEADER_PIXIEDATA
#define HEADER_PIXIEDATA

class PixieData
{
    public:
    
    unsigned char frames;
    unsigned char w, h;
    unsigned char* data;
    
    PixieData();
    PixieData(unsigned char frames, unsigned char w, unsigned char h, unsigned char* data);
    
    bool valid() const;
    
    void clear();
    void free();
};
#endif