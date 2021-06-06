#pragma once
#include<io.h>
#include<string>
#include<vector>
using namespace std;

class utils
{
public:
	static int getFilesCount(string path);
	static void getFiles(std::string path, std::vector<std::string>& files);
	static void removeFileInDir(std::string dir);
};

