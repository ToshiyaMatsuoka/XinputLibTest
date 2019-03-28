/**
* @file
* @author Toshiya Matsuoka
*/

#include "XinputDevice.h"

using namespace Xinput;


XinputDevice::XinputDevice(PLAYER_NUM number,int leftThumbDeadzone,int rightThumbDeadzone,int leftTriggerDeadzone,int rightTriggerDeadzone)
	:CONTROLER_NUM(number)
{ 
	SetLeftThumbDeadzone(leftThumbDeadzone);

	SetRightThumbDeadzone(rightThumbDeadzone);

	SetLeftTriggerDeadzone(leftTriggerDeadzone);

	SetRightTriggerDeadzone(rightTriggerDeadzone);
}

XinputDevice::~XinputDevice()
{
	RunVibration();
}

void XinputDevice::GetControl()
{
	XINPUT_INFO = XInputGetState(CONTROLER_NUM, &m_Xinput);
}

void XinputDevice::SetLeftThumbDeadzone(unsigned int leftThumbDeadzone)
{
	if (leftThumbDeadzone > MAX_THUMB_VALUE) leftThumbDeadzone = MAX_THUMB_VALUE;
	m_LeftThumbDeadzone = leftThumbDeadzone;
}
void XinputDevice::SetRightThumbDeadzone(unsigned int rightThumbDeadzone)
{
	if (rightThumbDeadzone > MAX_THUMB_VALUE) rightThumbDeadzone = MAX_THUMB_VALUE;
	m_RightThumbDeadzone = rightThumbDeadzone;
}
void XinputDevice::SetLeftTriggerDeadzone(unsigned int leftTriggerDeadzone)
{
	if (leftTriggerDeadzone > MAX_TRIGGER_VALUE) leftTriggerDeadzone = MAX_TRIGGER_VALUE;
	m_LeftTriggerDeadzone = leftTriggerDeadzone;
}
void XinputDevice::SetRightTriggerDeadzone(unsigned int rightTriggerDeadzone)
{
	if (rightTriggerDeadzone > MAX_TRIGGER_VALUE) rightTriggerDeadzone = MAX_TRIGGER_VALUE;
	m_RightTriggerDeadzone = rightTriggerDeadzone;
}

PADSTATE XinputDevice::GetButton(ButtonIndex index)const
{
	return m_PadState[index];
}
bool XinputDevice::PressedAnyButton()const
{
	bool isPressed = false;
	for (int i = 0; i < ButtomIndexMAX; ++i) {
		isPressed = GetButton(static_cast<ButtonIndex>(i));
		if (isPressed)
			return true;
	}
	return false;
}
void XinputDevice::ButtonCheck() {

	CheckButtonState(XINPUT_GAMEPAD_A, ButtonA);
	CheckButtonState(XINPUT_GAMEPAD_B, ButtonB);
	CheckButtonState(XINPUT_GAMEPAD_X, ButtonX);
	CheckButtonState(XINPUT_GAMEPAD_Y, ButtonY);
	CheckButtonState(XINPUT_GAMEPAD_START, ButtonStart);
	CheckButtonState(XINPUT_GAMEPAD_BACK, ButtonBack);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_SHOULDER, ButtonLB);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_SHOULDER, ButtonRB);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_UP, ButtonUP);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_DOWN, ButtonDOWN);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_LEFT, ButtonLEFT);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, ButtonRIGHT);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_THUMB, ButtonLeftThumb);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_THUMB, ButtonRightThumb);

	LeftThumbStateDivide(THUMB_UP);
	RightThumbStateDivide(THUMB_UP);
	LeftThumbStateDivide(THUMB_DOWN);
	RightThumbStateDivide(THUMB_DOWN);
	LeftThumbStateDivide(THUMB_LEFT);
	RightThumbStateDivide(THUMB_LEFT);
	LeftThumbStateDivide(THUMB_RIGHT);
	RightThumbStateDivide(THUMB_RIGHT);

	TriggerRStateDivide();
	TriggerLStateDivide();
}

void XinputDevice::DeviceUpdate() {

	GetControl();
	ButtonCheck();
}

void XinputDevice::CheckButtonState(WORD buttomID, ButtonIndex buttomIndex)
{
	if (m_Xinput.Gamepad.wButtons & buttomID)
	{
		if (m_PadOldState[buttomIndex] == PadOn)
		{
			m_PadState[buttomIndex] = PadOn;
		}
		else
		{
			m_PadState[buttomIndex] = PadPush;
		}

		m_PadOldState[buttomIndex] = PadOn;
	}
	else
	{
		if (m_PadOldState[buttomIndex] == PadOn)
		{
			m_PadState[buttomIndex] = PadRelease;
		}
		else
		{
			m_PadState[buttomIndex] = PadOff;
		}
		m_PadOldState[buttomIndex] = PadOff;
	}
}

