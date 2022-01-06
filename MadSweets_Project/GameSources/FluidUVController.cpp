/*!
@file FluidUVController.cpp
@brief FluidUVControllerのクラス実体
担当：丸山裕喜
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
		const float& speed = m_param.elapsedSpeed;
		const float& decelerationSpeed = m_param.decelerationSpeed;
		const Vec2& direct = m_param.direct;
		auto delta = App::GetApp()->GetElapsedTime();

		auto obj = GetGameObject();
		auto rectTrans = obj->GetComponent<RectTransform>();

		auto size = Vec2(rectTrans->GetWidth(), rectTrans->GetHeight());
		size += m_param.offsetElapsed;
		rectTrans->SetRectSize(size.x, size.y);

		m_param.offsetElapsed += direct * speed * delta;
		m_param.elapsedSpeed += -decelerationSpeed * delta;
		
		const Vec2& offsetElpased = m_param.offsetElapsed;
		if (offsetElpased.x < 0 || offsetElpased.y < 0) { //offsetがマイナスになったら処理を終了(逆走するため)
			SetUpdateActive(false);
		}
	}

	void FluidUVController::FluidStart() {
		SetUpdateActive(true);
		m_param.elapsedSpeed = m_param.speed;
	}
}

//endbasecross