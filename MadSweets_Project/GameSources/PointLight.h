/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	struct PointLight : Light 
	{
		Vec3 m_position;
		float m_power;

		PointLight()
			:PointLight(Vec3(0, -1.0f, 0),
				Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f),
				Col4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f)
			)
		{}

		PointLight(const Vec3& dir, const Col4& def, const Col4& sp)
			:PointLight(dir, def, sp, Vec3(0.0f), 1.0f)
		{}

		PointLight(const Vec3& dir, const Col4& def, const Col4& sp,
			const Vec3& position, const float& power
		):
			Light(dir, def , sp),
			m_position(position), m_power(power)
		{}

	};

}

//endbasecorss