#ifndef SOUND_H
#define SOUND_H

#include <windows.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <array>

#include "SoundLib/Include/SoundsManager.h"

class Sound
{
public:
	Sound();

	~Sound();

	VOID AddFile(const TCHAR* pFilePath, const TCHAR* pKey);

	VOID AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey);

	VOID OneShotSimultaneous(const TCHAR* pKey);

	VOID LoopStart(const TCHAR* pKey);

	VOID OneShotStart(const TCHAR* pKey);

	VOID Pause(const TCHAR* pKey);

	VOID Resume(const TCHAR* pKey);

	VOID Stop(const TCHAR* pKey);

	VOID SetVolume(const TCHAR* pKey, INT vol);

private:
	struct SimultaneousKeys
	{
	public:
		static const INT m_SIMULTANEOUS_NUM_MAX = 10;
		TCHAR* m_pKeys[m_SIMULTANEOUS_NUM_MAX];
		INT m_currentPlayNum = 0;
	};

	SoundLib::SoundsManager m_soundsManager;

	const TCHAR m_TEXT_END = _T('\0');

	std::map<const TCHAR*, SimultaneousKeys> m_simultaneousKeys;
};

//
//bgm、seなどの振り分けを使用者ができるようにする
//振り分けたそれぞれに停止と音量設定ができるようにする
//

#endif // !SOUND_H