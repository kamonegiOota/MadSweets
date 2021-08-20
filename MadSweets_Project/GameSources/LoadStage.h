#pragma once

namespace basecross
{
	/// <summary>
	/// �f�ނ̃��[�h���s���X�e�[�W
	/// </summary>
	class LoadStage : public Stage
	{
		/// <summary>
		/// ���\�[�X�̓ǂݍ��ݗp�f�[�^�\����
		/// </summary>
		struct ResourceLoadData
		{
			/// <summary>
			/// ���\�[�X�̃L�[
			/// </summary>
			std::wstring resourceKey;
			/// <summary>
			/// �ǂݍ��ރt�@�C����
			/// </summary>
			std::wstring filename;

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="resourceKey">���\�[�X�̃L�[</param>
			/// <param name="filename">�ǂݍ��ރt�@�C����</param>
			ResourceLoadData(const std::wstring& resourceKey, const std::wstring& filename);
		};

		/// <summary>
		/// ���f���̃^�C�v
		/// </summary>
		enum class ModelType
		{
			/// <summary>
			/// �X�^�e�B�b�N���f��
			/// </summary>
			Static,
			/// <summary>
			/// �{�[�����f��
			/// </summary>
			Bone
		};

		/// <summary>
		/// ���f���p���\�[�X�ǂݍ��ݗp�f�[�^�\����
		/// </summary>
		struct ModelResourceLoadData : public ResourceLoadData
		{
			/// <summary>
			/// ���f���̃^�C�v
			/// </summary>
			ModelType modelType;
			/// <summary>
			/// ���f���������Ă���t�H���_
			/// </summary>
			std::wstring modelDir;
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="resourceKey">���\�[�X�̃L�[</param>
			/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
			/// <param name="modelType">���f���̃^�C�v</param>
			/// <param name="modelDir">���f���������Ă���t�H���_��</param>
			ModelResourceLoadData(const std::wstring& resourceKey,
				const std::wstring& filename, const ModelType modelType,const std::wstring& modelDir);
		};

		/// <summary>
		/// �~���[�e�b�N�X
		/// </summary>
		static std::mutex m_mtx;
		/// <summary>
		/// ���[�h���I���������ǂ���
		/// </summary>
		static bool m_isLoadFinish;

		/// <summary>
		/// ���̃X�e�[�W�̃L�[
		/// </summary>
		std::wstring m_nextStageKey;

		/// <summary>
		/// �{���̃X�e�[�W�̔w�i�F
		/// </summary>
		Col4 m_stageBackColor;

		/// <summary>
		/// �e�N�X�`�����[�h�p�f�[�^�z��
		/// </summary>
		static const std::vector<ResourceLoadData> m_texureResourceLoadDatas;
		/// <summary>
		/// SE���[�h�p�z��
		/// </summary>
		static const std::vector<ResourceLoadData> m_seResourceLoadDatas;
		/// <summary>
		/// BGM���[�h�p�z��
		/// </summary>
		static const std::vector<ResourceLoadData> m_bgmResourceLoadDatas;
		/// <summary>
		/// ���f�����[�h�p�z��
		/// </summary>
		static const std::vector<ModelResourceLoadData> m_modelResourceLoadDatas;
		/// <summary>
		/// �r���[�쐬
		/// </summary>
		void CreateViewLight();

		/// <summary>
		/// �f�ނ̃��[�h������
		/// </summary>
		static void LoadResource();

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="nextStageKey">���̃X�e�[�W�̃L�[</param>
		LoadStage(const std::wstring& nextStageKey);

		void OnCreate() override;

		void OnUpdate() override;
	};
}