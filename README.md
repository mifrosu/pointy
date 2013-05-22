pointy
======

Pointy is intended as a Qt/QML implementation of Pinpoint.

Pinpoint is available from https://live.gnome.org/Pinpoint
and was developed by the following authors:

Øyvind Kolås, Damien Lespiau, Emmanuele Bassi, Neil Roberts,
Nick Richards, daniel g. siegel, Jussi Kukkonen, Chris Lord,
Will Thompson, Andoni Morales Alastruey, Vladimír Kincl,
Antonio Terceiro, Gary Ching-Pang Lin, Lionel Landwerlin, 
and Christoph Fischer 

Pointy was developed as a didactic exercise. The graphical
interface is implemented in QML on top of Qt/C++, using
test driven development (TDD) with QtTest. 

## Known Issues ##

Flickering during slide fade transitions was observed on KDE using nVidia and Nouveau graphics drivers. This distortion did not occur if desktop effects were switched off (the default shortcut to do this on KDE is Alt-Shift-F12). Pointy exhibited flicker on Gnome-Shell (Fedora 18) with the Nouveau driver, but not with the nVidia driver. No such distortion has been observed, so far, with Intel graphics chips.
