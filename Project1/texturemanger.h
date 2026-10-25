#pragma once
#include"all.h"
#include<vector>

//using  animationmap = vector<Texture2D>;//改变量名类似typddef
using  animationmap = unordered_map<string, vector<Texture2D>>;//哈希表（就是有查找功能的结构体，第一个是关键字第二个是要用的值）vector<Texture2D>纹理数组


class texturemanger
{
public:
	static vector<Texture2D>importFolder(const string& folder, const string& suffix = "all");
	//两参数一目录二格式（jpg;png;all）
	static  animationmap  importFolderex(const string& folder, const string& suffix = "all");

private:


};

