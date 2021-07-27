#pragma once
#include"DelegateSystem.h"

namespace basecross
{
	/// <summary>
	/// �T�E���h�ݒ�p�N���X
	/// </summary>
	class SoundSetting
	{
		/// <summary>
		/// BGM�̊�{���ʂ̃��x�� (0 �` 10, �����l 5) 
		/// </summary>
		static int m_bgmVolumeLevel;
		/// <summary>
		/// SE�̊�{���ʃ��x�� (0 �` 10, �����l5)
		/// </summary>
		static int m_seVolumeLevel;

		/// <summary>
		/// BGM�{���̃L���b�V��
		/// </summary>
		static float m_bgmScaleCash;
		/// <summary>
		/// SE�{���̃L���b�V��
		/// </summary>
		static float m_seScaleCash;

		/// <summary>
		/// ���ʃ��x���ő��
		/// </summary>
		static constexpr int VOLUME_LEVEL_MAX = 10;
		/// <summary>
		/// ���{���ő��
		/// </summary>
		static constexpr float VOLUME_SCALE_MAX = 2.0f;


		/// <summary>
		/// �{�����[�����x������X�P�[�����v�Z����
		/// </summary>
		/// <param name="volumeLevel">�{�����[�����x��</param>
		/// <returns>�{�����[���X�P�[��</returns>
		static float VolumeScaleCalculate(const int volumeLevel);
	public:
		/// <summary>
		/// �f�[�^���ύX���ꂽ��ʒm����C�x���g
		/// </summary>
		static itbs::Utility::Delegate<void()> changeEventDelegate; // �C�x���g�쓮�p�̂��̂�����������}���ւ���

		/// <summary>
		/// BGM�̊�{���ʃ��x����ݒ肷��
		/// </summary>
		/// <param name="bgmValumeLevel">BGM��{���ʃ��x��</param>
		static void SetBGMVolumeLevel(const int bgmValumeLevel);

		/// <summary>
		/// BGM�̊�{���ʃ��x����ݒ肷��
		/// </summary>
		/// <returns>BGM��{���ʃ��x��</returns>
		static int GetBGMVolumeLevel();

		/// <summary>
		/// SE�̊�{���ʃ��x����ݒ肷��
		/// </summary>
		/// <param name="seValumeLevel">SE�̊�{���ʃ��x��</param>
		static void SetSEVolumeLevel(const int seValumeLevel);

		/// <summary>
		/// SE�̊�{���ʃ��x�����擾����
		/// </summary>
		/// <returns></returns>
		static int GetSEVolumeLevel();

		/// <summary>
		/// BGM�{�����擾����
		/// </summary>
		/// <returns>BGM�{��</returns>
		static float GetBGMScale();

		/// <summary>
		/// SE�{�����擾����
		/// </summary>
		/// <returns>SE�{��</returns>
		static float GetSEScale();
	};
}