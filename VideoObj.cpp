#include "VideoObj.h"
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "utils.h"
#include <direct.h>
#include <stdio.h>
using namespace std;

VideoObj::VideoObj()
{
	char* buf = new char[1024];
	getcwd(buf, 1024);
	vector<string> videoes;
	string videoDir = string(buf) + "\\video";
	utils::getFiles(videoDir, videoes);

	string imagesDir = string(buf) + "\\images";
	framesNum = utils::getFilesCount(imagesDir);
	//framesNum = 1;

	int chVideo = 0;
	if (videoes.size() > 1) {
		chVideo = -1;
		for (size_t i = 0; i < videoes.size(); i++)
		{
			std::cout << i << ":" << videoes.at(i) << "\n";
		}
		while (chVideo < 0 || chVideo >= videoes.size())
		{
			std::cout << "��Ƶ��������1������ѡ����Ҫ��ȡ����Ƶ,�������:\n";
			cin >> chVideo;
		}
	}

	if (framesNum == 0) {
		if (videoes.size() == 0) {
			std::cout << "֡����ƵΪ�գ�" << std::endl;
			system("pause");
			exit(-1);
		}
		string cmd = "ffmpeg -i video/" + videoes.at(chVideo) + " -vf \"fps=24,scale=iw/2:-1\" -q:v 0.1 images/%d.png";
		system(cmd.c_str());
		framesNum = utils::getFilesCount(imagesDir);
	}
	else {

		char ch;
		std::cout << imagesDir << "�ļ�������֡����" << framesNum << "���Ƿ񸲸ǲ��������ɣ�\n��y/n����";
		cin >> ch;
		while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N') {
			cin >> ch;
		}
		if (ch == 'y' || ch == 'Y') { //
			utils::removeFileInDir(imagesDir);
			string cmd = "ffmpeg -i video/" + videoes.at(chVideo) + " -vf \"fps=24,scale=iw/2:-1\" -q:v 0.1 images/%d.png";
			system(cmd.c_str());
			framesNum = utils::getFilesCount(imagesDir);
		}

	}
	std::cout << "��֡����" << framesNum << std::endl;

	//system("ffmpeg -i video/my.mp4 -vf \"fps = 24, scale = iw / 2:-1\" -ss 00:01:59 -q:v 0.1 images/%d.png");
}

void VideoObj::initTexture() {
	int progress = 0;
	for (int i = 1; i <= framesNum; i++) {
		string path = "images/" + to_string(i) + ".png";
		unsigned int temp = GenTextures(path);
		currTexture = temp;
		if (-1 != temp)
			textureIDs.push_back(temp);
		int cu_pr = (100 * i) / framesNum;
		if (progress != cu_pr) {
			progress = cu_pr;
			std::cout << "�����У�" << progress << "%...\n";
		}
	}
	std::cout << "������ɡ�\n";
}


unsigned int VideoObj::GenTextures(string path) {
	unsigned int texture;
	int width, height, nrComponents;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	this->w = width; this->h = height;
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
		std::cout << "-----------------------Texture failed to load at path: " << std::endl;
		texture = -1;
	}
	stbi_image_free(data);
	return texture;
}



void VideoObj::Draw() {
	if (!ifInitTexture) {
		ifInitTexture = true;
		initTexture();
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currTexture);
	glBegin(GL_QUADS);//��ʼ����



	GLfloat x = 1.0f, y = h / (w*1.0f);
	glTexCoord2f(0.0, 1.0);  glVertex3f(-x, -y, 0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(x, -y, 0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(x, y, 0.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-x, y, 0.5);


	glEnd();
}