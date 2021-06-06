// -*- c++ -*-
// Copyright 2008 Isis Innovation Limited
//
// EyeGame.h
// Declares the EyeGame class
// EyeGame is a trivial AR app which draws some 3D graphics
// Draws a bunch of 3d eyeballs remniscient of the
// AVL logo
//
#ifndef __VideoGame_H
#define __VideoGame_H

#include <cmath>
#include <TooN/TooN.h>
#include "OpenGL.h"
#include "VideoObj.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace TooN;

class VideoGame
{
public:
	VideoGame();
	void DrawStuff(Vector<3> v3CameraPos);
	void Reset();
	void Init();

protected:
	bool mbInitialised;

	VideoObj *video;

};

#endif