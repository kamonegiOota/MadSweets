
/*!
@file TargetChase.h
@brief TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

namespace basecross {

	/// <summary>
	/// �^�[�Q�b�g���瓦����R���|�[�l���g
	/// </summary>
	class TargetEscape : public Component
	{
		int m_outSightCount = 0;     //���E����O�ꂽ�񐔂��J�E���g
		int m_alertReleaseNum = 2;   //���E���牽��O�ꂽ��x�����������邩  

		std::shared_ptr<GameObject> m_target;

		void Move();
		void TargetRayCheck();   //�^�[�Q�b�g�����E���ɂ��邩�ǂ������f
		void ChangeStateCheck(); //�X�e�[�g�̕ύX���K�v�Ȃ�ύX����B
		void CalucNextNode();    //���̃m�[�h���v�Z����B

		void SuccessEscape();

	public:
		TargetEscape(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//�A�N�Z�b�T-------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		
	};

}

//endbasecross