#include "RunningObj.h"
#include "stb_image.h"
#include <direct.h>
#include <stdio.h>
#include "utils.h"



RunningObj::RunningObj() {
	mbInitialised = false;
	srand(time(0));
	char* buf = new char[1024];
	getcwd(buf, 1024);
	string picsDir = string(buf) + "\\pics";
	utils::getFilesPath(picsDir, texs);
	texIDs = new unsigned int[texs.size()];
	delete buf;
	if (texs.size() == 0) {
		std::cout << "error: pic num is 0!!!!!";
		system("pause");
		exit(-1);
	}
	for (int i = 0; i < 6; i++){
		facesInfo.push_back(new FaceInfo);
	}
	initTextures();
}

int angle = 0;
void RunningObj::DrawStuff(Vector<3> v3CameraPos) {
	if (!mbInitialised) {
		Init();

	}

	angle = (angle + 3) % 360;
	GLfloat r = 1;
	GLfloat x_move = r * sin(angle*3.1415926 / 180), y_move = r * cos(angle*3.1415926 / 180);
	//glTranslatef(x_move, 0, y_move);
	glRotatef(angle, 0, -1, 0);
	glRotatef(angle, 1, 0, 0);

	//glCallList(mnCubeDisplayList);
	DrawCube();


}

void RunningObj::Reset() {

}

void RunningObj::Init() {
	if (mbInitialised) return;
	mbInitialised = true;

	mnCubeDisplayList = glGenLists(1);
	glNewList(mnCubeDisplayList, GL_COMPILE);
	glEndList();
}

void drawFace(int n) {
	glBegin(GL_QUADS);
	if (n == 1) {
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); //1
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	}
	else if (n == 2) {
		glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5); //2
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	}
	else if (n == 3) {
		glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5); //3
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	}
	else if (n == 4) {
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); //4
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	}
	else if (n == 5) {
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); //5
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	}
	else if (n == 6) {
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.5); //6
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	}
	glEnd();
}

const float FADESPEED = 0.05f;
const int FADE_INTERVAL = 2000; //ms

void RunningObj::DrawCube() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Enables trancluency 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++){
			glColor4f(1.0f, 1.0f, 1.0f, j==0 ? facesInfo[i]->alpha : (1- facesInfo[i]->alpha)); // 0 < alpha < 255
			//glColor4f(1.0f, 1.0f, 1.0f, 1.f); // 0 < alpha < 255
			glBindTexture(GL_TEXTURE_2D, facesInfo[i]->texID[j]);
			drawFace(i+1);
		}
		//update faceinfo
		if (clock() - facesInfo[i]->time > FADE_INTERVAL) {
			float delta = (facesInfo[i]->up ? 1 : -1) * FADESPEED;
			facesInfo[i]->alpha += delta;
			if (facesInfo[i]->alpha >= 1.f) {
				facesInfo[i]->alpha = 1.f; facesInfo[i]->up = false;
				facesInfo[i]->time = clock();
				facesInfo[i]->texID[1] = getRandomTexID();
			}
			else if (facesInfo[i]->alpha <= 0.2f) {
				facesInfo[i]->alpha = 0.2f; facesInfo[i]->up = true;
				//facesInfo[i]->time = clock();
				facesInfo[i]->texID[0] = getRandomTexID();
			}
		}
	}
}




unsigned int RunningObj::GenTextures(string path) {
	unsigned int texture;
	int width, height, nrComponents;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glGenerateMipmapEXT(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "-----------------------Texture failed to load at path: " << path << std::endl;
		texture = -1;
	}
	stbi_image_free(data);
	return texture;
}

void RunningObj::initTextures() {
	for (int i = 0; i < texs.size(); i++){
	//	std::cout << "idx:" << i  <<"   path:"<< texs[i] << "\n";
		texIDs[i] = GenTextures(texs.at(i));
	}
	for (int i = 0; i < 6; i++){
		facesInfo[i]->texID[0] = getRandomTexID();
		facesInfo[i]->texID[1] = getRandomTexID(1);
		facesInfo[i]->time = 0;
		float r = rand() / 65535.f;
		facesInfo[i]->alpha = r >= 0.2f ? r : (r + 0.2f);
	}
}

unsigned int RunningObj::getRandomTexID(int seed) {
	return texIDs[rand() % texs.size()];
}