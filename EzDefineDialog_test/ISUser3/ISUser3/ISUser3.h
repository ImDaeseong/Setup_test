#pragma once

#ifdef ISUSER3_EXPORTS
#define ISUSER3_API __declspec(dllexport)
#else
#define ISUSER3_API __declspec(dllimport)
#endif

extern "C" ISUSER3_API int __stdcall ShowCheckBoxDialog(HWND hParent);
