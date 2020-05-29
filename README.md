# kicad3Dmodels
Tool for generation of 3D VRML models for KiCad based on 3D CAD seed models
The main propose of this generator is to create models for each different values of the components (eg: different resistor color codes or SMD digit values) 

> NOTE: The WRL files can only be used by the (upcoming) version 5 of KiCad or with the Nightly Development Builds version.

# Licenses

## Source code
The software source code in the 'src'folder is licensed under the "GNU GENERAL PUBLIC LICENSE Version 3". Please read 'src\LICENSE'

## 3D model files
The 3D model files on the 'generated' folder are licensed under a modified MIT license. Please read 'generated\LICENSE'

# Download pre-generated

You can access the generated folder https://github.com/KammutierSpule/kicad3Dmodels/tree/master/generated and look for pre-generated ZIP files.

# Usage instructions

Since KiCad 5 it is possible to add different 3D model file formats (STEP, IGES, VRML, X3D) to footprints.
If you only care about CAD correctness you should use STEP or IGES format as much as possible.
VRML and X3D file formats are not designed for use with CAD (they are triangle based formats without units).
If you would like to achieve better renders with KiCad, then you should use VRML format. The most important aspect is that it allows to set materials for the different parts of the model. Using the proper materials on the models it will generate more realistic renders.

This library has for each component type group a generic CAD model (eg: A Resistor CAD model in the format FreeCAD, STEP/or IGES) and has a generated VRML model files for each value (eg: a axial film resistor with each individual bands for different values)

The generated VRML files for each individual value model are very small since they use a (now supported) included property of the VRML format, alowing to reuse different files and individual transform it on a new file.
However, mind that KiCad 3DViewer will cache on your system the loaded generated models that will use more disk space but if you only use some model values, there should be no big issue with the disk space and caching.

# Generated Models

## Resistors

### Chip

#### EIA 0603 METRIC 1608
#### EIA 0805 METRIC 2012
#### EIA 1206 METRIC 3216
![EIA0805_METRIC2012](https://github.com/KammutierSpule/kicad3Dmodels/raw/master/generated/Resistors/Chip/EIA0805_METRIC2012-RenderDemo.jpg)

### Film Carbon

#### 1/4W 5%
![Film_Carbon_5TOL_4B_025W](https://raw.githubusercontent.com/KammutierSpule/kicad3Dmodels/master/generated/Resistors/Film_Carbon/Film_Carbon_5TOL_4B_025W-RenderDemo.jpg)

# Other KiCad 3D Libraries

## kicad-3d-models-in-freecad by Maurice
https://github.com/easyw/kicad-3d-models-in-freecad
https://github.com/easyw/kicad-3d-mcad-models

This is a CAD parametric generated library, generated via scripts on FreeCAD that will generate / convert to STEP and VRML model files.

## kicad3Dmodels by Cirilo
https://github.com/cbernardo/kicad3Dmodels

This is a parametric generated library that will generate VRML models only.

## Kicad Electronic CAD libraries by Walter Lain
http://www.smisioto.eu/elettronica/kicad

This is a well know library that was adopted to use on the KiCad official libraries. The models were modeled using the Wings3D that are converted to VRML models to be used on KiCad.
