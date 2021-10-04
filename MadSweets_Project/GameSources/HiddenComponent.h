#pragma once
#include"ChoicesComponentBase.h"

namespace basecross
{
	/// <summary>
	/// �B���̂Ɏg���f�[�^�\����
	/// </summary>
	struct HideData
	{
		/// <summary>
		/// �B���ۂ̃��[���h���W
		/// </summary>
		Vec3 hideWorldPosition;
		/// <summary>
		/// �B���ۂ̌���
		/// </summary>
		Vec3 hideForward;
		//�B��Ă���I�u�W�F�N�g
		ex_weak_ptr<GameObject> hideObject = nullptr;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		HideData();
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="hideWorldPosition">�B���ۂ̃��[���h���W</param>
		/// <param name="hideForward">�B���ۂ̌���</param>
		HideData(const Vec3& hideWorldPosition, const Vec3& hideForward);
	};

	/// <summary>
	/// �B��铮�������R���|�[�l���g�ɂ���Interface
	/// </summary>
	class I_HideComponent
	{
	public:
		/// <summary>
		/// �B���ۂɌĂ΂��֐�
		/// </summary>
		/// <param name="hideData">�B���ۂɎg���f�[�^�\����</param>
		virtual void OnHide(HideData& hideData) = 0;

		/// <summary>
		/// �B���̂��I�������Ƃ��ɌĂ΂��֐�
		/// </summary>
		/// <param name="hideData">�B���̂ɕK�v�ȃf�|�^�\����</param>
		virtual void OnEndHide(HideData& hideData) = 0;
	};

	/// <summary>
	/// �B�����I�u�W�F�N�g�̋@�\���������R���|�[�l���g
	/// </summary>
	class HiddenComponent : public ChoicesComponentBase
	{
		/// <summary>
		/// �B���̂ɕK�v�ȃf�[�^
		/// </summary>
		HideData m_hideData;

		std::shared_ptr<ChoicesObjectAndEvent> m_choicesObjectAndEvent;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		/// <param name="hideWorldPosition">�B���̂Ɏg�����[���h���W</param>
		/// <param name="hideForward">�B���Ƃ��̌���</param>
		HiddenComponent(std::shared_ptr<GameObject>& owner, const Vec3& hideWorldPosition, const Vec3& hideForward);
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		/// <param name="hiddenWorldPosition">�B���̂Ɏg���f�[�^�\����</param>
		HiddenComponent(std::shared_ptr<GameObject>& owner,const HideData& hiddenWorldPosition);

		/// <summary>
		/// �B���̂ɕK�v�ȃf�[�^���擾����
		/// </summary>
		/// <returns>�B���̂ɕK�v�ȃf�[�^</returns>
		HideData GetHideData() const;

		std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) override;
	};
}