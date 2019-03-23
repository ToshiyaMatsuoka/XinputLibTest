#include "Sound.h"



Sound::Sound()
{
	m_soundsManager.Initialize();
}


Sound::~Sound()
{
	Stop();
	for (auto i : m_simultaneousKeys)
	{
		for (int si = 0; si < SimultaneousKeys::SIMULTANEOUS_NUM_MAX; ++si)
		{
			delete[](i.second.m_pKeys[si]);
		}
	}
	m_simultaneousKeys.clear();
}

SoundLib::PlayingStatus Sound::GetStatus(const WCHAR* pKey) const
{
	return m_soundsManager.GetStatus(pKey);
}

void Sound::AddFile(const TCHAR * pFilePath, const TCHAR * pKey, SoundType type)
{
	bool successAddFile = false;
	successAddFile = m_soundsManager.AddFile(pFilePath, pKey);
	if (successAddFile) {
		SoundKey soundKey;
		soundKey.Key = pKey;
		soundKey.Type = type;
		m_SoundKey.emplace_back(soundKey);
	}
}

//　一気に10個分の音声オブジェクトの生成する
void Sound::AddSimultaneousFile(const TCHAR * pFilePath, const TCHAR * pKey, SoundType type)
{
	size_t tCharLength = _tcsclen(pKey);
	size_t additionalKeyLength = tCharLength + 3;	//! 数字と\0の数足す
	bool successAddFile = false;

	for (int i = 0; i < SimultaneousKeys::SIMULTANEOUS_NUM_MAX; ++i)
	{
		m_simultaneousKeys[pKey].m_pKeys[i] = new TCHAR[additionalKeyLength];

		_tcscpy_s(m_simultaneousKeys[pKey].m_pKeys[i], additionalKeyLength, pKey);

		_itot_s(i, &m_simultaneousKeys[pKey].m_pKeys[i][tCharLength], sizeof(TCHAR) * (1 + (i / SimultaneousKeys::SIMULTANEOUS_NUM_MAX)), 10);
		m_simultaneousKeys[pKey].m_pKeys[i][tCharLength + 1 + (i / SimultaneousKeys::SIMULTANEOUS_NUM_MAX)] = m_TEXT_END;

		successAddFile = m_soundsManager.AddFile(pFilePath, &m_simultaneousKeys[pKey].m_pKeys[i][0]);
		if (successAddFile) {
			SoundKey soundKey;
			soundKey.Key = &m_simultaneousKeys[pKey].m_pKeys[i][0];
			soundKey.Type = type;
			m_SoundKey.emplace_back(soundKey);
		}
	}
}

//一気に作った音声オブジェクトの再生
void Sound::OneShotSimultaneous(const TCHAR * pKey)
{
	int currentNum = m_simultaneousKeys[pKey].m_currentPlayNum;

	int prevPrevNum = currentNum - 2;

	if (prevPrevNum < 0) prevPrevNum = SimultaneousKeys::SIMULTANEOUS_NUM_MAX + prevPrevNum;

	Stop(&m_simultaneousKeys[pKey].m_pKeys[prevPrevNum][0]);

	OneShotStart(&m_simultaneousKeys[pKey].m_pKeys[currentNum][0]);

	m_simultaneousKeys[pKey].m_currentPlayNum = (currentNum >= (SimultaneousKeys::SIMULTANEOUS_NUM_MAX - 1)) ? 0 : ++currentNum;
}

void Sound::LoopStart(const TCHAR * pKey)
{
	m_soundsManager.Start(pKey, true);
}

void Sound::OneShotStart(const TCHAR * pKey)
{
	m_soundsManager.Start(pKey, false);
}

void Sound::Pause(const TCHAR * pKey)
{
	m_soundsManager.Pause(pKey);
}

void Sound::Resume(const TCHAR * pKey)
{
	m_soundsManager.Resume(pKey);
}

void Sound::Stop(const TCHAR * pKey)
{
	m_soundsManager.Stop(pKey);
}

void Sound::Stop(SoundType type)
{
	for (auto i : m_SoundKey) {
		if (type != i.Type && type != ALL_TYPE) continue;
		m_soundsManager.Stop(i.Key);
	}
}

void Sound::SetVolume(const TCHAR * pKey, int vol)
{
	m_soundsManager.SetVolume(pKey, vol);
}


void Sound::SetVolume(int vol, SoundType type)
{
	for (auto i : m_SoundKey) {
		if (type != i.Type && type != ALL_TYPE) continue;
		m_soundsManager.SetVolume(i.Key, vol);
	}
}

