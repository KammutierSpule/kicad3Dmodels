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


#ifndef VERSION_H
#define VERSION_H

#include <QString>

// when you make incompatible API changes
#define VER_MAJOR 0

// when you add functionality in a backwards-compatible manner
#define VER_MINOR 1

// when you make backwards-compatible bug fixes
#define VER_PATCH 3

extern const QString g_VersionStr;

extern const QString g_VRML_Header;

#endif
