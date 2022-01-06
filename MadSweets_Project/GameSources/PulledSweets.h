
/*!
@file PulledSweets.h
@brief PulledSweetsクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "EatenComponent.h"

namespace basecross {

	/// <summary>
	/// スウィーツに引っ張られる処理
	/// </summary>
	class PulledSweets : public Component
	{
		float m_speed;  //吸い寄せられるスピード
		float m_range;  //吸い寄せられる範囲

		/// <summary>
		/// 寄せられる方向を計算して返す
		/// </summary>
		/// <returns>吸い寄せられる方向</returns>
		Vec3 CalucPulledVec();
		void PulledMove();

	public:

		PulledSweets(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_speed(1.5f),m_range(10.0f)
		{}

		void OnCreate() override;
		void OnStart() override;
		void OnUpdate() override;

		//アクセッサ--------------------------------------------------

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}

		void SetRange(const float& range) {
			m_range = range;
		}
		float GetRange() const {
			return m_range;
		}
	};

}

//endbasecross