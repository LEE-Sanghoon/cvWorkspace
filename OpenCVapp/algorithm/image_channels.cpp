#include <opencv2/opencv.hpp>
using namespace cv;

int image_channels(Mat &src, Mat &dst) {

	Mat bgr[3];
	split(src, bgr);

	imshow("blue channel", bgr[0]);
	imshow("green channel", bgr[1]);
	imshow("red channel", bgr[2]);

	return 0;
}