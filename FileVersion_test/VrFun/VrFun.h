#pragma once

extern "C" _declspec(dllexport) char* GetFileVersion(char* pFilePath);
extern "C" _declspec(dllexport) char* GetNowTime();
extern "C" _declspec(dllexport) char* GetUrlInfo(char* Url);