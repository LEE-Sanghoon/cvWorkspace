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

// 실행 명령 인수의 예: -algorithm=image_channels res\color.jpg res\ouput.jpg

const string keys =
"{help h ?        |               | print this message}"
"{algorithm A     |               | }"
"{source S        | image         | input source type(image / camera / video)}"
"{@argument1      |               | input file name}"
"{@argument2      |               | output file name}"
;


Mat				_source_image;
Mat				_operand_image;
VideoCapture	_capture;


// (1) 알고리즘 함수 원형 선언
int image_channels(Mat &src, Mat &dst);
int mat_abs(Mat &, Mat &);
int min_max(Mat &, Mat &);


int main(int argc, char* argv[])
{
	// (2) 알고리즘 함수 등록, (3) 프로젝트 속성 --> 디버거 --> -algorithm="***" 변경
	register_algorithm("image_channels", image_channels);
	register_algorithm("mat_abs", mat_abs);
	register_algorithm("min_max", min_max);

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
		_capture.open(0);
		CV_Assert(_capture.isOpened());

		_operand_image = imread(argument1);
	}
	else if (source.compare(SRC_FROM_VIDEO) == 0) {
		_capture.open(argument1);
		CV_Assert(_capture.isOpened());

		_operand_image = imread(argument2);
	}
	else {
		_source_image = imread(argument1);
		CV_Assert(_source_image.data);

		_operand_image = imread(argument2);
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

			if (_capture.isOpened())
				_capture >> _source_image;
			
			imshow(MAIN_WINDOW_TITLE, _source_image);


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

					if (_operand_image.data)
						resultImage = _operand_image;

					function(_source_image, resultImage);

					if (resultImage.data)
						imshow("RESULT IMAGE", resultImage);
				}
			}

			if (bSave) {
				
				if (_source_image.data)
					imwrite("source.jpg", _source_image);

				if (resultImage.data)
					imwrite("result.jpg", resultImage);

				bSave = false;
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