#include "RunningObj.h"
#include "stb_image.h"

RunningObj::RunningObj() {
	mbInitialised = false;
}

int angle = 0;
void RunningObj::DrawStuff(Vector<3> v3CameraPos) {
	if (!mbInitialised)
		Init();

	angle = (angle + 3) % 360;
	GLfloat r = 1;
	GLfloat x_move = r * sin(angle*3.1415926 / 180), y_move = r * cos(angle*3.1415926 / 180);
	glTranslatef(x_move, 0, y_move);
	glRotatef(angle, 0, -1, 0);
	glRotatef(angle, 1, 0, 0);

	glCallList(mnCubeDisplayList);

}

void RunningObj::Reset() {

}

void RunningObj::Init() {
	if (mbInitialised) return;
	mbInitialised = true;

	mnCubeDisplayList = glGenLists(1);
	glNewList(mnCubeDisplayList, GL_COMPILE);
	DrawCube();
	glEndList();
}



void RunningObj::DrawCube() {


	unsigned int texture = GenTextures("images/1.png");
	if (texture == -1) {
		std::cout << "Error : load texture failed!" << std::endl;
		system("pause");
		exit(-1);
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texture);
	std::cout << "load over......111......................" << std::endl;

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); //1
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);

	//glColor3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5); //2
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);

	//glColor3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5); //3
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);

	//glColor3f(0.3, 0.4, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); //4
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);

	//glColor3f(0.5, 0.4, 0.3);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); //5
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);

	//glColor3f(0.2, 0.7, 0.4);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.5); //6
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);

	glEnd();
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