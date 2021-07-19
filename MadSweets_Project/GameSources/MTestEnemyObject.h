/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MTestEnemyObject : public GameObject
	{


	public:
		MTestEnemyObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;


		//�A�N�Z�b�T-----------------------------------------------------------
		void SetColor(const Col4& color) {
			auto draw = GetComponent<BcPNTStaticDraw>();
			draw->SetDiffuse(color);
		}

		//�p�j�s���e�X�g
		void StartPlowlingTest();

		//�X�e�[�g�ύX�e�X�g
	};

}

//endbasecross