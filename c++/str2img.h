#ifndef _str2img_h
#define _str2img_h

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat oneStr2oneImg (const string& text, int fontFace, int thickness, Scalar color);

void mergeMultiImg (Mat mainImg, vector<Point2i> pos, vector<Mat> Imgs);

#endif