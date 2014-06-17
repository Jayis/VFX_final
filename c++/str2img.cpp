#include "str2img.h"

Mat oneStr2oneImg (const string& text, int fontFace, int thickness, Scalar color)
{
	double fontScale = 1;
	int baseline = 0;
	Size textSize = getTextSize(text, fontFace,fontScale, thickness, &baseline);
	// scale to fit Height = 1000;
	fontScale *= 1000 / textSize.height;
	baseline += thickness;
	textSize = getTextSize(text, fontFace,fontScale, thickness, &baseline);
	Mat img1(textSize.height*1.1, textSize.width*1.2, CV_8UC3, Scalar(0,0,0));
	// center the text
	Point textOrg((img1.cols - textSize.width)/2,(img1.rows + textSize.height)/2);
	Mat img(textSize.height*1.5, textSize.width*1.2, CV_8UC3, Scalar(0,0,0));
	// then put the text itself
	putText(img, text, textOrg, fontFace, fontScale,color, thickness, 8);
	/*
	namedWindow( "gg window", WINDOW_AUTOSIZE );
	imshow( "gg window", img );
	waitKey(0);
	*/
	return img;
}

void mergeMultiImg (Mat mainImg, vector<Point2i> pos, vector<Mat> Imgs)
{
	unsigned char* big = mainImg.data;
	unsigned char* small;
	unsigned char* cur;
	int chn = mainImg.channels();

	for (int n = 0; n < pos.size(); n++) {
		small = Imgs[n].data;
		cur = big + (pos[n].y * mainImg.cols + pos[n].x) * chn;
		for (int i = 0; i < Imgs[n].rows; i++) {
			if (pos[n].y + i >= mainImg.rows || pos[n].y + i < 0) continue;
			for (int j = 0; j < Imgs[n].cols; j++) {
				if (pos[n].x + j >= mainImg.cols || pos[n].x + j < 0) continue;
				for (int c = 0; c < chn; c++) {
					cur[(i * mainImg.cols + j) * chn + c] += small[(i * Imgs[n].cols + j) * chn + c];
					if (cur[(i * mainImg.cols + j) * chn + c] > 255) cur[(i * mainImg.cols + j) * chn + c] = 255; 
				}
			}
		}
	}

	return ;
}
