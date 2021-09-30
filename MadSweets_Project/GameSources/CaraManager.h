/*!
@file CaraManager.h
@brief CaraManager
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class CaraManager : public Component, public I_Chase, public I_Probe, public I_Ear, public I_ReturnPlowling
	{

	public:
		CaraManager(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		//Interface�̎���-------------------------------------------------------------

				//�Ǐ]�X�^�[�g
		void StartChase() override;
		void EndChase() override;  //�^�[�Q�b�g�����������Ƃ��̏���

		//�{���X�^�[�g
		void StartProbe() override;
		void EndProbe() override;
		void HideSearchAnimationStart() override;

		//���𕷂���
		void Listen() override;
		void EndListen() override;

		//���̏ꏊ�ɖ߂�s�׃X�^�[�g
		void StartReturnPlowling() override;
		void EndReturnPlowling() override;

		//�A�N�Z�b�T-------------------------------------------------------------------

	};

}

//endbasecross