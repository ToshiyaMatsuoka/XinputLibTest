#include "TestScene.h"

#define BLOCK_INTEGRATION_WIDTH 80.2f / 512.0f
#define BLOCK_INTEGRATION_HEIGHT 81.0f / 1024.0f

void RevolveZ(CUSTOMVERTEX* vertex, float rad, CENTRAL_STATE central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {

	float vertexX[4];
	float vertexY[4];

	vertexX[0] = central.x - central.scaleX;
	vertexX[1] = central.x + central.scaleX;
	vertexX[2] = central.x + central.scaleX;
	vertexX[3] = central.x - central.scaleX;

	vertexY[0] = central.y - central.scaleY;
	vertexY[1] = central.y - central.scaleY;
	vertexY[2] = central.y + central.scaleY;
	vertexY[3] = central.y + central.scaleY;

	for (int i = 0; i < 4; i++) {

		vertexX[i] -= central.x;
		vertexY[i] -= central.y;

		float buf = vertexX[i];

		vertexX[i] = (vertexX[i] * cos(-rad)) - (vertexY[i] * sin(-rad));
		vertexY[i] = (vertexY[i] * cos(-rad)) + (buf * sin(-rad));

		vertexX[i] += central.x;
		vertexY[i] += central.y;

	}

	vertex[0] = { vertexX[0], vertexY[0], 1.f, 1.f, color, tu, tv };
	vertex[1] = { vertexX[1], vertexY[1], 1.f, 1.f, color, tu + scaleTu, tv };
	vertex[2] = { vertexX[2], vertexY[2], 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	vertex[3] = { vertexX[3], vertexY[3], 1.f, 1.f, color, tu, tv + scaleTv };

}

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
	delete m_pXinputManager;
}

void TestScene::Initialize(DirectX* pDirectX)
{
	m_pDirectX = pDirectX;
	m_pXinputManager = new XinputManager(10000, 10000, 10000, 10000);
	m_pDirectX->LoadTexture(L"Resource/Texture/object_a.png", "BLOCK_INTEGRATION_A_TEX");
	m_pDirectX->SetFont(50, 50, "test", L"AmeChanPopMaruTTFLight-Regular.ttf",128);
}

void TestScene::Update()
{
	m_pXinputManager->DeviceUpdate();
	if (Xinput::PadOn == m_pXinputManager->GetLeftThumbState(Xinput::THUMB_RIGHT))
	{
		m_Central.x+=20;
	}
	if (Xinput::PadOn == m_pXinputManager->GetLeftThumbState(Xinput::THUMB_LEFT))
	{
		m_Central.x-=20;
	}
	if (Xinput::PadOn == m_pXinputManager->GetLeftThumbState(Xinput::THUMB_DOWN))
	{
		m_Central.y+= 20;
	}
	if (Xinput::PadOn == m_pXinputManager->GetLeftThumbState(Xinput::THUMB_UP))
	{
		m_Central.y-= 20;
	}
	if (Xinput::PadOn == m_pXinputManager->GetButton(Xinput::ButtonA/*,Xinput::PLAYER_03*/))
	{
		m_Central.y += 20;
	}
	if (m_pXinputManager->PressedAnyButton()) {
		m_Central.x = 500;
		m_Central.y = 500;
	}

	if(m_pXinputManager->GetInfo(Xinput::PLAYER_01)) {
		m_Central.x = 200;
		m_Central.y = 200;
	}
	if (m_Central.x > 600 && m_Central.y < 300)
	{
		m_pXinputManager->RunVibration(600000, 60000);
	}
	else m_pXinputManager->RunVibration(0, 0);

	if (m_pXinputManager->GetTriggerValue(Xinput::LEFT_TRIGGER)) m_Central.x = 200;
	if (m_pXinputManager->GetTriggerValue(Xinput::RIGHT_TRIGGER)) m_Central.x = 600;

}

void TestScene::Render()
{
	const DWORD DEFFALT_COLOR = 0xFFFFFFFF;

	RECT testName = { 0, 100, 1250, 720 };
	const WCHAR* TestName = L"ABC‚ ‚¢‚¤‚¦‚¨‰Æ";
	//m_pDirectX->DrawWord(testName, TestName, "test", DT_RIGHT, 0xffffffff);

	CUSTOMVERTEX ShurikenVertex[4];
	static float rad = 0.f;
	rad += 10.f;
	RevolveZ(ShurikenVertex, static_cast<float>(rad), m_Central, DEFFALT_COLOR, 0.f, BLOCK_INTEGRATION_HEIGHT * 2.965f, BLOCK_INTEGRATION_WIDTH, BLOCK_INTEGRATION_HEIGHT);
	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", ShurikenVertex);

}
