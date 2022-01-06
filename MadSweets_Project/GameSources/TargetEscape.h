
/*!
@file TargetEscape.h
@brief TargetEscape
�S���ҁF�ێR �T��
*/

#pragma once

#include "BaseUseVelocity.h"
class BaseUseVelocity;

namespace basecross {

	/// <summary>
	/// �^�[�Q�b�g���瓦����R���|�[�l���g
	/// </summary>
	class TargetEscape : public Component , public BaseUseVelocity
	{
		int m_outSightCount = 0;     //���E����O�ꂽ�񐔂��J�E���g
		int m_alertReleaseNum = 2;   //���E���牽��O�ꂽ��x�����������邩  

		ex_weak_ptr<GameObject> m_target = nullptr;

		void EyeSearch(); //�����Ǘ�
		void Rotation();
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