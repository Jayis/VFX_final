#include "funcs.h"

vector<KeyPoint> findGoodFeatures (const string& location, int start, int end)
{
	int skip = 11;

	Mat img_0 = imread(location + num2string(start) + ".jpg",CV_LOAD_IMAGE_GRAYSCALE);
	//resize(img_0, img_0, Size(0,0), 0.5,0.5);

	Mat img_temp;

	int minHessian = 400;
	SurfFeatureDetector detector( minHessian );
	SurfDescriptorExtractor extractor;
	BFMatcher matcher;
	vector< DMatch > matches;
	vector< DMatch > good_matches;
	double max_dist = 0; double min_dist = 100; double dist;
	vector<KeyPoint> keypoints_0, keypoints_temp, keypoints_good;	
	Mat descriptors_0,descriptors_temp;
	
	detector.detect( img_0, keypoints_0 );

	for (int t = skip; t <= end; t+=skip){
		printf("feat_size:%d\n", keypoints_0.size());

		max_dist = 0; min_dist = 100;
		img_temp = imread(location + num2string(t) + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);
		//resize(img_temp, img_temp, Size(0,0), 0.5,0.5);
		keypoints_temp.clear();
		keypoints_good.clear();
		good_matches.clear();
		matches.clear();
				
		detector.detect( img_temp, keypoints_temp );
		extractor.compute( img_0, keypoints_0, descriptors_0 );
		extractor.compute( img_temp, keypoints_temp, descriptors_temp );
		
		matcher.match( descriptors_0, descriptors_temp, matches );

		for( int i = 0; i < descriptors_0.rows; i++ )  { 
			dist = matches[i].distance;
			if( dist < min_dist ) min_dist = dist;
			if( dist > max_dist ) max_dist = dist;
		}
		for( int i = 0; i < descriptors_0.rows; i++ )  {
			if( matches[i].distance <= max(2*min_dist, 0.13) )  { 
				good_matches.push_back( matches[i]);
			}
		}

		// draw
		Mat img_matches;
		drawMatches( img_0, keypoints_0, img_temp, keypoints_temp,
			good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

		//-- Show detected matches
		namedWindow("Good Matches" + num2string(t),WINDOW_AUTOSIZE);
		imshow( "Good Matches" + num2string(t), img_matches );
		
		// make good feats to next round
		for (int i = 0; i < good_matches.size(); i++) {
			keypoints_good.push_back(keypoints_0[good_matches[i].queryIdx]);
		}
		keypoints_0 = keypoints_good;
	}
	Mat img_keypoints_0;
	drawKeypoints( img_0, keypoints_0, img_keypoints_0, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	imshow("Keypoints", img_keypoints_0 );	

	return keypoints_0;
}