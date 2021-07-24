
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "Velocity.h"

namespace basecross {

	void Velocity::Move() {
		if (m_direct == Vec3(0.0f)) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = transform->GetPosition();
		pos += m_direct.GetNormalized() * m_speed * delta;
		transform->SetPosition(pos);
	}

	void Velocity::OnUpdate() {
		Move();
	}

}

//endbasecross