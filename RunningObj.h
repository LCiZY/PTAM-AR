#pragma once
#include <cmath>
#include <TooN/TooN.h>
#include "OpenGL.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>


using namespace std;
using namespace TooN;

struct FaceInfo {
	bool up;
	clock_t time;
	float alpha;
	unsigned int texID[2];
};

class RunningObj {
	vector<string> texs;
	unsigned int* texIDs;
	vector<FaceInfo*> facesInfo; //面的信息列表

public:
	RunningObj();
	void DrawStuff(Vector<3> v3CameraPos);
	void Reset();
	void Init();


private:
	bool mbInitialised;
	void DrawCube();
	GLuint mnCubeDisplayList;
	unsigned int GenTextures(string path);
	void initTextures();
	unsigned int getRandomTexID(int seed=0);
};