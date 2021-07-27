#include"SoundSetting.h"
#include"MathHelper.h"

using itbs::Math::MyMath;

namespace basecross
{
	int SoundSetting::m_bgmVolumeLevel = 5;
	int SoundSetting::m_seVolumeLevel = 5;

	float SoundSetting::m_bgmScaleCash = SoundSetting::VolumeScaleCalculate(SoundSetting::m_bgmVolumeLevel);
	float SoundSetting::m_seScaleCash = SoundSetting::VolumeScaleCalculate(SoundSetting::m_seVolumeLevel);

	itbs::Utility::Delegate<void()> SoundSetting::changeEventDelegate;


	float SoundSetting::VolumeScaleCalculate(const int volumeLevel)
	{
		float volumeLevelHalf = VOLUME_LEVEL_MAX * 0.5f;
		float level = volumeLevel - volumeLevelHalf;
		float levelScale = level / volumeLevelHalf;
		float volumeScaleCenter = VOLUME_SCALE_MAX * 0.5f;
		return levelScale * volumeScaleCenter + volumeLevelHalf;
	}

	void SoundSetting::SetBGMVolumeLevel(const int bgmValumeLevel)
	{
		m_bgmVolumeLevel = static_cast<int>(MyMath::Clamp(bgmValumeLevel, 0, 10));

		m_bgmScaleCash = VolumeScaleCalculate(m_bgmVolumeLevel);

		changeEventDelegate();
	}

	int SoundSetting::GetBGMVolumeLevel()
	{
		return m_bgmVolumeLevel;
	}

	void SoundSetting::SetSEVolumeLevel(const int seBalumeLevel)
	{
		m_seVolumeLevel = static_cast<int>(MyMath::Clamp(seBalumeLevel, 0, 10));

		m_seScaleCash = VolumeScaleCalculate(m_seVolumeLevel);

		changeEventDelegate();
	}

	int SoundSetting::GetSEVolumeLevel()
	{
		return m_seVolumeLevel;
	}

	float SoundSetting::GetBGMScale()
	{
		return m_bgmScaleCash;
	}

	float SoundSetting::GetSEScale()
	{
		return m_seScaleCash;
	}
}