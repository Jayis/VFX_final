#ifndef _UI_h
#define _UI_h

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#include "str2img.h"

static Point2i click;
static Mat back1, back2;

Mat determineFontImg();

vector<Point2i> drawQuad();

void onMouse(int event, int x, int y, int, void*);

#endif