/*!
@file AshiManager.h
@brief AshiManager
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "I_Escape.h"
#include "I_ReturnPlowling.h"

namespace basecross {

	class AshiManager : public BaseEnemy, public I_Escape, public I_ReturnPlowling
	{

	public:

		AshiManager(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		//�C���^�[�t�F�[�X�̎���---------------------------------------------------

		//������C���^�[�t�F�[�X
		void StartEscape() override;
		void SuccessEscape() override;

		//���̏ꏊ�ɖ߂�s�׃X�^�[�g
		void StartReturnPlowling() override;
		void EndReturnPlowling() override;
	};

}

//endbasecross