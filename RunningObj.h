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

class RunningObj {

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

};