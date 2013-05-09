#include "slide_data.h"

namespace pointy {

SlideData::SlideData():
    stageColor("black"), font("Sans 60px"), notesFont("Sans"),
    notesFontSize("20px"), textColor("white"), textAlign("left"),
    shadingColor("black"), shadingOpacity(0.66), duration(30),
    command(), transition("fade"), backgroundScale("fill"),
    position("center"), useMarkup(true), slideText(), slideMedia(),
    backgroundColor("white"), slideNumber(0)
{}

}
