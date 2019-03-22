#include "Sound.h"



Sound::Sound()
{
	m_soundsManager.Initialize();
}


Sound::~Sound()
{
	for (auto i : m_simultaneousKeys)
	{
		for (INT si = 0; si < SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX; ++si)
		{
			delete[](i.second.m_pKeys[si]);
		}
	}

	m_simultaneousKeys.clear();
}

VOID Sound::AddFile(const TCHAR * pFilePath, const TCHAR * pKey)
{
	m_soundsManager.AddFile(pFilePath, pKey);
}

//　一気に10個分の音声オブジェクトの生成する
VOID Sound::AddSimultaneousFile(const TCHAR * pFilePath, const TCHAR * pKey)
{
	size_t tCharLength = _tcsclen(pKey);
	size_t additionalKeyLength = tCharLength + 3;	//! 数字と\0の数足す

	for (INT i = 0; i < SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX; ++i)
	{
		m_simultaneousKeys[pKey].m_pKeys[i] = new TCHAR[additionalKeyLength];

		_tcscpy_s(m_simultaneousKeys[pKey].m_pKeys[i], additionalKeyLength, pKey);

		_itot_s(i, &m_simultaneousKeys[pKey].m_pKeys[i][tCharLength], sizeof(TCHAR) * (1 + (i / SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX)), 10);
		m_simultaneousKeys[pKey].m_pKeys[i][tCharLength + 1 + (i / SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX)] = m_TEXT_END;

		m_soundsManager.AddFile(pFilePath, &m_simultaneousKeys[pKey].m_pKeys[i][0]);
	}
}

//一気に作った音声オブジェクトの再生
VOID Sound::OneShotSimultaneous(const TCHAR * pKey)
{
	INT currentNum = m_simultaneousKeys[pKey].m_currentPlayNum;

	INT prevPrevNum = currentNum - 2;

	if (prevPrevNum < 0) prevPrevNum = SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX + prevPrevNum;

	Stop(&m_simultaneousKeys[pKey].m_pKeys[prevPrevNum][0]);

	OneShotStart(&m_simultaneousKeys[pKey].m_pKeys[currentNum][0]);

	m_simultaneousKeys[pKey].m_currentPlayNum = (currentNum >= (SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX - 1)) ? 0 : ++currentNum;
}

VOID Sound::LoopStart(const TCHAR * pKey)
{
	m_soundsManager.Start(pKey, true);
}

VOID Sound::OneShotStart(const TCHAR * pKey)
{
	m_soundsManager.Start(pKey, false);
}

VOID Sound::Pause(const TCHAR * pKey)
{
	m_soundsManager.Pause(pKey);
}

VOID Sound::Resume(const TCHAR * pKey)
{
	m_soundsManager.Resume(pKey);
}

VOID Sound::Stop(const TCHAR * pKey)
{
	m_soundsManager.Stop(pKey);
}

VOID Sound::SetVolume(const TCHAR * pKey, INT vol)
{
	m_soundsManager.SetVolume(pKey, vol);
}

