#pragma once
#include <string>

class MiscUtility {

	// string→wstring文字変換入力
	std::wstring ConvertString(const std::string& str);

	// wstring→string文字変換入力
	std::string ConvertString(const std::wstring& str);
};
