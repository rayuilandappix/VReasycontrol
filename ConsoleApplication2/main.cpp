#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include<math.h>
using namespace cv;
using namespace std;
int thresh = 30;
int max_thresh = 255;

int bSums(Mat src)
{

	int counter = 0;
	//迭代器访问像素点  
	Mat_<uchar>::iterator it = src.begin<uchar>();
	Mat_<uchar>::iterator itend = src.end<uchar>();
	int i = 0;
	for (; it != itend; ++it)
	{
		i++;
		if ((*it)>0) {
			counter += 1;//二值化后，像素点是0或者255
		//printf("%d\n", it);
		}  
		if (counter == 2000) break;
	
	}
	
	return i;
}

int main()
{
	char c;
	VideoCapture inputVideo(0);    
	Mat src;
	Mat oneclo[3];
	int oldnum = 0;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	cvNamedWindow("output", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("biaoji", CV_WINDOW_AUTOSIZE);
	for (;;)
	{
		inputVideo >> src;
		cvtColor(src, src, CV_BGR2GRAY);
		medianBlur(src,src,3);
		//cvFlip(src,src, 1);
		GaussianBlur(src, src, Size(7, 7), 4.5,3);
		threshold(src, src, 246, 255, THRESH_BINARY);
		//Canny(src, src, thresh, thresh * 3, 3);
		int num=bSums(src);


		//findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		int numx = num / 640;
		int numy = num % 640;
		int oldx = oldnum / 640;
		int oldy = oldnum % 640;
		int cha = sqrt(abs(oldx - numx) ^ 2 + abs(oldy - numy) ^ 2);
		if(oldx>0){
			if ((50 > cha > 15)) {
			numx = oldx;
			numy = oldy;
			printf("%d\n", cha);
			}
		}
	    
		Point center = Point(numy, numx);
		int r = 25;
		Mat picture(480, 640, CV_8UC3, Scalar(255, 255, 255));
		circle(picture, center, r, Scalar(0, 0, 0));
		imshow("output", src);
		imshow("biaoji", picture);
		
		

		c = waitKey(10);
		if (c == 27) break;
	}
	return 0;
}

