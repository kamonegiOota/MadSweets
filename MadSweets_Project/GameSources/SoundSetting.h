#pragma once
#include"DelegateSystem.h"

namespace basecross
{
	/// <summary>
	/// サウンド設定用クラス
	/// </summary>
	class SoundSetting
	{
		/// <summary>
		/// BGMの基本音量のレベル (0 ～ 10, 初期値 5) 
		/// </summary>
		static int m_bgmVolumeLevel;
		/// <summary>
		/// SEの基本音量レベル (0 ～ 10, 初期値5)
		/// </summary>
		static int m_seVolumeLevel;

		/// <summary>
		/// BGM倍率のキャッシュ
		/// </summary>
		static float m_bgmScaleCash;
		/// <summary>
		/// SE倍率のキャッシュ
		/// </summary>
		static float m_seScaleCash;

		/// <summary>
		/// 音量レベル最大量
		/// </summary>
		static constexpr int VOLUME_LEVEL_MAX = 10;
		/// <summary>
		/// 音倍率最大量
		/// </summary>
		static constexpr float VOLUME_SCALE_MAX = 2.0f;


		/// <summary>
		/// ボリュームレベルからスケールを計算する
		/// </summary>
		/// <param name="volumeLevel">ボリュームレベル</param>
		/// <returns>ボリュームスケール</returns>
		static float VolumeScaleCalculate(const int volumeLevel);
	public:
		/// <summary>
		/// データが変更されたら通知するイベント
		/// </summary>
		static itbs::Utility::Delegate<void()> changeEventDelegate; // イベント駆動用のものが完成したら挿げ替える

		/// <summary>
		/// BGMの基本音量レベルを設定する
		/// </summary>
		/// <param name="bgmValumeLevel">BGM基本音量レベル</param>
		static void SetBGMVolumeLevel(const int bgmValumeLevel);

		/// <summary>
		/// BGMの基本音量レベルを設定する
		/// </summary>
		/// <returns>BGM基本音量レベル</returns>
		static int GetBGMVolumeLevel();

		/// <summary>
		/// SEの基本音量レベルを設定する
		/// </summary>
		/// <param name="seValumeLevel">SEの基本音量レベル</param>
		static void SetSEVolumeLevel(const int seValumeLevel);

		/// <summary>
		/// SEの基本音量レベルを取得する
		/// </summary>
		/// <returns></returns>
		static int GetSEVolumeLevel();

		/// <summary>
		/// BGM倍率を取得する
		/// </summary>
		/// <returns>BGM倍率</returns>
		static float GetBGMScale();

		/// <summary>
		/// SE倍率を取得する
		/// </summary>
		/// <returns>SE倍率</returns>
		static float GetSEScale();
	};
}