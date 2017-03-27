#ifndef _ENTROPYSEQ_H_
#define _ENTROPYSEQ_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "rtcprgb2gray.h"
using namespace cv;
using namespace std;

class entropySeq
{
public:
	Mat EntropySeg(Mat src);
};
#endif