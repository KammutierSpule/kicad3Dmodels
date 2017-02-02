/**
 * Tool for generation of 3D VRML models for KiCad based on 3D CAD seed models
 * Copyright (C) 2017 Mario Luzeiro (mrluzeiro@ua.pt)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef RESISTORS_H
#define RESISTORS_H

#include <map>
#include <QString>

typedef enum
{
    RES_TYPE_FILM_CARBON = 0,
    RES_TYPE_CHIP
}eResistorType;

// http://www.resistorguide.com/resistor-color-code/

typedef enum
{
    RES_BAND_3,
    RES_BAND_4,
    RES_BAND_5,
    RES_BAND_6
}eResistorBandType;

typedef enum
{
    RES_CHIP_EIA0402_METRIC1005,
    RES_CHIP_EIA0603_METRIC1608,
    RES_CHIP_EIA0805_METRIC2012,
    RES_CHIP_EIA1206_METRIC3216,
}eResistorChipType;

typedef enum
{
    RES_PWR_00625W, ///< 1/16 W
    RES_PWR_0125W,  ///< 1/8 W
    RES_PWR_025W,   ///< 1/4 W
    RES_PWR_05W,    ///< 1/2 W
    RES_PWR_1W,     ///< 1 W
    RES_PWR_2W      ///< 2 W
}eResistorPower;

// http://www.resistorguide.com/pictures/resistor_color_codes_chart.png

typedef enum
{
    RES_TOL_1,      ///< 1%     (F)
    RES_TOL_2,      ///< 2%     (G)
    RES_TOL_05,     ///< 0.5%   (D)
    RES_TOL_025,    ///< 0.25%
    RES_TOL_01,     ///< 0.10%
    RES_TOL_005,    ///< 0.05%
    RES_TOL_5,      ///< 5%
    RES_TOL_10,     ///< 10%
    RES_TOL_20      ///< 20%
}eResistorTolerance;

// Global vars
// /////////////////////////////////////////////////////////////////////////////

extern std::map <eResistorTolerance, int> g_MapResTolToNumber;
extern std::map <eResistorTolerance, QString> g_MapResTolToString;
extern std::map <eResistorTolerance, QString> g_MapResTolToPercentage;

extern std::map <eResistorBandType, int> g_MapBandToNumber;
extern std::map <eResistorBandType, QString> g_MapBandToString;

extern std::map <eResistorPower, QString> g_MapResPwrToString;

extern std::map <eResistorType, QString> g_MapResTypeToString;

extern std::map <eResistorChipType, QString> g_MapChipTypeToString;

// Public prototypes
// /////////////////////////////////////////////////////////////////////////////

void Init_resistors();

bool GENERATE_Resistors( QString aPath,
                         eResistorType aResType,
                         eResistorPower aResPower,
                         eResistorBandType aBandType,
                         eResistorTolerance aResTolerance );

bool GENERATE_ResistorsChip( QString aPath,
                             eResistorChipType aChipType );

#endif
