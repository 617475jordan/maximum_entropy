#ifndef _REGIONGROWING_H_
#define _REGIONGROWING_H_
#include<opencv2\opencv.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;

class regionGrowing
{
public:
	Mat RegionGrow(Mat MatIn, int iGrowPoint, int iGrowJudge);//iGrowPointΪ���ӵ���ж�������iGrowJudgeΪ��������  

};
#endif