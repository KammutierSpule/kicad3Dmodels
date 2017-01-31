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


#include <QtGlobal>
#include <QDir>
#include <QTextStream>
#include <QDataStream>

#include "resistors.h"

static bool generate_ResistorBand( QString aPath,
                                   eResistorType aResType,
                                   eResistorPower aResPower,
                                   int aBand1, int aBand2, int aBand3, int aBand4, int aBand5, int aBand6 )
{
    // http://www.resistorguide.com/pictures/resistor_color_codes_chart.png

    Q_ASSERT( aBand1 >= 0 );
    Q_ASSERT( aBand2 >= 0 );
    Q_ASSERT( aBand3 >= 0 );

    QString fileName = "R" +
                       aBand1 +
                       aBand2 +
                       aBand3 +
                       ((aBand4>=0)? QString::number(aBand4):"") +
                       ".wrl";


    QFile file( fileName );

    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qFatal( "Error opening the file %s for writting. error: %s",
                fileName.toUtf8().data(),
                file.errorString().toUtf8().data() );

        return false;
    }

    QTextStream stream( &file );

    stream.setPadChar( ' ' );
    stream.setFieldWidth( 0 );
    stream.setRealNumberNotation( QTextStream::FixedNotation );

    stream << "text" << "\n";

    file.close();

    return true;
}


bool GENERATE_Resistors( QString aPath,
                         eResistorType aResType,
                         eResistorPower aResPower,
                         eResistorBandType aBandType,
                         eResistorTolerance aResTolerance )
{
    Init_resistors();

    if( !QDir(aPath).exists() )
    {
        qFatal( "Path %s does not exists.", aPath.toUtf8().data() );

        return false;
    }

    QString pathDir = aPath + "/" +
                      "FilmCarbon_" + g_MapResTolToString[aResTolerance] + "TOL_" +
                      g_MapBandToString[aBandType] + "B" +
                      g_MapResPwrToString[aResPower] + "W" +
                      "/";

    QDir dir(pathDir);

    if( dir.exists() == false )
    {
        if( dir.mkpath(".") == false )
        {
            qFatal( "Cannot create path %s.", pathDir.toUtf8().data() );

            return false;
        }
    }
}
