
/*!
@file FluidUVController.h
@brief FluidUVController�w�b�_�@
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�t�̓����UV�ɂ����邽�߂̏���
	class FluidUVController : public Component
	{
		struct Parametor {
			float speed = 1.0f;
			float elapsedSpeed = speed;
			float decelerationSpeed = 0.5f;  //�����X�s�[�h
			Vec2 direct = Vec2(0.0f, 1.0f);
			Vec2 offsetElapsed = Vec2(0.0f);  
		};

		Parametor m_param;

	public:

		FluidUVController(const std::shared_ptr<GameObject>& objPtr, const Parametor& param = Parametor())
			:Component(objPtr),m_param(param)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//�t�̓���
		void FluidUpdate();

		//�A�N�Z�b�T------------------------------------------------------

		void FluidStart();

		void SetParametor(const Parametor& param) {
			m_param = param;
		}
		Parametor GetParametor() {
			return m_param;
		}

	};

}

//endbasecross