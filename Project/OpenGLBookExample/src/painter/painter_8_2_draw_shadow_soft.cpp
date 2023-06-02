#include "painter_8_2_draw_shadow_soft.h"

void Painter_8_2::init()
{
    title = "Example 8.2";

    vert = "./shader/s_8_1_shadow_pass1_vert.glsl";
    frag = "./shader/s_8_1_shadow_pass1_frag.glsl";

	vert2 = "./shader/s_8_1_shadow_pass2_vert.glsl";
	frag2 = "./shader/s_8_2_shadow_soft_pass2_frag.glsl";

    tex0 = "./res/model/shuttle/spstob_1.jpg";
    model0 = "./res/model/pyr/pyr.obj";
}
