#include "utils.h"
#include<string>


//计算文件夹的个数
int utils::getFilesCount(string path)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	int result = 0;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
				if ((fileinfo.attrib &  _A_SUBDIR)) {
				}
				else {
					result++;
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return result;
}

/*得到文件夹内的文件名*/
void utils::getFiles(std::string path, std::vector<std::string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				files.push_back(fileinfo.name);
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

/*得到文件夹内的文件名*/
void utils::getFilesPath(std::string path, std::vector<std::string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
				std::string path = p.substr(0,p.size()-1) + string(fileinfo.name);
				files.push_back(path);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


/*
删除文件夹里面的文件
*/
void utils::removeFileInDir(std::string path) {
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				remove(fileinfo.name);
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

