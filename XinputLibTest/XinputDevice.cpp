/**
* @file
* @author Toshiya Matsuoka
*/

#include "XinputDevice.h"

using namespace Xinput;


XinputDevice::XinputDevice(PLAYER_NUM number,int thumbLDeadzone,int thumbRDeadzone,int triggerLDeadzone,int triggerRDeadzone)
	:CONTROLER_NUM(number)
{ 
	SetAnalogLeftThumbDeadzone(thumbLDeadzone);

	SetAnalogRightThumbDeadzone(thumbRDeadzone);

	SetAnalogLeftTriggerDeadzone(triggerLDeadzone);

	SetAnalogRightTriggerDeadzone(triggerRDeadzone);
}

XinputDevice::~XinputDevice()
{
	RunVibration();
}

void XinputDevice::GetControl()
{
	XINPUT_INFO = XInputGetState(CONTROLER_NUM, &m_Xinput);
}

void XinputDevice::SetAnalogLeftThumbDeadzone(unsigned int thumbLDeadzone)
{
	if (thumbLDeadzone > MAX_THUMB_VALUE) thumbLDeadzone = MAX_THUMB_VALUE;
	m_AnalogLeftThumbDeadzone = thumbLDeadzone;
}
void XinputDevice::SetAnalogRightThumbDeadzone(unsigned int thumbRDeadzone)
{
	if (thumbRDeadzone > MAX_THUMB_VALUE) thumbRDeadzone = MAX_THUMB_VALUE;
	m_AnalogRightThumbDeadzone = thumbRDeadzone;
}
void XinputDevice::SetAnalogLeftTriggerDeadzone(unsigned int triggerLDeadzone)
{
	if (triggerLDeadzone > MAX_TRIGGER_VALUE) triggerLDeadzone = MAX_TRIGGER_VALUE;
	m_AnalogLeftTriggerDeadzone = triggerLDeadzone;
}
void XinputDevice::SetAnalogRightTriggerDeadzone(unsigned int triggerRDeadzone)
{
	if (triggerRDeadzone > MAX_TRIGGER_VALUE) triggerRDeadzone = MAX_TRIGGER_VALUE;
	m_AnalogRightTriggerDeadzone = triggerRDeadzone;
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
void XinputDevice::BottonCheck() {

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

	AnalogLStateDivide(ANALOGUP);
	AnalogRStateDivide(ANALOGUP);
	AnalogLStateDivide(ANALOGDOWN);
	AnalogRStateDivide(ANALOGDOWN);
	AnalogLStateDivide(ANALOGLEFT);
	AnalogRStateDivide(ANALOGLEFT);
	AnalogLStateDivide(ANALOGRIGHT);
	AnalogRStateDivide(ANALOGRIGHT);

	TriggerRStateDivide();
	TriggerLStateDivide();
}

void XinputDevice::DeviceUpdate() {

	GetControl();
	BottonCheck();
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

int XinputDevice::GetTriggerValue(AnalogTrigger trigger)const
{
	switch (trigger)
	{
	case LEFT_TRIGGER:
		if (m_Xinput.Gamepad.bLeftTrigger < m_AnalogLeftTriggerDeadzone &&
			m_Xinput.Gamepad.bLeftTrigger > -m_AnalogLeftTriggerDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.bLeftTrigger;
	case RIGHT_TRIGGER:
		if (m_Xinput.Gamepad.bRightTrigger < m_AnalogRightTriggerDeadzone &&
			m_Xinput.Gamepad.bRightTrigger > -m_AnalogRightTriggerDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.bRightTrigger;
	}
	return 0;
}

bool XinputDevice::GetThumbL(Analog analogState)const
{
	switch (analogState)
	{
	case ANALOGUP:
		if (GetThumbLValue(ANALOG_Y) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (GetThumbLValue(ANALOG_Y) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (GetThumbLValue(ANALOG_X) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (GetThumbLValue(ANALOG_X) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

bool XinputDevice::GetThumbR(Analog analogState)const
{
	switch (analogState)
	{
	case ANALOGUP:
		if (GetThumbRValue(ANALOG_Y) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (GetThumbRValue(ANALOG_Y) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (GetThumbRValue(ANALOG_X) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (GetThumbRValue(ANALOG_X) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

int XinputDevice::GetThumbLValue(AnalogAxis analogState)const
{
	switch (analogState)
	{
	case ANALOG_Y:
		if (m_Xinput.Gamepad.sThumbLY < m_AnalogLeftThumbDeadzone &&
			m_Xinput.Gamepad.sThumbLY > -m_AnalogLeftThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbLY;
		break;
	case ANALOG_X:
		if (m_Xinput.Gamepad.sThumbLX < m_AnalogLeftThumbDeadzone &&
			m_Xinput.Gamepad.sThumbLX > -m_AnalogLeftThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbLX;
		break;
	default:
		return 0;
	}
}

int XinputDevice::GetThumbRValue(AnalogAxis analogState)const
{
	switch (analogState)
	{
	case ANALOG_Y:
		if (m_Xinput.Gamepad.sThumbRY < m_AnalogRightThumbDeadzone &&
			m_Xinput.Gamepad.sThumbRY > -m_AnalogRightThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbRY;
		break;
	case ANALOG_X:
		if (m_Xinput.Gamepad.sThumbRX < m_AnalogRightThumbDeadzone &&
			m_Xinput.Gamepad.sThumbRX > -m_AnalogRightThumbDeadzone) {
			return 0;
		}
		return m_Xinput.Gamepad.sThumbRX;
		break;
	default:
		return 0;
	}
}

PADSTATE XinputDevice::GetThumbLState(Analog analogState)const
{
	return m_AnalogLState[analogState];
}

PADSTATE XinputDevice::GetThumbRState(Analog analogState)const
{
	return m_AnalogRState[analogState];
}

PADSTATE XinputDevice::GetTriggerRState()const
{
	return m_TriggerRState;
}

PADSTATE XinputDevice::GetTriggerLState()const
{
	return m_TriggerLState;
}

void XinputDevice::AnalogRStateDivide(Analog analogState) {
	if (GetThumbR(analogState))
	{
		if (m_AnalogROldState[analogState] == PadOn)
		{
			m_AnalogRState[analogState] = PadOn;
		}
		else
		{
			m_AnalogRState[analogState] = PadPush;
		}
		m_AnalogROldState[analogState] = PadOn;
	}
	else
	{
		if (m_AnalogROldState[analogState] == PadOn)
		{
			m_AnalogRState[analogState] = PadRelease;
		}
		else
		{
			m_AnalogRState[analogState] = PadOff;
		}
		m_AnalogROldState[analogState] = PadOff;
	}
}

void XinputDevice::AnalogLStateDivide(Analog analogState) {
	if (GetThumbL(analogState))
	{
		if (m_AnalogLOldState[analogState] == PadOn)
		{
			m_AnalogLState[analogState] = PadOn;
		}
		else
		{
			m_AnalogLState[analogState] = PadPush;
		}
		m_AnalogLOldState[analogState] = PadOn;
	}
	else
	{
		if (m_AnalogLOldState[analogState] == PadOn)
		{
			m_AnalogLState[analogState] = PadRelease;
		}
		else
		{
			m_AnalogLState[analogState] = PadOff;
		}
		m_AnalogLOldState[analogState] = PadOff;
	}
}

void XinputDevice::TriggerRStateDivide() {
	if (GetTriggerValue(RIGHT_TRIGGER))
	{
		if (m_TriggerROldState == PadOn)
		{
			m_TriggerRState = PadOn;
		}
		else
		{
			m_TriggerRState = PadPush;
		}
		m_TriggerROldState = PadOn;
	}
	else
	{
		if (m_TriggerROldState == PadOn)
		{
			m_TriggerRState = PadRelease;
		}
		else
		{
			m_TriggerRState = PadOff;
		}
		m_TriggerROldState = PadOff;
	}
}
void XinputDevice::TriggerLStateDivide() {
	if (GetTriggerValue(LEFT_TRIGGER))
	{
		if (m_TriggerLOldState == PadOn)
		{
			m_TriggerLState = PadOn;
		}
		else
		{
			m_TriggerLState = PadPush;
		}
		m_TriggerLOldState = PadOn;
	}
	else
	{
		if (m_TriggerLOldState == PadOn)
		{
			m_TriggerLState = PadRelease;
		}
		else
		{
			m_TriggerLState = PadOff;
		}
		m_TriggerLOldState = PadOff;
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

