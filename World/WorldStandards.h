#ifndef WORLDSTANDARDS_H
#define WORLDSTANDARDS_H

#include <Box2D/Box2D.h>

namespace WorldStandards{ //! Contains Global variables (if you will) for World stuff. like ratios and debug info.


static float ratio = 30.0f;
static float ppm =1/50.0f;//multiply pixels by this to get b2d units
static float mpp = 50.0f;//multiply b2d by this to get pixels
static float unratio = mpp;
static float degtorad = (b2_pi / 180.0);
static float radtodeg = (180.0 / b2_pi);
static bool debug = true; //set to false to supress couts
static bool debug_step = false; //set to false to supress couts in stepping
static float rgrav_forceConst = 0.5;
static float minSpeed =.0085;
static float maxSpeed =.055;


};


#endif // WORLD_H
