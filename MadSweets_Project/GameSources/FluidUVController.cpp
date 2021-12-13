/*!
@file ScalePop.cpp
@brief ScalePop‚ÌƒNƒ‰ƒXŽÀ‘Ì
’S“–FŠÛŽR—TŠì
*/

#include "stdafx.h"
#include "Project.h"

#include "FluidUVController.h"

namespace basecross {

	void FluidUVController::OnCreate() {

	}

	void FluidUVController::OnUpdate() {
		FluidUpdate();
	}

	void FluidUVController::FluidUpdate() {
		const float& speed = m_param.speed;
		const float& decelerationSpeed = m_param.decelerationSpeed;
		const Vec2& direct = m_param.direct;
		auto delta = App::GetApp()->GetElapsedTime();

		auto obj = GetGameObject();
		auto rectTrans = obj->GetComponent<RectTransform>();

		auto size = Vec2(rectTrans->GetWidth(), rectTrans->GetHeight());
		size += m_param.offsetElapsed;
		rectTrans->SetRectSize(size.x, size.y);

		m_param.offsetElapsed += direct * speed * delta;
		m_param.speed += -decelerationSpeed * delta;
		
		if (m_param.speed < 0) {
			SetUpdateActive(false);
		}
	}
}

//endbasecross