
/*!
@file BaseUseVelocity.h
@brief BaseUseVelocityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// Velocityを使う場合に最低限必要な情報
	/// </summary>
	class BaseUseVelocity
	{
		float m_maxSpeed = 3.0f;
		float m_nearRange = 1.0f;  //近くと判断する距離

	protected:
		virtual void SetVelocityMaxSpeed(const float& speed) final {
			m_maxSpeed = speed;
		}
		virtual float GetVelocityMaxSpeed() const final{
			return m_maxSpeed;
		}

		//到着行動時に近くと判断する距離
		virtual void SetArriveNearRange(const float& range) final{
			m_nearRange = range;
		}
		virtual float GetArriveNearRange() const final{
			return m_nearRange;
		}
	};

}

//endbasecorss