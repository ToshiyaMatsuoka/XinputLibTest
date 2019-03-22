#ifndef XINPUT_MANAGER_H
#define XINPUT_MANAGER_H
/**
* @file
* @author Toshiya Matsuoka
*/

#include "XinputDevice.h"

/// <summary>
/// XinputPADの管理
/// </summary>
class XinputManager
{
public:

	/// <param name="thumbLDeadzone">0-32767の範囲を取る指定の左スティックデッドゾーン値</param>
	/// <param name="thumbRDeadzone">0-32767の範囲を取る指定の右スティックデッドゾーン値</param>
	/// <param name="triggerLDeadzone">0-255の範囲を取る指定の左トリガーデッドゾーン値</param>
	/// <param name="triggerRDeadzone">0-255の範囲を取る指定の右トリガーデッドゾーン値</param>
	XinputManager(unsigned int thumbLDeadzone = 0, unsigned int thumbRDeadzone = 0, unsigned int triggerLDeadzone = 0, unsigned int triggerRDeadzone = 0);

	~XinputManager();

	/// <summary>
	/// PADの接続、入力状態の確認
	/// </summary>
	/// <seealso cref="GetControl"/>
	/// <seealso cref="BottonCheck"/>
	void DeviceUpdate();
	
	/// <summary>
	/// 接続状態の取得
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <returns>保存されているXInputGetState関数の戻り値</returns>
	HRESULT GetInfo(Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの入力取得
	/// </summary>
	/// <param name="index">取得したいボタンの配列番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>PADSTATEの値</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetButton(Xinput::ButtonIndex index, Xinput::PLAYER_NUM num)const;

	/// <summary>
	/// XinputDeviceでゲームパッドのいずれかのボタン押下確認
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <returns>いずれかのボタンが押下されてればtrue</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	bool PressedAnyButton(Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドのトリガーの入力取得
	/// </summary>
	/// <param name="Trigger">トリガーの左右認識番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>0～255の値、押してなければ0</returns>
	/// <seealso cref="Xinput::AnalogTrigger"/>
	int GetTriggerValue(Xinput::AnalogTrigger Trigger, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetThumbL(Xinput::Analog analogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetThumbR(Xinput::Analog analogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetThumbLValue(Xinput::AnalogAxis analogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetThumbRValue(Xinput::AnalogAxis analogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetThumbLState(Xinput::Analog analogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetThumbRState(Xinput::Analog analogState, Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態取得
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerRState(Xinput::PLAYER_NUM num);

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態取得
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerLState(Xinput::PLAYER_NUM num);

	/// <summary>
	/// 左右のバイブレーションモーターを動作させる
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <param name="LeftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <param name="RightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
	void RunVibration(Xinput::PLAYER_NUM num,unsigned int LeftValue = 0, unsigned int RightValue = 0);

	/// <summary>
	/// すべてのゲームパッドの入力取得
	/// </summary>
	/// <param name="index">取得したいボタンの配列番号</param>
	/// <returns>PADSTATEの値</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	Xinput::PADSTATE GetButton(Xinput::ButtonIndex index) const;

	/// <summary>
	/// すべてのゲームパッドのいずれかのボタン押下確認
	/// </summary>
	/// <returns>いずれかのボタンが押下されてればtrue</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	bool PressedAnyButton();

	/// <summary>
	/// すべてのゲームパッドのトリガーの入力取得
	/// </summary>
	/// <param name="Trigger">トリガーの左右認識番号</param>
	/// <returns>0～255の値、押してなければ0</returns>
	/// <seealso cref="Xinput::AnalogTrigger"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	int GetTriggerValue(Xinput::AnalogTrigger Trigger);

	/// <summary>
	/// すべてのゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	bool GetThumbL(Xinput::Analog analogState);

	/// <summary>
	/// すべてのゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	bool GetThumbR(Xinput::Analog analogState);

	/// <summary>
	/// すべてのゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	int GetThumbLValue(Xinput::AnalogAxis analogState);

	/// <summary>
	/// すべてのゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	int GetThumbRValue(Xinput::AnalogAxis analogState);

	/// <summary>
	/// すべてのゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	Xinput::PADSTATE GetThumbLState(Xinput::Analog analogState);

	/// <summary>
	/// すべてのゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="analogState">スティックの方向け先番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	Xinput::PADSTATE GetThumbRState(Xinput::Analog analogState);

	/// <summary>
	/// すべてのゲームパッドの右トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	Xinput::PADSTATE GetTriggerRState();

	/// <summary>
	/// すべてのゲームパッドの左トリガー入力状態取得
	/// </summary>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	/// <remarks>入力はPLAYER_01優先</remarks>	
	Xinput::PADSTATE GetTriggerLState();

	/// <summary>
	/// すべてのゲームパッドの左右のバイブレーションモーターを動作させる
	/// </summary>
	/// <param name="LeftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <param name="RightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
	void RunVibration(unsigned int leftValue, unsigned int rightValue);

private:
	static const int PLAYER_MAX = 4;
	XinputDevice* m_pXinputDevices[PLAYER_MAX];
};

#endif
