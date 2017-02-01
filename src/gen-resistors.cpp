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

// Includes
// /////////////////////////////////////////////////////////////////////////////

#include <QtGlobal>
#include <QDir>
#include <QTextStream>
#include <QDataStream>

#include "version.h"
#include "resistors.h"

static bool generate_ResistorBand( QString aPath,
                                   eResistorType aResType,
                                   eResistorPower aResPower,
                                   eResistorBandType aBandType,
                                   int aBand1, int aBand2, int aBand3, int aBand4, int aBand5, int aBand6 )
{
    // http://www.resistorguide.com/pictures/resistor_color_codes_chart.png

    Q_ASSERT( aBand1 >= 0 );
    Q_ASSERT( aBand2 >= 0 );
    Q_ASSERT( aBand3 >= 0 );

    QString fileName;

    if( aBandType < RES_BAND_5 )
    {
        fileName = "R" + QString::number(aBand1) +
                         QString::number(aBand2) +
                         QString::number(aBand3) + ".wrl";
    }
    else
    {
        fileName = "R" + QString::number(aBand1) +
                         QString::number(aBand2) +
                         QString::number(aBand3) +
                         QString::number(aBand4) +".wrl";
    }


    QFile file( aPath + fileName );

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

    stream << g_VRML_Header;

    // Add the resistence rings
    switch( aBandType )
    {
        case RES_BAND_4:
            stream << "Transform { translation -.90 0 .51 scale .55 1.22 1.22 children [ Inline { url \"../ring_" + QString::number(aBand1) + ".wrl\" } ] }\n";
            stream << "Transform { translation -.53 0 .51 scale .55 1.04 1.04 children [ Inline { url \"../ring_" + QString::number(aBand2) + ".wrl\" } ] }\n";
            stream << "Transform { translation -.18 0 .51 scale .55 1.03 1.03 children [ Inline { url \"../ring_" + QString::number(aBand3) + ".wrl\" } ] }\n";
            stream << "Transform { translation 0.80 0 .51 scale .55 1.22 1.22 children [ Inline { url \"../ring_" + QString::number(aBand4) + ".wrl\" } ] }\n";
        break;

        default:
            qFatal( "Error %d band type is not implemented.", aBandType );
        break;
    }

    // Add the resistence body
    switch( aResType )
    {
        case RES_TYPE_FILM_CARBON:
            switch( aResPower )
            {
                case RES_PWR_025W:
                    stream << "Inline { url \"../RESAD780W55L630D240B.wrl\" }\n";
                break;

                default:
                    qFatal( "Error resistence power: %d is not implemented for resistence type: %d", aResPower, aResType );
                break;
            }
        break;

        default:
            qFatal( "Error %d resistence type is not implemented.", aResType );
        break;
    }

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

    QString pathDir = aPath + "/" + "Resistors/"+
                      g_MapResTypeToString[aResType] + "/" +
                      g_MapResTypeToString[aResType] + "_" +
                      g_MapResTolToString[aResTolerance] + "TOL_" +
                      g_MapBandToString[aBandType] + "B_" +
                      g_MapResPwrToString[aResPower] + "W" +
                      "/";

    QDir dir( pathDir );

    if( dir.exists() == false )
    {
        if( dir.mkpath( "." ) == false )
        {
            qFatal( "Cannot create path %s.", pathDir.toUtf8().data() );

            return false;
        }
    }

    switch( aBandType )
    {
        case RES_BAND_4:
            for( int value1 = 0; value1 < 10; ++value1 )
            {
                for( int value2 = 0; value2 < 10; ++value2 )
                {
                    for( int value3 = 0; value3 < 10; ++value3 )
                    {
                        generate_ResistorBand( pathDir,
                                               aResType,
                                               aResPower,
                                               aBandType,
                                               value1,
                                               value2,
                                               value3,
                                               g_MapResTolToNumber[aResTolerance],
                                               -1,
                                               -1 );
                    }
                }
            }
        break;

        default:
            qFatal( "Error %d band type is not implemented.", aBandType );
        break;
    }



    return true;
}
