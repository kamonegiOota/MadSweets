
/*!
@file FluidUVController.h
@brief FluidUVControllerヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//液体動作をUVにさせるための処理
	class FluidUVController : public Component
	{
		struct Parametor {
			float speed = 1.0f;
			float elapsedSpeed = speed;
			float decelerationSpeed = 0.5f;  //減速スピード
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

		//液体動作
		void FluidUpdate();

		//アクセッサ------------------------------------------------------

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