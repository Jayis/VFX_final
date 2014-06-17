#ifndef _funcs_h
#define _funcs_h

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "misc.h"

using namespace std;
using namespace cv;

vector<KeyPoint> findGoodFeatures (const string& location, int start, int end);



#endif