#pragma once

#include <string>

//****************************/
//-- class Util
//****************************/
class Util
{
public:
	// 获取exe所在目录 注：尾部带有"\\"
	static std::string  GetAppDirA();
	static std::wstring GetAppDirW();
};