#pragma once
#include "OpenGL.h"

#include <vector>
#include <string>
using namespace std;
class VideoObj {
public:
	VideoObj();//���캯��
	void Draw();//���ƺ���
	int framesNum = 0; //��Ƶ֡�ܹ�������
	unsigned int currTexture = 0; // ��ǰ��Ƶ֡������id
	vector<unsigned int> textureIDs; //�����id����

private:
	bool ifInitTexture = false;
	int w, h; // ��Ƶ���
	unsigned int GenTextures(string path);
	void initTexture();
};

