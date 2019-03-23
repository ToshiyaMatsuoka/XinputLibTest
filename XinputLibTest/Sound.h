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

	enum SoundType {
		ALL_TYPE,
		BGM,
		SE,
	};

	struct SoundKey {
		const TCHAR* Key;
		SoundType Type;
	};

	Sound();

	~Sound();

	SoundLib::PlayingStatus GetStatus(const WCHAR * pKey) const;

	void AddFile(const TCHAR* pFilePath, const TCHAR* pKey, SoundType type);

	void AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey, SoundType type);

	void OneShotSimultaneous(const TCHAR* pKey);

	void LoopStart(const TCHAR* pKey);

	void OneShotStart(const TCHAR* pKey);

	void Pause(const TCHAR* pKey);

	void Resume(const TCHAR* pKey);

	void Stop(const TCHAR* pKey);

	void Stop(SoundType type = ALL_TYPE);

	void SetVolume(const TCHAR * pKey, int vol);

	void SetVolume(int vol, SoundType type = ALL_TYPE);

private:
	
	Sound(Sound& sound) = delete;

	Sound& operator=(Sound& sound) = delete;

	struct SimultaneousKeys
	{
	public:
		static const int SIMULTANEOUS_NUM_MAX = 10;
		TCHAR* m_pKeys[SIMULTANEOUS_NUM_MAX];
		int m_currentPlayNum = 0;
	};

	SoundLib::SoundsManager m_soundsManager;

	const TCHAR m_TEXT_END = _T('\0');

	std::map<const TCHAR*, SimultaneousKeys> m_simultaneousKeys;

	std::vector<SoundKey> m_SoundKey;

	SoundType GetSoundType(int arrayNum) {
		return m_SoundKey[arrayNum].Type;
	}

};

//
//bgm、seなどの振り分けを使用者ができるようにする
//振り分けたそれぞれに停止と音量設定ができるようにする
//

#endif // !SOUND_H