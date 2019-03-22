#pragma once
#include "DirectX.h"
#include "XinputManager.h"

struct CENTRAL_STATE
{
	float x, y, scaleX, scaleY;
};

class TestScene
{
public:
	TestScene();
	~TestScene();

	void Initialize(DirectX* pDirectX);
	void Update();
	void Render();
private:
	DirectX* m_pDirectX;
	XinputManager* m_pXinputManager;
	CENTRAL_STATE m_Central = { 0,0,50,50 };

};

