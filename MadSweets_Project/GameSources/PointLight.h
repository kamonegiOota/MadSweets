/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	struct PointLight : Light 
	{
		Vec3 m_position;
		Col4 m_power;

		PointLight()
			:PointLight(Vec3(0, -1.0f, 0),
				Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f),
				Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f)
			)
		{}

		PointLight(const Vec3& dir, const Col4& def, const Col4& sp)
			:PointLight(dir, def, sp, Vec3(0.0f), Col4(1.0f))
		{}

		PointLight(const Vec3& dir, const Col4& def, const Col4& sp,
			const Vec3& position, const Col4& power
		):
			Light(dir, def , sp),
			m_position(position), m_power(power)
		{}

	};

	class PointLightComp : public Component
	{
		PointLight m_light;

	public:
		PointLightComp(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_light(PointLight())
		{}

		void OnCreate() override {}
		void OnUpdate() override {
			m_light.m_position = transform->GetPosition();
		}

		//アクセッサ---------------------------------------------------------
		PointLight GetLight() const {
			return m_light;
		}
	};

}

//endbasecorss