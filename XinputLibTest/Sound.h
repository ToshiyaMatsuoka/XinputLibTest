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
		VOICE,
	};

	struct SoundKey {
		const TCHAR* Key;
		SoundType Type;
		bool isSimultaneous = false;
	};

	Sound();

	~Sound();


	/// <summary>
	/// 音声ファイルを追加する。
	/// </summary>
	/// <param name="pFilePath">ファイルパス</param>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <param name="type">音声に設定する音声種別</param>
	void AddFile(const TCHAR* pFilePath, const TCHAR* pKey, SoundType type);

	/// <summary>
	/// 音声ファイルを10個分追加する。
	/// </summary>
	/// <param name="pFilePath">ファイルパス</param>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <param name="type">音声に設定する音声種別</param>
	void AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey, SoundType type);

	/// <summary>
	/// ファイルの先頭から単発再生を行う。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	void OneShotSimultaneous(const TCHAR* pKey);

	/// <summary>
	/// ファイルの先頭からループ再生を行う。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	void LoopStart(const TCHAR* pKey);

	/// <summary>
	/// ファイルの先頭から再生を行う。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	void OneShotStart(const TCHAR* pKey);

	/// <summary>
	/// 再生を一時停止する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <returns>成否</returns>
	/// <remarks>続きから再生再開するときには<see cref="Resume(const T*)"/>を実行して下さい。</remarks>
	void Pause(const TCHAR* pKey);

	/// <summary>
	/// 一時停止中の音声を続きから再生する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <returns>成否</returns>
	/// <remarks><see cref="Pause(const T*)"/>で一時停止した音声の続きからの再生に使用します。</remarks>
	void Resume(const TCHAR* pKey);

	/// <summary>
	/// 再生を停止する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <returns>成否</returns>
	/// <remarks>後で続きから再生する必要がある場合は、<see cref="Pause(const TCHAR*)"/>を使用して下さい。</remarks>
	void Stop(const TCHAR* pKey);

	/// <summary>
	/// 再生を停止する。
	/// </summary>
	/// <param name="type">音声ファイルを識別する音声種別</param>
	/// <returns>成否</returns>
	/// <remarks>後で続きから再生する必要がある場合は、<see cref="Pause(const TCHAR*)"/>を使用して下さい。</remarks>
	void Stop(SoundType type = ALL_TYPE);

	/// <summary>
	/// 再生状況を示すステータスを取得する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <returns>再生ステータス</returns>
	SoundLib::PlayingStatus GetStatus(const TCHAR* pKey) const;

	/// <summary>
	/// ボリュームを取得する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <returns>ボリューム(0:無音　100:音源ボリューム)</returns>
	uint8_t GetVolume(const TCHAR* pKey) const;

	/// <summary>
	/// 再生速度とピッチの変化率を取得する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <returns>音源からの変化率</returns>
	/// <remarks>
	/// 1.0の場合、音源から変化なし。
	/// 2.0の場合、再生速度2倍で1オクターブ高音。
	/// 0.5の場合、再生速度1/2で1オクターブ低音。
	/// </remarks>
	float GetFrequencyRatio(const TCHAR* pKey) const;

	/// <summary>
	/// 再生速度とピッチの変化率を設定する。
	/// </summary>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	/// <param name="ratio">音源からの変化率</param>
	/// <returns>成否</returns>
	/// <remarks>
	/// <para>
	/// 1.0の場合、音源から変化なし。
	/// 2.0の場合、再生速度2倍で1オクターブ高音。
	/// 0.5の場合、再生速度1/2で1オクターブ低音。
	/// </para>
	/// <para>設定可能最大値は4。</para>
	/// </remarks>
	void SetFrequencyRatio(const TCHAR* pKey, float ratio);

	/// <summary>
	/// ボリュームを設定する。
	/// </summary>
	/// <param name="vol">ボリューム(0:無音　100:音源ボリューム)</param>
	/// <param name="pKey">音声ファイルを識別するキー</param>
	void SetVolume(int vol,const TCHAR* pKey);

	/// <summary>
	/// ボリュームを設定する。
	/// </summary>
	/// <param name="vol">ボリューム(0:無音　100:音源ボリューム)</param>
	/// <param name="type">音声ファイルを識別する音声種別</param>
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

	const TCHAR TEXT_END = _T('\0');

	std::map<const TCHAR*, SimultaneousKeys> m_simultaneousKeys;

	std::vector<SoundKey> m_soundKeys;

	/// <summary>
	/// AddSimultaneousFile()で生成したキーか調べる
	/// </summary>
	/// <param name="pKey"></param>
	/// <returns>AddSimultaneousFile()で生成していれば真</returns>
	bool IsSimultaneousKey(const TCHAR* pKey);

	/// <summary>
	/// 同じキーが存在するか確認する
	/// </summary>
	/// <param name="pKey"></param>
	/// <returns>存在すれば真、しなければ偽</returns>
	bool FindSameKey(const TCHAR* pKey);
};

//
//bgm、seなどの振り分けを使用者ができるようにする
//振り分けたそれぞれに停止と音量設定ができるようにする
//

#endif // !SOUND_H
