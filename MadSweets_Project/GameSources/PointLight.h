/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	struct PointLightParam {
		Col4 diffuseColor = Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f);	//�f�B�t�B�[�Y�F
		Col4 specularColor = Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f);	//�X�y�L�����[�F
		Vec4 position = Vec4(0.0f);
		Col4 power = Col4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	class PointLight : public Component
	{
		PointLightParam m_param;

	public:
		PointLight(const std::shared_ptr<GameObject>& objPtr);

		PointLight(const std::shared_ptr<GameObject>& objPtr,
			const PointLightParam& param
		);

		void OnCreate() override {}
		void OnUpdate() override;

		//�A�N�Z�b�T---------------------------------------------------------
		void SetParametor(const PointLightParam& param) {
			m_param = param;
		}
		PointLightParam GetParametor() const {
			return m_param;
		}

		void SetPower(const float& power) {
			m_param.power = Col4(1.0f) * power;
		}
	};

}

//endbasecorss