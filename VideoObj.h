#pragma once
#include "OpenGL.h"

#include <vector>
#include <string>
using namespace std;
class VideoObj {
public:
	VideoObj();//构造函数
	void Draw();//绘制函数
	int framesNum = 0; //视频帧总共的数量
	unsigned int currTexture = 0; // 当前视频帧的纹理id
	vector<unsigned int> textureIDs; //纹理的id容器

private:
	bool ifInitTexture = false;
	int w, h; // 视频宽高
	unsigned int GenTextures(string path);
	void initTexture();
};

