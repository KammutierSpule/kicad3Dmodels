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
    RES_TYPE_FILM_CARBON = 0
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
    RES_PWR_025W    ///< 1/4 W
}eResistorPower;

// http://www.resistorguide.com/pictures/resistor_color_codes_chart.png

typedef enum
{
    RES_TOL_1,      ///< 1%     (F)
    RES_TOL_2,      ///< 2%     (G)
    RES_TOL_05,     ///< 0.5%   (D)
    RES_TOL_025,
    RES_TOL_01,
    RES_TOL_005,
    RES_TOL_5,
    RES_TOL_10,
    RES_TOL_20
}eResistorTolerance;

extern std::map <eResistorTolerance, int> g_MapResTolToNumber;
extern std::map <eResistorTolerance, QString> g_MapResTolToString;
extern std::map <eResistorTolerance, QString> g_MapResTolToPercentage;

extern std::map <eResistorBandType, int> g_MapBandToNumber;
extern std::map <eResistorBandType, QString> g_MapBandToString;

extern std::map <eResistorPower, QString> g_MapResPwrToString;

extern std::map <eResistorType, QString> g_MapResTypeToString;

void Init_resistors();

bool GENERATE_Resistors( QString aPath,
                         eResistorType aResType,
                         eResistorPower aResPower,
                         eResistorBandType aBandType,
                         eResistorTolerance aResTolerance );

#endif
