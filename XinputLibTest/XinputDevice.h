#ifndef XINPUT_DEVICE_H
#define XINPUT_DEVICE_H
/**
* @file
* @author Toshiya Matsuoka
*/
#include <Windows.h>
#include<Xinput.h>

/// <summary>
/// Xinputでの列挙体の纏まり
/// </summary>
namespace Xinput {
	/// <summary>
	/// コントローラ番号
	/// </summary>
	enum PLAYER_NUM
	{
		PLAYER_01,
		PLAYER_02,
		PLAYER_03,
		PLAYER_04,
	};

	/// <summary>
	/// ボタンの押下状態
	/// </summary>
	enum PADSTATE
	{
		//! 押されていない
		PadOff,
		//! 押されている
		PadOn,
		//! 押された
		PadPush,
		//! 離された
		PadRelease
	};
	/// <summary>
	/// パッドのボタン番号
	/// </summary>
	enum ButtonIndex
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		//! R1ボタン
		ButtonRB,
		//! L1ボタン
		ButtonLB,
		ButtonStart,
		ButtonBack,
		ButtonUP,
		ButtonDOWN,
		ButtonLEFT,
		ButtonRIGHT,
		//!L3ボタン
		ButtonLeftThumb,
		//!R3ボタン
		ButtonRightThumb,
		ButtomIndexMAX
	};

	/// <summary>
	/// アナログスティックの傾き方向
	/// </summary>
	enum ThumbTilt
	{
		THUMB_UP,
		THUMB_DOWN,
		THUMB_LEFT,
		THUMB_RIGHT,
		ANALOGMAX
	};
	/// <summary>
	/// アナログスティックの傾き軸
	/// </summary>
	enum ThumbTiltAxis
	{
		THUMB_X,
		THUMB_Y,
	};
	/// <summary>
	/// 左右のトリガー識別
	/// </summary>
	enum Trigger
	{
		LEFT_TRIGGER,
		RIGHT_TRIGGER
	};
};

/// <summary>
/// XinputPADの動作
/// </summary>
class XinputDevice {
	
public:
	
	/// <param name="leftThumbDeadzone">0-32767の範囲を取る指定の左スティックデッドゾーン値</param>
	/// <param name="rightThumbDeadzone">0-32767の範囲を取る指定の右スティックデッドゾーン値</param>
	/// <param name="leftTriggerDeadzone">0-255の範囲を取る指定の左トリガーデッドゾーン値</param>
	/// <param name="rightTriggerDeadzone">0-255の範囲を取る指定の右トリガーデッドゾーン値</param>
	explicit XinputDevice(Xinput::PLAYER_NUM number, int leftThumbDeadzone = 0, int rightThumbDeadzone = 0, int leftTriggerDeadzone = 0, int rightTriggerDeadzone = 0);

	~XinputDevice();

	/// <summary>
	/// 接続状態の取得
	/// </summary>
	/// <returns>保存されているXInputGetState関数の戻り値</returns>
	DWORD GetInfo() const{
		return XINPUT_INFO;
	}

	/// <summary>
	/// 左スティックのデッドゾーン指定
	/// </summary>
	/// <param name="leftThumbDeadzone">0-32767の範囲を取る指定のデッドゾーン値</param>
	void SetLeftThumbDeadzone(unsigned int leftThumbDeadzone);

	/// <summary>
	/// 右スティックのデッドゾーン指定
	/// </summary>
	/// <param name="rightThumbDeadzone">0-32767の範囲を取る指定のデッドゾーン値</param>
	void SetRightThumbDeadzone(unsigned int rightThumbDeadzone);

	/// <summary>
	/// 左トリガーのデッドゾーン指定
	/// </summary>
	/// <param name="leftTriggerDeadzone">0-255の範囲を取る指定のデッドゾーン値</param>
	void SetLeftTriggerDeadzone(unsigned int leftTriggerDeadzone);

	/// <summary>
	/// 右トリガーのデッドゾーン指定
	/// </summary>
	/// <param name="rightTriggerDeadzone">0-255の範囲を取る指定のデッドゾーン値</param>
	void SetRightTriggerDeadzone(unsigned int rightTriggerDeadzone);

	/// <summary>
	/// GetControlとButtonCheckを纏めて行う
	/// </summary>
	/// <seealso cref="GetControl"/>
	/// <seealso cref="ButtonCheck"/>
	void DeviceUpdate();

	/// <summary>
	/// XinputDeviceでゲームパッドの入力取得
	/// </summary>
	/// <param name="index">取得したいボタンの配列番号</param>
	/// <returns>PADSTATEの値</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetButton(Xinput::ButtonIndex index)const;

	/// <summary>
	/// すべてのゲームパッドのいずれかのボタン押下確認
	/// </summary>
	/// <returns>いずれかのボタンが押下されてればtrue</returns>
	bool PressedAnyButton() const;

