#pragma once
#include<x3daudio.h>
#include"SaveHelper.h"

namespace basecross
{
	struct SoundSettingData
	{
		float bgmVolume;
		float seVolume;
	};

	class SoundSetting : public SavableBase<SoundSettingData>
	{
		SoundSettingData m_soundSettingData;

	public:
		itbs::Utility::Delegate<void()> changeEvent;

		SoundSetting(const std::wstring& filePath);

		void SetBGMVolume(const float bgmVolume);
		void SetSEVolume(const float seVolume);

		void AddBGMVolume(const float addVolume);
		void AddSEVolume(const float addVolume);

		float GetBGMVolume() const;
		float GetSEVolume() const;
	};

	/// <summary>
	/// �T�E���h�Đ��p�f�[�^
	/// </summary>
	struct SoundClip
	{
		/// <summary>
		/// �Đ����̃L�[
		/// </summary>
		std::wstring soundName;
		/// <summary>
		/// ���[�v�����邩�ǂ���
		/// </summary>
		bool isLoop;
		/// <summary>
		/// ����
		/// </summary>
		float volume;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		SoundClip();

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="soundName">�Đ����̃L�[</param>
		/// <param name="isLoop">���[�v�����邩</param>
		/// <param name="volume">����</param>
		SoundClip(const std::wstring& soundName, const bool isLoop, const float volume);
	};

	/// <summary>
	/// SoundItem�Ɖ��ʂ̃y�A
	/// </summary>
	struct SoundData
	{
		/// <summary>
		/// �T�E���h�A�C�e��
		/// </summary>
		ex_weak_ptr<SoundItem> soundItem;
		/// <summary>
		/// ����
		/// </summary>
		float volume;
		/// <summary>
		/// ���f�ނ̃L�[
		/// </summary>
		std::wstring soundKey;
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		SoundData();
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="soundItem">�T�E���h�A�C�e��</param>
		/// <param name="volume">����</param>
		/// <param name="soundKey">���f�ނ̃L�[</param>
		SoundData(const std::shared_ptr<SoundItem>& soundItem, const float volume, const std::wstring& soundKey);
	};


	/// <summary>
	/// �ȒP��SE��BGM�Ǘ��N���X
	/// </summary>
	class SimpleSoundManager
	{
		/// <summary>
		/// ������Setting����邩�ǂ���
		/// </summary>
		static bool m_canSetting;

		/// <summary>
		/// BGM�̃T�E���h�A�C�e���̉���
		/// </summary>
		static SoundData m_bgmSoundData;

		/// <summary>
		/// SE�̃T�E���h�A�C�e���Ɖ��ʍ\����
		/// </summary>
		static std::vector<SoundData> m_seSoundDatas;

		/// <summary>
		/// �T�E���h�A�C�e�����쐬����
		/// </summary>
		/// <param name="soundClip">�T�E���h�A�C�e�������̂ɕK�v�ȃf�[�^�\����</param>
		/// <returns>�T�E���h�A�C�e��</returns>
		static std::shared_ptr<SoundItem> CreateSoundItem(const SoundClip& soundClip);

		/// <summary>
		/// �Ǘ����Ă���T�E���h�A�C�e���̉��ʂ����ׂčX�V����
		/// </summary>
		static void UpdateSoundItemVolume();

		/// <summary>
		/// �T�E���h�A�C�e���̉��ʂ��X�V����
		/// </summary>
		/// <param name="soundItemAndVolume">�X�V����T�E���h�A�C�e���Ɖ��ʍ\����</param>
		/// <param name="baseVolume">�X�V���鉹�ʂ̊�{����</param>
		static void SettingSoundVolume(const SoundData& soundItemAndVolume, const float baseVolume);

		/// <summary>
		/// SE�̊Ǘ��f�[�^�z����֐��ōX�V����
		/// </summary>
		/// <param name="func">�Ăт����֐�</param>
		static void UpdateSESoundItemAndVolumes(void(*func)(SoundData&));
	public:
		/// <summary>
		/// BGM��؂�ւ���
		/// </summary>
		/// <param name="bgmName">BGM��</param>
		/// <param name="volume">����</param>
		static void ChangeBGM(const std::wstring& bgmName,const float volume = 1.0f);

