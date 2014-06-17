#include "UI.h"
/*
Mat determineFontImg ()
{
	int fontFace = FONT_HERSHEY_SIMPLEX;
	int thickness = 60;

	Mat scrn(1000,1000,CV_8UC3,Scalar(0,0,0));
	Mat output(1000,1000,CV_8UC3,Scalar(0,0,0));
	Mat strImg;
	namedWindow( "gg window", WINDOW_AUTOSIZE );

	int x1, x2, y1, y2;
	char keepon = 'N', correct = 'N';
	char gg[100];
	string text;	
	float r, g, b;
	int R, G, B;
	vector<Point2i> pos;
	vector<Mat> imgs;

	cout << "where do you want to put string?" << endl;
	while (keepon == 'N' || keepon == 'n') {
		correct = 'N';
		cout << "plz give me the Top-Left & Right-Bottom coordinate" << endl;
		cout << "Top-Left : ";
		cin >> x1 >> y1;
		cout << "Right-Bottom : ";
		cin >> x2 >> y2;
		rectangle(scrn, Point(x1,y1), Point(x2,y2), Scalar::all(255), 1, 8, 0);
		imshow( "gg window", scrn );
		waitKey(50);
		cout << "you sure?(Y/N)" << endl;
		cin >> keepon;
		if (keepon == 'y' || keepon == 'Y') {
			while (correct == 'N' || correct == 'n') {
				cout << "plz give me the string~" << endl;
				while (text.empty()) {
					getline(cin,text);
				}
				cout << "is that the string you want?(Y/N)" << endl;
				cin >> correct;
				if (correct == 'Y' || correct == 'y') {
					cout << "the color, plz? (0 ~ 1) (B G R)" << endl;
					cin >> b >> g >> r;
					R = r*255; G = g*255; B = b*255;
					strImg = oneStr2oneImg (text, fontFace, thickness, Scalar(B,G,R));
					resize (strImg, strImg, Size(x2-x1, y2-y1), 0, 0, INTER_CUBIC);
					pos.push_back(Point2i(x1,y1));
					imgs.push_back(strImg);
					mergeMultiImg (output, pos, imgs);
					pos.pop_back();
					imgs.pop_back();
					output.copyTo(scrn);
					imshow( "gg window", scrn );
					waitKey(50);
				}
			}
			cout << "keep on doing? (Y/N)" << endl;
			cin >> keepon;
			if (keepon == 'N' || keepon == 'n') {
				break;
			}else{
				keepon = 'N';
				text.clear();
			}
		}else{
			output.copyTo(scrn);
		}
	}

	return output;
}
*/
Mat determineFontImg ()
{
	int fontFace = FONT_HERSHEY_SIMPLEX;
	int thickness = 60;
	Mat scrn1(1000,1000,CV_8UC3,Scalar(0,0,0));
	Mat scrn2(1000,1000,CV_8UC3,Scalar(0,0,0));
	Mat output(1000,1000,CV_8UC3,Scalar(0,0,0));
	back1 = scrn1;
	back2 = scrn2;
	Mat strImg;
	namedWindow( "gg", WINDOW_AUTOSIZE );
	imshow("gg",back1);
	setMouseCallback( "gg", onMouse, 0);


	int x1, x2, y1, y2;
	char keepon = 'N', correct = 'N', take = 'N', ans;
	char gg[100];
	string text;	
	float r, g, b;
	int R, G, B;
	vector<Point2i> pos;
	vector<Mat> imgs;

	cout << "where do you want to put string?" << endl;
	while (keepon == 'N' || keepon == 'n') {
		correct = 'N';
		cout << "plz give me the Top-Left & Right-Bottom coordinate" << endl;
		cout << "Top-Left : \n";
		while (take == 'N') {
			ans = waitKey(0);
			if (ans == 'y') {
				take = 'Y';
				x1 = click.x;
				y1 = click.y;
				printf("---take (%d, %d) as Top-Left\n", x1, y1);
				back2.copyTo(back1);
				circle(back1, click, 8, Scalar(0,255,0), 2, 8, 0);
				imshow("gg",back1);
				back1.copyTo(back2);
			}
		}
		take = 'N';
		cout << "Right-Bottom : \n";
		while (take == 'N') {
			ans = waitKey(0);
			if (ans == 'y') {
				take = 'Y';
				x2 = click.x;
				y2 = click.y;
				printf("---take (%d, %d) as Right-Bottom\n", x2, y2);
			}
		}
		take = 'N';
		output.copyTo(back1);
		rectangle(back1, Point(x1,y1), Point(x2,y2), Scalar::all(255), 1, 8, 0);
		imshow( "gg", back1 );
		waitKey(50);
		cout << "you sure?(Y/N)" << endl;
		cin >> keepon;
		if (keepon == 'y' || keepon == 'Y') {
			while (correct == 'N' || correct == 'n') {
				cout << "plz give me the string~" << endl;
				while (text.empty()) {
					getline(cin,text);
				}
				cout << "is that the string you want?(Y/N)" << endl;
				cin >> correct;
				if (correct == 'Y' || correct == 'y') {
					cout << "the color, plz? (0 ~ 1) (B G R)" << endl;
					cin >> b >> g >> r;
					R = r*255; G = g*255; B = b*255;
					strImg = oneStr2oneImg (text, fontFace, thickness, Scalar(B,G,R));
					resize (strImg, strImg, Size(x2-x1, y2-y1), 0, 0, INTER_CUBIC);
					pos.push_back(Point2i(x1,y1));
					imgs.push_back(strImg);
					mergeMultiImg (output, pos, imgs);
					pos.pop_back();
					imgs.pop_back();
					output.copyTo(back1);
					output.copyTo(back2);
					imshow( "gg", back1 );
					waitKey(50);
				}else{
					text.clear();
				}
			}
			cout << "keep on doing? (Y/N)" << endl;
			cin >> keepon;
			if (keepon == 'N' || keepon == 'n') {
				break;
			}else{
				keepon = 'N';
				text.clear();
			}
		}else{
			output.copyTo(back1);
			output.copyTo(back2);
		}
	}

	return output;
}

