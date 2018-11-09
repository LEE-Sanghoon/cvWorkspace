#pragma once
#include "myOpenCV.hpp"

#include <map>
#include <string>

using namespace std;
using namespace cv;

typedef 
int (*FUNCTION)(Mat& src, Mat& dst);


int register_algorithm(string name, FUNCTION func);
FUNCTION get_algorithm(string name);
