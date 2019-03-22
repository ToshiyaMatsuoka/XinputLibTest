/**
* @file GameManager.h
* @brief Mainループ処理,Window関連
* @author Toshiya Matsuoka
*/
#pragma once

#include "DirectX.h"
#include<iostream>
#include <fstream>
#include<sstream>
#include <algorithm>
#include "TestScene.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


void WriteLog(std::string Text);


class GameManager
{
public:
	GameManager(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow);
	~GameManager();
	int MessageLoop();
	static void ChangeDisplayMode(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
private:
	const WCHAR API_NAME[10] = L"忍者屋敷";
	static DirectX* pDirectX;
	 TestScene* m_pTestScene;
	static HWND hWnd;
	static bool isWindowMode;	//true:Window　false:Full
	static bool isDeviceLost;
	static RECT WinRect;			//Window Mode での位置大きさ
};
