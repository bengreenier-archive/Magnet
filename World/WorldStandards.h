#ifndef WORLDSTANDARDS_H
#define WORLDSTANDARDS_H

#include <Box2D/Box2D.h>

namespace WorldStandards{


static const float ratio = 30.0f;
static const float ppm =1/50.0f;//multiply pixels by this to get b2d units
static const float mpp = 50.0f;//multiply b2d by this to get pixels
static const float unratio = mpp;
static const float degtorad = (b2_pi / 180.0);
static const float radtodeg = (180.0 / b2_pi);


static const bool debug = false; //set to false to supress couts
static const bool debug_step = false; //set to false to supress couts in stepping


};



#endif // WORLD_H
