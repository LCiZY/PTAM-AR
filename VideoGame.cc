// Copyright 2008 Isis Innovation Limited
#include "VideoGame.h"
#include <stdio.h>
#include<stdlib.h>
#include <direct.h>
#include <cvd/convolution.h>

using namespace CVD;
using namespace std;

VideoGame::VideoGame()
{
	mbInitialised = false;
}

void VideoGame::Reset()
{
}


clock_t st = 0;
clock_t ed = 0;
int count1 = 1;
void VideoGame::DrawStuff(Vector<3> v3CameraPos)
{
	if (!mbInitialised)
		Init();
	video->Draw();
	if (1) {//如果到时间了就下一帧
		if (count1 == video->framesNum) count1 = 1;
		video->currTexture = video->textureIDs.at(count1++ % video->framesNum);
	}
	clock_t temp = clock();
	cout << "time for frame:" << temp - st << "\n";
	st = temp;

};


void VideoGame::Init()
{
	if (mbInitialised) return;
	mbInitialised = true;
	video = new VideoObj();


}



