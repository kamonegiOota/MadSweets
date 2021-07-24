
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Velocity : public Component
	{
		float m_speed = 1.0f;
		Vec3 m_direct = Vec3(0.0f);

		void Move();

	public:

		Velocity(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;


		//アクセッサ-----------------------------------------------------------

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}

		void SetDirect(const Vec3& direct) {
			m_direct = direct;
		}
		Vec3 GetDirect() const {
			return m_direct;
		}

		void AddForce(const Vec3& direct, const float& speed) {
			SetDirect(direct);
			SetSpeed(speed);
		}
	};

}

//endbasecross