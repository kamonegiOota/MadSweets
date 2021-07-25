
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "Velocity.h"
#include "Mathf.h"
#include "DebugObject.h"

//#include <directxmath.h>

namespace basecross {

	void Velocity::MaxVelocityCheck() {
		auto speed = m_velocity.length();

		speed = maru::Mathf::Clamp(speed, 0.0f ,m_maxSpeed);
		m_velocity = m_velocity.GetNormalized() * speed;
		//DebugObject::m_wss << to_wstring(speed) << endl;
		//DebugObject::sm_isResetDelta = true;
		//m_velocity *= (Mat4x4)XMMatrixRotationAxis(Vec3(1.0f,0.0f,0.0f),XM_PI);
		
	}

	void Velocity::MaxForceCheck() {
		auto force = m_force.length();

		force = maru::Mathf::Clamp(force, 0.0f, m_maxForce);
		m_force = m_force.GetNormalized() * force;
	}

	void Velocity::Move() {
		if (m_velocity == Vec3(0.0f)) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = transform->GetPosition();
		pos += m_velocity * delta;
		transform->SetPosition(pos);
	}

	void Velocity::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_velocity += m_force * delta;

		Move();

		MaxVelocityCheck();
	}

}

//endbasecross