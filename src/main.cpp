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


#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDir>

#include "version.h"
#include "resistors.h"

int main(int argc, char *argv[])
{
    QCoreApplication app( argc, argv );
    QCoreApplication::setApplicationName("kicad3Dmodels generator");
    QCoreApplication::setApplicationVersion( g_VersionStr );

    QString outputPath = "../../generated/";

    // http://doc.qt.io/qt-5/qcommandlineparser.html

    QCommandLineParser parser;
    parser.setApplicationDescription("Help");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.setApplicationDescription( "kicad3Dmodels generator  Copyright (C) 2017  Mario Luzeiro\n" \
                                      "This program comes with ABSOLUTELY NO WARRANTY;\n" \
                                      "This is free software, and you are welcome to redistribute it\n" \
                                      "under conditions of GNU General Public License 3.\n"
                                      );

    parser.addPositionalArgument( "command",
                                  "The command to execute.\n\n" \
                                  "generate resistor carbon 0.25 - 1/4W film carbon resistor\n" \
                                  );

    // Process the actual command line arguments given by the user
    parser.process( app );

    const QStringList args = parser.positionalArguments();
    const QString command = args.isEmpty() ? QString() : args.first();

    if( command == "generate" )
    {
        /*
        GENERATE_Resistors( outputPath,
                            RES_TYPE_FILM_CARBON,
                            RES_PWR_025W,
                            RES_BAND_4,
                            RES_TOL_5 );
        */

        /*
        GENERATE_ResistorsChip( outputPath,
                                RES_CHIP_EIA0805_METRIC2012 );
        */

        /*
        GENERATE_ResistorsChip( outputPath,
                                RES_CHIP_EIA0603_METRIC1608 );
        */

        GENERATE_ResistorsChip( outputPath,
                                RES_CHIP_EIA1206_METRIC3216 );
    }

    //return app.exec();
    return 0;
}