		/// <summary>
		/// BGM���ꎞ��~����
		/// </summary>
		static void PauseBGM();
		/// <summary>
		/// BGM���ĊJ����
		/// </summary>
		static void UnPauseBGM();
		/// <summary>
		/// BGM���I����~����
		/// </summary>
		static void StopBGM();

		/// <summary>
		/// �n���ꂽ�L�[��BGM������Ă��邩
		/// </summary>
		/// <param name="bgmName">BGM�̃L�[</param>
		/// <returns>����Ă��邩</returns>
		static bool IsPlayingBGM(const std::wstring& bgmName);

		/// <summary>
		/// SE�����Đ�����
		/// </summary>
		/// <param name="soundName">SE��</param>
		/// <param name="volume">����</param>
		static void OnePlaySE(const std::wstring& soundName,const float volume = 1.0f);

		/// <summary>
		/// SE���ꎞ��~����
		/// </summary>
		static void PauseSE();

		/// <summary>
		/// SE���ĊJ����
		/// </summary>
		static void UnPauseSE();

		/// <summary>
		/// SE���I������
		/// </summary>
		static void StopSE();
	};

	/// <summary>
	/// 3D�����p ���𕷂��I�u�W�F�N�g�ɂ���R���|�[�l���g(1�X�e�[�W�Ɉ�܂�)
	/// </summary>
	class SoundListener : public Component
	{
		/// <summary>
		/// ����������Ă��邩�ǂ���
		/// </summary>
		static bool m_isInited;
		/// <summary>
		/// X3DAudio�̃C���X�^���X�n���h��
		/// </summary>
		static X3DAUDIO_HANDLE m_X3DAudioHandle;
		/// <summary>
		/// 3D�����̌v�Z�������ʂ������Ă���\����
		/// </summary>
		static X3DAUDIO_DSP_SETTINGS m_dspSettring;

		/// <summary>
		/// ����������Ă��Ȃ������珉����������
		/// </summary>
		static void CheckInit();

		/// <summary>
		/// ���X�i�[�\���̂��쐬����
		/// </summary>
		/// <returns>���X�i�[�\����</returns>
		X3DAUDIO_LISTENER CreateListener() const;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		SoundListener(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// ������ʒu�Ȃǂ��特�̏����v�Z���ĕԂ�
		/// </summary>
		/// <param name="emitter">�G�~�b�^�[�\����</param>
		/// <returns>����񂪓������\����</returns>
		const X3DAUDIO_DSP_SETTINGS& SoundCalculate(const X3DAUDIO_EMITTER& emitter) const;
	};

	/// <summary>
	/// 3D�����p ���𔭂���I�u�W�F�N�g�ɂ���R���|�[�l���g
	/// </summary>
	class SoundEmitter : public Component
	{
		/// <summary>
		/// ���X�i�[�̎Q��
		/// </summary>
		ex_weak_ptr<SoundListener> m_listener;

		/// <summary>
		/// SoundItem�Ǘ��z��
		/// </summary>
		std::vector<SoundData> m_soundItemAndVolumes;

		/// <summary>
		/// �����v�Z�Ŏg���I�u�W�F�N�g�̃G�~�b�^�[�\���̂��쐬����
		/// </summary>
		/// <param name="soundItem">�T�E���h�A�C�e��</param>
		/// <returns>�G�~�b�^�[�\����</returns>
		X3DAUDIO_EMITTER CreateEmitter(const ex_weak_ptr<SoundItem>& soundItem) const;

		/// <summary>
		/// ���X�i�[�̎Q�Ƃ�������΃��X�i�[��T�����ĎQ�Ƃ���
		/// </summary>
		void CheckListener();

		/// <summary>
		/// �T�E���h�A�C�e�����X�V����
		/// </summary>
		/// <param name="soundItemAndVolome">�T�E���h�A�C�e��</param>
		/// <param name="dspSetting">�X�V�p�̃f�[�^�\����</param>
		void UpdateSoundItemAndVolume(const SoundData& soundItemAndVolome, const X3DAUDIO_DSP_SETTINGS& dspSetting) const;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		SoundEmitter(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// �����Đ�����
		/// </summary>
		/// <param name="soundClip">�Đ�����T�E���h�f�[�^</param>
		void PlaySoundClip(const SoundClip& soundClip);

		void OnStart() override;

		void OnUpdate() override;

		void OnEnable() override;

		void OnDisable() override;
	};
}