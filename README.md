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

Observed using nVidia drivers with KDE on Debian Wheezy and Kubuntu 13.04:
The slide transition fade effect exhibits flickering. Switching off desktop compositing (the default KDE shortcut is Alt-Shift-F12) removes the flicker. 