vector<Point2i> drawQuad(const string& dir)
{
	back1 = imread(dir);
	back2 = back1.clone();
	vector<Point2i> quad;
	Point2i temp;
	char ans;
	int cnt = 0;
	string rr = "x";

	namedWindow("gg", WINDOW_AUTOSIZE);
	imshow("gg", back1);
	waitKey(100);

	setMouseCallback( "gg", onMouse, 0);

	cout << "draw the quadrilateral on COUNTER-CLOCKWISE!!!\n";
	cout << "1st point should be the LEFT-TOP one!!!\n";
	cout << "input \"y\" to take the point\n";
	imshow("gg", back1);
	
	while(1 && cnt < 5){		
		ans = waitKey(0);

		if (ans == 'y' || ans == 'Y') {
			temp = click;
			quad.push_back(temp);
			ans = 'n';
			cnt++;
			printf("---------saved No.%d point = (%d, %d)\n", cnt, quad.back().x, quad.back().y);
			back2.copyTo(back1);
			circle(back1, click, 8, Scalar(0,255,0), 2, 8, 0);
			if (cnt > 1) {
				line(back1, quad[cnt-2], quad[cnt-1], Scalar(255,255,0), 1, 8, 0);
			}
			if (cnt == 4) {
				line(back1, quad[0], quad[cnt-1], Scalar(255,255,0), 1, 8, 0);
			}

			imshow("gg", back1);
			back1.copyTo(back2);
			
		}
		
		
	}
	//back2.copyTo(back1);
	circle(back1, click, 8, Scalar(0,255,0), 2, 8, 0);
	cout << "4 points:\n";
	for (int i = 0; i < 4; i++){
		printf("(%d,%d)",quad[i].x,quad[i].y);
	}
	quad.pop_back();

	system("pause");
	return quad;
}

void onMouse(int event, int x, int y, int, void*)
{
	if( event != EVENT_LBUTTONDOWN )
        return;

	back2.copyTo(back1);
	printf("cur_point = (%d, %d)\n", x, y);
	click = Point2i(x, y);
	Size textSize = getTextSize("x", FONT_HERSHEY_SIMPLEX,1, 20, 0);
	putText(back1, "x", click + Point2i(-0.25*textSize.width,0.25*textSize.height) , FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 2, 8, false );
	imshow("gg", back1);
}