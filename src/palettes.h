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

char rainbow_pal[] =
    {
        0, 0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 0,
        4, 4, 0, 5, 5, 0, 6, 6, 0, 7, 7, 0,
        8, 8, 0, 9, 9, 0, 10, 10, 0, 11, 11, 0,
        12, 12, 0, 13, 13, 0, 14, 14, 0, 15, 15, 0,
        16, 16, 0, 17, 17, 0, 18, 18, 0, 19, 19, 0,
        20, 20, 0, 21, 21, 0, 22, 22, 0, 23, 23, 0,
        24, 24, 0, 25, 25, 0, 26, 26, 0, 27, 27, 0,
        28, 28, 0, 29, 29, 0, 30, 30, 0, 31, 31, 0,
        32, 32, 0, 33, 33, 0, 34, 34, 0, 35, 35, 0,
        36, 36, 0, 37, 37, 0, 38, 38, 0, 39, 39, 0,
        40, 40, 0, 41, 41, 0, 42, 42, 0, 43, 43, 0,
        44, 44, 0, 45, 45, 0, 46, 46, 0, 47, 47, 0,
        48, 48, 0, 49, 49, 0, 50, 50, 0, 51, 51, 0,
        52, 52, 0, 53, 53, 0, 54, 54, 0, 55, 55, 0,
        56, 56, 0, 57, 57, 0, 58, 58, 0, 59, 59, 0,
        60, 60, 0, 61, 61, 0, 62, 62, 0, 63, 63, 0,
        63, 63, 0, 63, 62, 1, 63, 61, 2, 63, 60, 3,
        63, 59, 4, 63, 58, 5, 63, 57, 6, 63, 56, 7,
        63, 55, 8, 63, 54, 9, 63, 53, 10, 63, 52, 11,
        63, 51, 12, 63, 50, 13, 63, 49, 14, 63, 48, 15,
        63, 47, 16, 63, 46, 17, 63, 45, 18, 63, 44, 19,
        63, 43, 20, 63, 42, 21, 63, 41, 22, 63, 40, 23,
        63, 39, 24, 63, 38, 25, 63, 37, 26, 63, 36, 27,
        63, 35, 28, 63, 34, 29, 63, 33, 30, 63, 32, 31,
        63, 31, 32, 63, 30, 33, 63, 29, 34, 63, 28, 35,
        63, 27, 36, 63, 26, 37, 63, 25, 38, 63, 24, 39,
        63, 23, 40, 63, 22, 41, 63, 21, 42, 63, 20, 43,
        63, 19, 44, 63, 18, 45, 63, 17, 46, 63, 16, 47,
        63, 15, 48, 63, 14, 49, 63, 13, 50, 63, 12, 51,
        63, 11, 52, 63, 10, 53, 63, 9, 54, 63, 8, 55,
        63, 7, 56, 63, 6, 57, 63, 5, 58, 63, 4, 59,
        63, 3, 60, 63, 2, 61, 63, 1, 62, 63, 0, 63,
        63, 0, 63, 62, 1, 63, 61, 2, 63, 60, 3, 63,
        59, 4, 63, 58, 5, 63, 57, 6, 63, 56, 7, 63,
        55, 8, 63, 54, 9, 63, 53, 10, 63, 52, 11, 63,
        51, 12, 63, 50, 13, 63, 49, 14, 63, 48, 15, 63,
        47, 16, 63, 46, 17, 63, 45, 18, 63, 44, 19, 63,
        43, 20, 63, 42, 21, 63, 41, 22, 63, 40, 23, 63,
        39, 24, 63, 38, 25, 63, 37, 26, 63, 36, 27, 63,
        35, 28, 63, 34, 29, 63, 33, 30, 63, 32, 31, 63,
        31, 32, 63, 30, 33, 63, 29, 34, 63, 28, 35, 63,
        27, 36, 63, 26, 37, 63, 25, 38, 63, 24, 39, 63,
        23, 40, 63, 22, 41, 63, 21, 42, 63, 20, 43, 63,
        19, 44, 63, 18, 45, 63, 17, 46, 63, 16, 47, 63,
        15, 48, 63, 14, 49, 63, 13, 50, 63, 12, 51, 63,
        11, 52, 63, 10, 53, 63, 9, 54, 63, 8, 55, 63,
        7, 56, 63, 6, 57, 63, 5, 58, 63, 4, 59, 63,
        3, 60, 63, 2, 61, 63, 1, 62, 63, 0, 63, 63,
        0, 63, 63, 0, 62, 62, 0, 61, 61, 0, 60, 60,
        0, 59, 59, 0, 58, 58, 0, 57, 57, 0, 56, 56,
        0, 55, 55, 0, 54, 54, 0, 53, 53, 0, 52, 52,
        0, 51, 51, 0, 50, 50, 0, 49, 49, 0, 48, 48,
        0, 47, 47, 0, 46, 46, 0, 45, 45, 0, 44, 44,
        0, 43, 43, 0, 42, 42, 0, 41, 41, 0, 40, 40,
        0, 39, 39, 0, 38, 38, 0, 37, 37, 0, 36, 36,
        0, 35, 35, 0, 34, 34, 0, 33, 33, 0, 32, 32,
        0, 31, 31, 0, 30, 30, 0, 29, 29, 0, 28, 28,
        0, 27, 27, 0, 26, 26, 0, 25, 25, 0, 24, 24,
        0, 23, 23, 0, 22, 22, 0, 21, 21, 0, 20, 20,
        0, 19, 19, 0, 18, 18, 0, 17, 17, 0, 16, 16,
        0, 15, 15, 0, 14, 14, 0, 13, 13, 0, 12, 12,
        0, 11, 11, 0, 10, 10, 0, 9, 9, 0, 8, 8,
        0, 7, 7, 0, 6, 6, 0, 5, 5, 0, 4, 4,
        0, 3, 3, 0, 2, 2, 0, 1, 1, 0, 0, 0
    };
