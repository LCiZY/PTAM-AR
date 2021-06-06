#include "VideoSource.h"
#include "videoInput.h" // External lib
#include <gvars3/instances.h>
#include <cvd/utility.h>
#include <vector> 
#include <string> 
#include <fstream> 
#include <iostream>
#define WIN32_MEAN_AND_LEAN
#include <windows.h>


using namespace std;
using namespace CVD;
using namespace GVars3;


struct VideoInputInfo
{
	videoInput *pVideoInput;
	int nDevice;
};


int get_device_number(string config_path) {
	ifstream myfile(config_path);
	string line;
	if (!myfile.is_open())
	{
		std::cout << "读取相机编号文件失败" << std::endl;
	}
	while (getline(myfile, line))
	{
		if (line.length() > 0) {
			if (line[0] == '#') {
				continue;
			}
			int result = 0, factor = 1;
			for (int i = line.length() - 1; i >= 0 ; i--)
			{
				if (line[i] < 48 || line[i] > 57) {
					std::cout << "无效字符:"<< line[i] << std::endl;
					return 0;
				}
				result += (line[i] - 48) * factor;
				factor *= 10;
			}
			myfile.close();
			return result;
		}
		
	}
	myfile.close();
	return 0;
}

VideoSource::VideoSource()
{
	VideoInputInfo *pInfo = new VideoInputInfo;
	mptr = (void*) pInfo;

	pInfo->pVideoInput = new videoInput;
	pInfo->nDevice = GV3::get<int>("VideoInput.DeviceNumber", get_device_number("VideoInput.DeviceNumber.conf"), HIDDEN);
	int nIdealFrameRate = GV3::get<int>("VideoInput.IdealFrameRate", 30, HIDDEN);
	ImageRef irIdealSize = GV3::get<ImageRef>("VideoInput.IdealSize", ImageRef(640,480), HIDDEN);


	pInfo->pVideoInput->setIdealFramerate(pInfo->nDevice, nIdealFrameRate);
	pInfo->pVideoInput->setupDevice(pInfo->nDevice, irIdealSize.x, irIdealSize.y);


	mirSize.x = pInfo->pVideoInput->getWidth(pInfo->nDevice);
	mirSize.y = pInfo->pVideoInput->getHeight(pInfo->nDevice);
};


void VideoSource::GetAndFillFrameBWandRGB(Image<CVD::byte> &imBW, Image<CVD::Rgb<CVD::byte> > &imRGB)
{
	imRGB.resize(mirSize);
	imBW.resize(mirSize);


	VideoInputInfo *pInfo = (VideoInputInfo*) mptr;
	while(!pInfo->pVideoInput->isFrameNew(pInfo->nDevice))
	Sleep(1);


	pInfo->pVideoInput->getPixels(pInfo->nDevice, (CVD::byte*) imRGB.data(), true, true);
	copy(imRGB, imBW);
}


ImageRef VideoSource::Size()
{
return mirSize;
}