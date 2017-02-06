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


static bool generate_ResistorChip_3_digit( QString aPath,
                                           eResistorChipType aChipType,
                                           QString aDigit1, QString aDigit2, QString aDigit3 )
{
    QString fileName = aDigit1 + aDigit2 + aDigit3 + ".wrl";

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

    // Add the resistence values and body
    switch( aChipType )
    {
        case RES_CHIP_EIA0603_METRIC1608:
            if (!(( aDigit1 == "0") && ( aDigit2 == "0") && ( aDigit3 == "0")))
            {
                stream << "Transform { translation -0.17 0.10 0.125 scale 0.5 0.5 0.2 children [ Inline { url \"../" + aDigit1 + ".wrl\" } ] }\n";
                stream << "Transform { translation -0.05 0.10 0.125 scale 0.5 0.5 0.2 children [ Inline { url \"../" + aDigit2 + ".wrl\" } ] }\n";
                stream << "Transform { translation +0.08 0.10 0.125 scale 0.5 0.5 0.2 children [ Inline { url \"../" + aDigit3 + ".wrl\" } ] }\n";

                if ( (( aDigit1 == "6") && ( aDigit2 == "6") && ( aDigit3 == "6") ) ||
                     (( aDigit1 == "9") && ( aDigit2 == "9") && ( aDigit3 == "9") ) )
                {
                    stream << "Transform { translation  0.0 -0.115 0.185 scale 0.8 0.05 0.04 children [ Inline { url \"../cube.wrl\" } ] }\n";
                }
            }
            else
            {
                stream << "Transform { translation -0.05 0.10 0.125 scale 0.5 0.5 0.2 children [ Inline { url \"../" + aDigit2 + ".wrl\" } ] }\n";
            }


            stream << "Inline { url \"../RESC1608X50_EIA0603_METRIC1608.wrl\" }\n";
        break;

        case RES_CHIP_EIA0805_METRIC2012:
            if (!(( aDigit1 == "0") && ( aDigit2 == "0") && ( aDigit3 == "0")))
            {
                stream << "Transform { translation -0.22 0.16 0.125 scale 0.7 0.7 0.3 children [ Inline { url \"../" + aDigit1 + ".wrl\" } ] }\n";
                stream << "Transform { translation -0.05 0.16 0.125 scale 0.7 0.7 0.3 children [ Inline { url \"../" + aDigit2 + ".wrl\" } ] }\n";
                stream << "Transform { translation +0.10 0.16 0.125 scale 0.7 0.7 0.3 children [ Inline { url \"../" + aDigit3 + ".wrl\" } ] }\n";

                if ( (( aDigit1 == "6") && ( aDigit2 == "6") && ( aDigit3 == "6") ) ||
                     (( aDigit1 == "9") && ( aDigit2 == "9") && ( aDigit3 == "9") ) )
                {
                    stream << "Transform { translation  0.0 -0.16 0.225 scale 1.1 0.09 0.04 children [ Inline { url \"../cube.wrl\" } ] }\n";
                }
            }
            else
            {
                stream << "Transform { translation -0.06 0.16 0.125 scale 0.7 0.7 0.3 children [ Inline { url \"../" + aDigit2 + ".wrl\" } ] }\n";
            }


            stream << "Inline { url \"../RESC2012X65_EIA0805_METRIC2012.wrl\" }\n";
        break;

        case RES_CHIP_EIA1206_METRIC3216:
            if (!(( aDigit1 == "0") && ( aDigit2 == "0") && ( aDigit3 == "0")))
            {
                stream << "Transform { translation -0.32 .23 .15 scale 1 1 .3 children [ Inline { url \"../" + aDigit1 + ".wrl\" } ] }\n";
                stream << "Transform { translation -0.08 .23 .15 scale 1 1 .3 children [ Inline { url \"../" + aDigit2 + ".wrl\" } ] }\n";
                stream << "Transform { translation .16 .23 .15 scale 1 1 .3 children [ Inline { url \"../" + aDigit3 + ".wrl\" } ] }\n";

                if ( (( aDigit1 == "6") && ( aDigit2 == "6") && ( aDigit3 == "6") ) ||
                     (( aDigit1 == "9") && ( aDigit2 == "9") && ( aDigit3 == "9") ) )
                {
                    stream << "Transform { translation  0 -0.22 .15 scale 1.6 .1 .3 children [ Inline { url \"../cube.wrl\" } ] }\n";
                }
            }
            else
            {
                stream << "Transform { translation -0.08 .20 .15 scale 1 1 .3 children [ Inline { url \"../" + aDigit2 + ".wrl\" } ] }\n";
            }


            stream << "Inline { url \"../RESC3216x66_EIA1206_METRIC3216.wrl\" }\n";
        break;

        default:
            qFatal( "Error %d chipt resistor type is not implemented.", aChipType );
        break;
    }

    file.close();

    return true;
}


bool GENERATE_ResistorsChip( QString aPath,
                             eResistorChipType aChipType )
{
    Init_resistors();

    if( !QDir(aPath).exists() )
    {
        qFatal( "Path %s does not exists.", aPath.toUtf8().data() );

        return false;
    }

    QString pathDir = aPath + "/" + "Resistors/"+
                      g_MapResTypeToString[RES_TYPE_CHIP] + "/" +
                      g_MapChipTypeToString[aChipType] +
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

    generate_ResistorChip_3_digit( pathDir, aChipType, QString::number(0), QString::number(0), QString::number(0) );

    // Rvv
    for( int value1 = 1; value1 < 10; ++value1 )
    {
        for( int value2 = 0; value2 < 10; ++value2 )
        {
            generate_ResistorChip_3_digit( pathDir, aChipType, "R", QString::number(value1), QString::number(value2) );
        }
    }

    // vRv
    for( int value1 = 1; value1 < 10; ++value1 )
    {
        for( int value2 = 0; value2 < 10; ++value2 )
        {
            generate_ResistorChip_3_digit( pathDir, aChipType, QString::number(value1), "R", QString::number(value2) );
        }
    }

    // vvv
    for( int value3 = 0; value3 < 10; ++value3 )
    {
        for( int value1 = 1; value1 < 10; ++value1 )
        {
            for( int value2 = 0; value2 < 10; ++value2 )
            {
                generate_ResistorChip_3_digit( pathDir, aChipType, QString::number(value1), QString::number(value2), QString::number(value3) );
            }
        }
    }

    return true;
}
