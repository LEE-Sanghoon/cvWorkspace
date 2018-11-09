#pragma once
#include <opencv2/opencv.hpp>

#ifdef _MSC_VER

	#define OPENCV_LIB_PREFIX	"opencv_"

//------------------------------------------------------------------
	#ifdef _DEBUG
		#define OPENCV_LIB_POSTFIX	"d.lib"
	#else
		#define OPENCV_LIB_POSTFIX	".lib"
	#endif

	#define STR_EXPAND(tok)	#tok
	#define STR(tok)		STR_EXPAND(tok)

	#define OPENCV_VERSION_STRING	STR(CV_MAJOR_VERSION) STR(CV_MINOR_VERSION) STR(CV_SUBMINOR_VERSION)
	#define OPENCV_LIB_EXPAND(x)	OPENCV_LIB_PREFIX x OPENCV_VERSION_STRING OPENCV_LIB_POSTFIX
//------------------------------------------------------------------

	#define LIB_WORLD	OPENCV_LIB_EXPAND("world")

//------------------------------------------------------------------
	#pragma comment(lib, LIB_WORLD)
//------------------------------------------------------------------
#endif
