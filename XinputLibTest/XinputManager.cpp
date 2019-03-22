/**
* @file
* @author Toshiya Matsuoka
*/
#include "XinputManager.h"

using namespace Xinput;


XinputManager::XinputManager(unsigned int thumbLDeadzone, unsigned int thumbRDeadzone, unsigned int triggerLDeadzone, unsigned int triggerRDeadzone)
{
	m_pXinputDevices[PLAYER_01] = new XinputDevice(PLAYER_01,thumbLDeadzone,thumbRDeadzone,triggerLDeadzone,triggerRDeadzone);
	m_pXinputDevices[PLAYER_02] = new XinputDevice(PLAYER_02,thumbLDeadzone,thumbRDeadzone,triggerLDeadzone,triggerRDeadzone);
	m_pXinputDevices[PLAYER_03] = new XinputDevice(PLAYER_03,thumbLDeadzone,thumbRDeadzone,triggerLDeadzone,triggerRDeadzone);
	m_pXinputDevices[PLAYER_04] = new XinputDevice(PLAYER_04,thumbLDeadzone,thumbRDeadzone,triggerLDeadzone,triggerRDeadzone);
}


XinputManager::~XinputManager()
{
	delete m_pXinputDevices[PLAYER_01];
	delete m_pXinputDevices[PLAYER_02];
	delete m_pXinputDevices[PLAYER_03];
	delete m_pXinputDevices[PLAYER_04];
}

void XinputManager::DeviceUpdate()
{
	m_pXinputDevices[PLAYER_01]->DeviceUpdate();
	m_pXinputDevices[PLAYER_02]->DeviceUpdate();
	m_pXinputDevices[PLAYER_03]->DeviceUpdate();
	m_pXinputDevices[PLAYER_04]->DeviceUpdate();
}


////////////////////
//
// 単体確認
//
////////////////////

HRESULT XinputManager::GetInfo(PLAYER_NUM num) 
{
	return m_pXinputDevices[num]->GetInfo();
}

PADSTATE XinputManager::GetButton(ButtonIndex index, PLAYER_NUM num) const
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetButton(index);
}

bool XinputManager::PressedAnyButton(PLAYER_NUM num) {
	bool isPressed = false;

	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	for (int i = 0; i < ButtomIndexMAX; ++i) {
		isPressed = m_pXinputDevices[num]->GetButton(static_cast<ButtonIndex>(i));
		if (isPressed)return true;
	}
	return false;
}

int XinputManager::GetTriggerValue(AnalogTrigger trigger, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetTriggerValue(trigger);
}

bool XinputManager::GetThumbL(Analog analogState, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetThumbL(analogState);
}

bool XinputManager::GetThumbR(Analog analogState, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetThumbR(analogState);
}

int XinputManager::GetThumbLValue(AnalogAxis analogState, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetThumbLValue(analogState);
}

int XinputManager::GetThumbRValue(AnalogAxis analogState, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetThumbRValue(analogState);
}

PADSTATE XinputManager::GetThumbLState(Analog analogState, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetThumbLState(analogState);
}

PADSTATE XinputManager::GetThumbRState(Analog analogState, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetThumbRState(analogState);
}

PADSTATE XinputManager::GetTriggerRState(PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetTriggerRState();
}

PADSTATE XinputManager::GetTriggerLState(PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetTriggerLState();
}

void XinputManager::RunVibration(PLAYER_NUM num, unsigned int leftValue, unsigned int rightValue)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return;
	m_pXinputDevices[num]->RunVibration(leftValue, rightValue);
}



////////////////////
//
// 全体確認
// 入力はPLAYER_01優先
//
////////////////////

PADSTATE XinputManager::GetButton(ButtonIndex index) const
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState= XinputDevice->GetButton(index);
		if (PadOff == padState) continue;
		return padState;
		
	}
	return PadOff;
}

bool XinputManager::PressedAnyButton() {
	bool isPressed = false;
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		isPressed = XinputDevice->PressedAnyButton();
		if (isPressed) return true;
	}
	return false;
}

int XinputManager::GetTriggerValue(AnalogTrigger trigger)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		int AnalogValue;
		AnalogValue = XinputDevice->GetTriggerValue(trigger);
		if (AnalogValue == 0) continue;
		return AnalogValue;
	}
	return 0;
}

bool XinputManager::GetThumbL(Analog analogState)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		bool isTilted = false;
		isTilted = XinputDevice->GetThumbL(analogState);
		if (isTilted == 0) continue;
		return isTilted;
	}
	return false;
}

bool XinputManager::GetThumbR(Analog analogState)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		bool isTilted = false;
		isTilted = XinputDevice->GetThumbR(analogState);
		if (isTilted == 0) continue;
		return isTilted;
	}
	return false;
}

int XinputManager::GetThumbLValue(AnalogAxis analogState)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		int AnalogValue;
		AnalogValue= XinputDevice->GetThumbLValue(analogState);
		if (AnalogValue == 0) continue;
		return AnalogValue;
	}
	return 0;
}

int XinputManager::GetThumbRValue(AnalogAxis analogState)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		int AnalogValue;
		AnalogValue = XinputDevice->GetThumbRValue(analogState);
		if (AnalogValue == 0) continue;
		return AnalogValue;
	}
	return 0;
}

PADSTATE XinputManager::GetThumbLState(Analog analogState)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetThumbLState(analogState);
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

PADSTATE XinputManager::GetThumbRState(Analog analogState)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetThumbRState(analogState);
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

PADSTATE XinputManager::GetTriggerRState()
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetTriggerRState();
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

PADSTATE XinputManager::GetTriggerLState()
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetTriggerRState();
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

void XinputManager::RunVibration(unsigned int leftValue, unsigned int rightValue)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		XinputDevice->RunVibration(leftValue, rightValue);
	}
}

