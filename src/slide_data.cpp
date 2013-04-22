#include "slide_data.h"

namespace pointy {

SlideData::SlideData():
    stage_color("black"), font("Sans 60px"), notes_font("Sans"),
    notes_font_size("20px"), text_color("white"), text_align("left"),
    shading_color("black"), shading_opacity(0.66), duration(30),
    command(), transition("fade"), background_scale("fill"),
    position("center"), use_markup(true), slide_text(), slide_media()
{}

}
