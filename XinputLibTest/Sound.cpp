#include "Sound.h"

using namespace SoundLib;

Sound::Sound()
{
	m_soundsManager.Initialize();
}


Sound::~Sound()
{
	Stop();
	for (auto i : m_simultaneousKeys)
	{
		for (auto& j : i.second.m_pKeys)
		{
			delete[] j;
		}
	}
	m_simultaneousKeys.clear();
}

void Sound::AddFile(const TCHAR* pFilePath, const TCHAR* pKey, SoundType type)
{
	if (FindSameKey(pKey))return;
	bool successAddFile = false;
	successAddFile = m_soundsManager.AddFile(pFilePath, pKey);
	if (successAddFile) {
		SoundKey soundKey;
		soundKey.Key = pKey;
		soundKey.Type = type;
		m_soundKeys.emplace_back(soundKey);
	}
}

//　一気に10個分の音声オブジェクトの生成する
void Sound::AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey, SoundType type)
{
	if (FindSameKey(pKey))return;
	size_t keyLength = _tcsclen(pKey);
	size_t additionalKeyLength = keyLength + 3;	// 数字と\0の数足す
	bool successAddFile = false;

	for (int i = 0; i < SimultaneousKeys::SIMULTANEOUS_NUM_MAX; ++i)
	{
		m_simultaneousKeys[pKey].m_pKeys[i] = new TCHAR[additionalKeyLength];

		_tcscpy_s(m_simultaneousKeys[pKey].m_pKeys[i], additionalKeyLength, pKey);

		
		//int hh = (1 + (i / SimultaneousKeys::SIMULTANEOUS_NUM_MAX));
		_itot_s(i, &m_simultaneousKeys[pKey].m_pKeys[i][keyLength], sizeof(TCHAR), 10);

		
		size_t simultaneousKeyLength = keyLength + 1/* + (i / SimultaneousKeys::SIMULTANEOUS_NUM_MAX)*/;
		m_simultaneousKeys[pKey].m_pKeys[i][simultaneousKeyLength] = TEXT_END;

		successAddFile = m_soundsManager.AddFile(pFilePath, m_simultaneousKeys[pKey].m_pKeys[i]);
		if (successAddFile) {
			SoundKey soundKey;
			soundKey.Key = pKey;
			soundKey.Type = type;
			soundKey.isSimultaneous = true;
			m_soundKeys.emplace_back(soundKey);
		}
	}
}

//一気に作った音声オブジェクトの再生
void Sound::OneShotSimultaneous(const TCHAR* pKey)
{
	if (false == FindSameKey(pKey))return;

	if (false == IsSimultaneousKey(pKey)) return;

	int currentNum = m_simultaneousKeys[pKey].m_currentPlayNum;

	int prevPrevNum = currentNum - 2;

	if (prevPrevNum < 0) prevPrevNum = SimultaneousKeys::SIMULTANEOUS_NUM_MAX + prevPrevNum;

	Stop(m_simultaneousKeys[pKey].m_pKeys[prevPrevNum]);

	OneShotStart(m_simultaneousKeys[pKey].m_pKeys[currentNum]);

	m_simultaneousKeys[pKey].m_currentPlayNum = (currentNum >= (SimultaneousKeys::SIMULTANEOUS_NUM_MAX - 1)) ? 0 : ++currentNum;
}

void Sound::LoopStart(const TCHAR* pKey)
{
	if (true == IsSimultaneousKey(pKey)) return;
	m_soundsManager.Start(pKey, true);
}

void Sound::OneShotStart(const TCHAR* pKey)
{
	if (true == IsSimultaneousKey(pKey)) return;
	m_soundsManager.Start(pKey, false);
}

void Sound::Pause(const TCHAR* pKey)
{
	m_soundsManager.Pause(pKey);
}

void Sound::Resume(const TCHAR* pKey)
{
	m_soundsManager.Resume(pKey);
}

void Sound::Stop(const TCHAR* pKey)
{
	m_soundsManager.Stop(pKey);
}

void Sound::Stop(SoundType type)
{
	for (auto i : m_soundKeys) {
		if (type != i.Type && type != ALL_TYPE) continue;
		m_soundsManager.Stop(i.Key);
	}
}

PlayingStatus Sound::GetStatus(const TCHAR* pKey) const
{
	return m_soundsManager.GetStatus(pKey);
}

uint8_t Sound::GetVolume(const TCHAR* pKey) const
{
	return m_soundsManager.GetVolume(pKey);
}

float Sound::GetFrequencyRatio(const TCHAR* pKey) const
{
	return m_soundsManager.GetFrequencyRatio(pKey);
}

void Sound::SetFrequencyRatio(const TCHAR* pKey, float ratio)
{
	m_soundsManager.SetFrequencyRatio(pKey, ratio);
}

void Sound::SetVolume(int vol, const TCHAR* pKey)
{
	m_soundsManager.SetVolume(pKey, vol);
}

void Sound::SetVolume(int vol, SoundType type)
{
	for (auto i : m_soundKeys) {
		if (type != i.Type && type != ALL_TYPE) continue;
		m_soundsManager.SetVolume(i.Key, vol);
	}
}

bool Sound::IsSimultaneousKey(const TCHAR* pKey)
{
	for (auto i : m_soundKeys)
	{
		if (i.Key != pKey) continue;
		if (i.isSimultaneous == true)
		{
			return true;
		}
		break;
	}
	return false;
}

bool Sound::FindSameKey(const TCHAR* pKey)
{
	for (auto i : m_soundKeys)
	{
		if (i.Key != pKey) continue;
		return true;
	}
	return false;
}


