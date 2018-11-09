#include <windows.h>

#include "myOpenCV.hpp"
#include "AppSub.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace cv;


#define LOOP_FREQUENCY		100

#define MAIN_WINDOW_TITLE	"OpenCV App"

#define SRC_FROM_CAMERA		"camera"
#define SRC_FROM_IMAGE		"image"
#define SRC_FROM_VIDEO		"video"


const string keys =
"{help h ?        |               | print this message}"
"{algorithm A     |               | }"
"{source S        | image         | input source type(image / camera / video)}"
"{@argument1      | lenna.jpg     | input file name}"
"{@argument2      | output.jpg    | output file name}"
;


Mat				gMainWndImage;
VideoCapture	gMainCapture;

// 알고리즘 함수 원형 선언
int image_channels(Mat &src, Mat &dst);

int main(int argc, char* argv[])
{
	register_algorithm("image_channels", image_channels);

#ifndef _DEBUG
	FreeConsole();
#endif

	CommandLineParser parser(argc, argv, keys);
	parser.about(MAIN_WINDOW_TITLE);


	if (parser.has("help") == true) {
		parser.printMessage();
		return 0;
	}


	string algorithm = parser.get<string>("algorithm");

	string argument1 = parser.get<string>("@argument1");
	string argument2 = parser.get<string>("@argument2");


	string source = parser.get<string>("source");
	if (source.compare(SRC_FROM_CAMERA) == 0) {
		gMainCapture.open(0);
		CV_Assert(gMainCapture.isOpened());
	}
	else if (source.compare(SRC_FROM_VIDEO) == 0) {
		gMainCapture.open(argument1);
		CV_Assert(gMainCapture.isOpened());
	}
	else {
		gMainWndImage = imread(argument1);
		CV_Assert(gMainWndImage.data);
	}


	try {

		Mat resultImage;

		bool bAct = algorithm.empty()? false: true;

		bool bSave = true;
		bool bLoop = true;

		while (bLoop) {

			int cmdKey = waitKey(LOOP_FREQUENCY);

			if (cmdKey == 27) // ESC
				break;

			if (gMainCapture.isOpened())
				gMainCapture >> gMainWndImage;
			
			imshow(MAIN_WINDOW_TITLE, gMainWndImage);


			switch (cmdKey) {

			case 'S':
			case 's':
				bSave = !(bSave);
				break;

			default:
				break;
			}

			if (bAct) {

				FUNCTION function = get_algorithm(algorithm);

				if (function != NULL) {
					function(gMainWndImage, resultImage);
					imshow("RESULT IMAGE", resultImage);
				}
			}

			if (bSave) {

			}
		}
	}
	catch (...) {

		return -1;
	}


	waitKey(0);
	destroyAllWindows();

	return 0;
}