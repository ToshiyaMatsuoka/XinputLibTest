/**
* @file
* @author Toshiya Matsuoka
*/
#include "XinputManager.h"

using namespace Xinput;


XinputManager::XinputManager(unsigned int leftThumbDeadzone, unsigned int rightThumbDeadzone, unsigned int leftTriggerDeadzone, unsigned int rightTriggerDeadzone)
{
	m_pXinputDevices[PLAYER_01] = new XinputDevice(PLAYER_01,leftThumbDeadzone,rightThumbDeadzone,leftTriggerDeadzone,rightTriggerDeadzone);
	m_pXinputDevices[PLAYER_02] = new XinputDevice(PLAYER_02,leftThumbDeadzone,rightThumbDeadzone,leftTriggerDeadzone,rightTriggerDeadzone);
	m_pXinputDevices[PLAYER_03] = new XinputDevice(PLAYER_03,leftThumbDeadzone,rightThumbDeadzone,leftTriggerDeadzone,rightTriggerDeadzone);
	m_pXinputDevices[PLAYER_04] = new XinputDevice(PLAYER_04,leftThumbDeadzone,rightThumbDeadzone,leftTriggerDeadzone,rightTriggerDeadzone);
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

int XinputManager::GetTriggerValue(Trigger trigger, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetTriggerValue(trigger);
}

bool XinputManager::TiltedLeftThumb(ThumbTilt thumbTilt, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->TiltedLeftThumb(thumbTilt);
}

bool XinputManager::TiltedRightThumb(ThumbTilt thumbTilt, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->TiltedRightThumb(thumbTilt);
}

int XinputManager::GetLeftThumbValue(ThumbTiltAxis thumbTilt, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetLeftThumbValue(thumbTilt);
}

int XinputManager::GetRightThumbValue(ThumbTiltAxis thumbTilt, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return 0;
	return m_pXinputDevices[num]->GetRightThumbValue(thumbTilt);
}

PADSTATE XinputManager::GetLeftThumbState(ThumbTilt thumbTilt, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetLeftThumbState(thumbTilt);
}

PADSTATE XinputManager::GetRightThumbState(ThumbTilt thumbTilt, PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetRightThumbState(thumbTilt);
}

PADSTATE XinputManager::GetRightTriggerState(PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetRightTriggerState();
}

PADSTATE XinputManager::GetLeftTriggerState(PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevices[num]->GetInfo()) return PadOff;
	return m_pXinputDevices[num]->GetLeftTriggerState();
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

int XinputManager::GetTriggerValue(Trigger trigger)
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

bool XinputManager::TiltedLeftThumb(ThumbTilt thumbTilt)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		bool isTilted = false;
		isTilted = XinputDevice->TiltedLeftThumb(thumbTilt);
		if (isTilted == 0) continue;
		return isTilted;
	}
	return false;
}

bool XinputManager::TiltedRightThumb(ThumbTilt thumbTilt)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		bool isTilted = false;
		isTilted = XinputDevice->TiltedRightThumb(thumbTilt);
		if (isTilted == 0) continue;
		return isTilted;
	}
	return false;
}

int XinputManager::GetLeftThumbValue(ThumbTiltAxis thumbTilt)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		int AnalogValue;
		AnalogValue= XinputDevice->GetLeftThumbValue(thumbTilt);
		if (AnalogValue == 0) continue;
		return AnalogValue;
	}
	return 0;
}

int XinputManager::GetRightThumbValue(ThumbTiltAxis thumbTilt)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		int AnalogValue;
		AnalogValue = XinputDevice->GetRightThumbValue(thumbTilt);
		if (AnalogValue == 0) continue;
		return AnalogValue;
	}
	return 0;
}

PADSTATE XinputManager::GetLeftThumbState(ThumbTilt thumbTilt)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetLeftThumbState(thumbTilt);
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

PADSTATE XinputManager::GetRightThumbState(ThumbTilt thumbTilt)
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetRightThumbState(thumbTilt);
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

PADSTATE XinputManager::GetRightTriggerState()
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetRightTriggerState();
		if (padState == PadOff) continue;
		return padState;
	}
	return PadOff;
}

PADSTATE XinputManager::GetLeftTriggerState()
{
	for (auto& XinputDevice : m_pXinputDevices) {
		if (ERROR_SUCCESS != XinputDevice->GetInfo()) continue;
		PADSTATE padState = PadOff;
		padState = XinputDevice->GetRightTriggerState();
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

