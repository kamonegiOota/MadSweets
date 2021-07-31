/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	struct PointLightParam {
		Col4 diffuseColor = Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f);	//ディフィーズ色
		Col4 specularColor = Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f);	//スペキュラー色
		Vec4 position = Vec4(0.0f);
		Col4 power = Col4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	class PointLightComp : public Component
	{
		PointLightParam m_param;

	public:
		PointLightComp(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr), m_param(PointLightParam())
		{}

		void OnCreate() override {}
		void OnUpdate() override {
			m_param.position = transform->GetPosition();
		}

		//アクセッサ---------------------------------------------------------
		PointLightParam GetLight() const {
			return m_param;
		}
	};





	//struct PointLight : Light 
	//{
	//	Vec3 m_position;
	//	Col4 m_power;

	//	PointLight()
	//		:PointLight(Vec3(0, -1.0f, 0),
	//			Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f),
	//			Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f)
	//		)
	//	{}

	//	PointLight(const Vec3& dir, const Col4& def, const Col4& sp)
	//		:PointLight(dir, def, sp, Vec3(0.0f), Col4(1.0f))
	//	{}

	//	PointLight(const Vec3& dir, const Col4& def, const Col4& sp,
	//		const Vec3& position, const Col4& power
	//	):
	//		Light(dir, def , sp),
	//		m_position(position), m_power(power)
	//	{}

	//};

}

//endbasecorss