int XinputDevice::GetTriggerValue(Trigger trigger)const
{
	switch (trigger)
	{
	case LEFT_TRIGGER:
		if (m_Xinput.Gamepad.bLeftTrigger < m_LeftTriggerDeadzone &&
			m_Xinput.Gamepad.bLeftTrigger > -m_LeftTriggerDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.bLeftTrigger;
	case RIGHT_TRIGGER:
		if (m_Xinput.Gamepad.bRightTrigger < m_RightTriggerDeadzone &&
			m_Xinput.Gamepad.bRightTrigger > -m_RightTriggerDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.bRightTrigger;
	}
	return 0;
}

bool XinputDevice::TiltedLeftThumb(ThumbTilt thumbTilt)const
{
	switch (thumbTilt)
	{
	case THUMB_UP:
		if (GetLeftThumbValue(THUMB_Y) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case THUMB_DOWN:
		if (GetLeftThumbValue(THUMB_Y) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case THUMB_RIGHT:
		if (GetLeftThumbValue(THUMB_X) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case THUMB_LEFT:
		if (GetLeftThumbValue(THUMB_X) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

bool XinputDevice::TiltedRightThumb(ThumbTilt thumbTilt)const
{
	switch (thumbTilt)
	{
	case THUMB_UP:
		if (GetRightThumbValue(THUMB_Y) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case THUMB_DOWN:
		if (GetRightThumbValue(THUMB_Y) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case THUMB_RIGHT:
		if (GetRightThumbValue(THUMB_X) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case THUMB_LEFT:
		if (GetRightThumbValue(THUMB_X) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

int XinputDevice::GetLeftThumbValue(ThumbTiltAxis thumbTilt)const
{
	switch (thumbTilt)
	{
	case THUMB_Y:
		if (m_Xinput.Gamepad.sThumbLY < m_LeftThumbDeadzone &&
			m_Xinput.Gamepad.sThumbLY > -m_LeftThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbLY;
		break;
	case THUMB_X:
		if (m_Xinput.Gamepad.sThumbLX < m_LeftThumbDeadzone &&
			m_Xinput.Gamepad.sThumbLX > -m_LeftThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbLX;
		break;
	default:
		return 0;
	}
}

int XinputDevice::GetRightThumbValue(ThumbTiltAxis thumbTilt)const
{
	switch (thumbTilt)
	{
	case THUMB_Y:
		if (m_Xinput.Gamepad.sThumbRY < m_RightThumbDeadzone &&
			m_Xinput.Gamepad.sThumbRY > -m_RightThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbRY;
		break;
	case THUMB_X:
		if (m_Xinput.Gamepad.sThumbRX < m_RightThumbDeadzone &&
			m_Xinput.Gamepad.sThumbRX > -m_RightThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbRX;
		break;
	default:
		return 0;
	}
}

PADSTATE XinputDevice::GetLeftThumbState(ThumbTilt thumbTilt)const
{
	return m_LeftThumbState[thumbTilt];
}

PADSTATE XinputDevice::GetRightThumbState(ThumbTilt thumbTilt)const
{
	return m_RightThumbState[thumbTilt];
}

PADSTATE XinputDevice::GetRightTriggerState()const
{
	return m_RightTriggerState;
}

PADSTATE XinputDevice::GetLeftTriggerState()const
{
	return m_LeftTriggerState;
}

void XinputDevice::RightThumbStateDivide(ThumbTilt thumbTilt) {
	if (TiltedRightThumb(thumbTilt))
	{
		if (m_RightThumbOldState[thumbTilt] == PadOn)
		{
			m_RightThumbState[thumbTilt] = PadOn;
		}
		else
		{
			m_RightThumbState[thumbTilt] = PadPush;
		}
		m_RightThumbOldState[thumbTilt] = PadOn;
	}
	else
	{
		if (m_RightThumbOldState[thumbTilt] == PadOn)
		{
			m_RightThumbState[thumbTilt] = PadRelease;
		}
		else
		{
			m_RightThumbState[thumbTilt] = PadOff;
		}
		m_RightThumbOldState[thumbTilt] = PadOff;
	}
}

void XinputDevice::LeftThumbStateDivide(ThumbTilt thumbTilt) {
	if (TiltedLeftThumb(thumbTilt))
	{
		if (m_LeftThumbOldState[thumbTilt] == PadOn)
		{
			m_LeftThumbState[thumbTilt] = PadOn;
		}
		else
		{
			m_LeftThumbState[thumbTilt] = PadPush;
		}
		m_LeftThumbOldState[thumbTilt] = PadOn;
	}
	else
	{
		if (m_LeftThumbOldState[thumbTilt] == PadOn)
		{
			m_LeftThumbState[thumbTilt] = PadRelease;
		}
		else
		{
			m_LeftThumbState[thumbTilt] = PadOff;
		}
		m_LeftThumbOldState[thumbTilt] = PadOff;
	}
}

void XinputDevice::TriggerRStateDivide() {
	if (GetTriggerValue(RIGHT_TRIGGER))
	{
		if (m_RightTriggerOldState == PadOn)
		{
			m_RightTriggerState = PadOn;
		}
		else
		{
			m_RightTriggerState = PadPush;
		}
		m_RightTriggerOldState = PadOn;
	}
	else
	{
		if (m_RightTriggerOldState == PadOn)
		{
			m_RightTriggerState = PadRelease;
		}
		else
		{
			m_RightTriggerState = PadOff;
		}
		m_RightTriggerOldState = PadOff;
	}
}

void XinputDevice::TriggerLStateDivide() {
	if (GetTriggerValue(LEFT_TRIGGER))
	{
		if (m_LeftTriggerOldState == PadOn)
		{
			m_LeftTriggerState = PadOn;
		}
		else
		{
			m_LeftTriggerState = PadPush;
		}
		m_LeftTriggerOldState = PadOn;
	}
	else
	{
		if (m_LeftTriggerOldState == PadOn)
		{
			m_LeftTriggerState = PadRelease;
		}
		else
		{
			m_LeftTriggerState = PadOff;
		}
		m_LeftTriggerOldState = PadOff;
	}
}

void XinputDevice::RunVibration(unsigned int leftValue, unsigned int rightValue) {
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	if (leftValue > MAX_VIBRATION_VALUE) leftValue = MAX_VIBRATION_VALUE;
	if (rightValue > MAX_VIBRATION_VALUE) rightValue = MAX_VIBRATION_VALUE;

	vibration.wLeftMotorSpeed = leftValue;
	vibration.wRightMotorSpeed = rightValue;
	XInputSetState(CONTROLER_NUM, &vibration);
}