	/// <summary>
	/// XinputDeviceでゲームパッドのトリガーの入力取得
	/// </summary>
	/// <param name="trigger">トリガーの左右認識番号</param>
	/// <returns>0～255の値、押してなければ0</returns>
	/// <seealso cref="Xinput::trigger"/>
	int GetTriggerValue(Xinput::Trigger trigger)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティックが傾いているか取得
	/// </summary>
	/// <param name="thumbTilt">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::ThumbTilt"/>
	bool TiltedLeftThumb(Xinput::ThumbTilt thumbTilt)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティックが傾いているか取得
	/// </summary>
	/// <param name="thumbTilt">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::ThumbTilt"/>
	bool TiltedRightThumb(Xinput::ThumbTilt thumbTilt)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="thumbTilt">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::ThumbTilt"/>
	int GetLeftThumbValue(Xinput::ThumbTiltAxis thumbTilt)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="thumbTilt">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::ThumbTilt"/>
	int GetRightThumbValue(Xinput::ThumbTiltAxis thumbTilt)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="thumbTilt">スティックの方向け先番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::ThumbTilt"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetLeftThumbState(Xinput::ThumbTilt thumbTilt)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="thumbTilt">スティックの方向け先番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::ThumbTilt"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetRightThumbState(Xinput::ThumbTilt thumbTilt)const;

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetRightTriggerState()const;

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetLeftTriggerState()const;

	/// <summary>
	/// 左右のバイブレーションモーターを動作させる
	/// </summary>
	/// <param name="leftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <param name="rightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
	void RunVibration(unsigned int leftValue = 0, unsigned int rightValue = 0);

private:
	const Xinput::PLAYER_NUM CONTROLER_NUM;
	const unsigned int MAX_VIBRATION_VALUE = 65535;
	const unsigned int MAX_TRIGGER_VALUE = 255;
	const unsigned int MAX_THUMB_VALUE = 32767;

	XINPUT_STATE m_Xinput = { NULL };
	// スティックデッドゾーン 
	int m_LeftThumbDeadzone;
	int m_RightThumbDeadzone;
	// トリガーデッドゾーン 
	int m_LeftTriggerDeadzone;
	int m_RightTriggerDeadzone;

	Xinput::PADSTATE m_PadState[Xinput::ButtomIndexMAX] = { Xinput::PadOff };
	Xinput::PADSTATE m_PadOldState[Xinput::ButtomIndexMAX] = { Xinput::PadOff };

	Xinput::PADSTATE m_RightThumbOldState[Xinput::ANALOGMAX] = { Xinput::PadOff };
	Xinput::PADSTATE m_RightThumbState[Xinput::ANALOGMAX] = { Xinput::PadOff };

	Xinput::PADSTATE m_LeftThumbOldState[Xinput::ANALOGMAX] = { Xinput::PadOff };
	Xinput::PADSTATE m_LeftThumbState[Xinput::ANALOGMAX] = { Xinput::PadOff };
	
	Xinput::PADSTATE m_RightTriggerOldState = Xinput::PadOff;
	Xinput::PADSTATE m_RightTriggerState = Xinput::PadOff;

	Xinput::PADSTATE m_LeftTriggerOldState = Xinput::PadOff;
	Xinput::PADSTATE m_LeftTriggerState = Xinput::PadOff;

	//! デバイスの状態確認用
	DWORD XINPUT_INFO = -1;
	
	const int INCLINATION_THRESHOLD_VALUE = MAX_THUMB_VALUE * 0.5;
	
	/// <summary>
	/// XinputDeviceでゲームパッドデバイスの取得
	/// </summary>
	void GetControl();

	/// <summary>
	/// 全てのボタンに対してCheckButtonStateを行う
	/// </summary>
	/// <seealso cref="CheckButtonState"/>
	void ButtonCheck();

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態振り分け
	/// </summary>
	/// <param name="thumbTilt">入力状態の欲しい方向</param>
	/// <seealso cref="Xinput::ThumbTilt"/>
	void LeftThumbStateDivide(Xinput::ThumbTilt thumbTilt);

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力状態振り分け
	/// </summary>
	/// <param name="thumbTilt">入力状態の欲しい方向</param>
	/// <seealso cref="Xinput::ThumbTilt"/>
	void RightThumbStateDivide(Xinput::ThumbTilt thumbTilt);

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態振り分け
	/// </summary>
	void TriggerRStateDivide();

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態振り分け
	/// </summary>
	void TriggerLStateDivide();

	/// <summary>
	/// Dinputでキーボードの状態取得
	/// </summary>
	/// <param name="ButtomID">取得したいXInputボタン番号</param>
	/// <param name="ButtomIndex">取得したいボタンの配列番号</param>
	/// <seealso cref="Xinput::ButtonIndex"/>
	void CheckButtonState(WORD ButtomID, Xinput::ButtonIndex ButtomIndex);


};
#endif
