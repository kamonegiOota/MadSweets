
/*!
@file BaseUseVelocity.h
@brief BaseUseVelocityNX
SFÛRTì
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// Velocityðg¤êÉÅáÀKvÈîñ
	/// </summary>
	class BaseUseVelocity
	{
		float m_maxSpeed = 3.0f;
		float m_nearRange = 1.0f;  //ß­Æ»f·é£

	protected:
		virtual void SetVelocityMaxSpeed(const float& speed) final {
			m_maxSpeed = speed;
		}
		virtual float GetVelocityMaxSpeed() const final{
			return m_maxSpeed;
		}

		//s®Éß­Æ»f·é£
		virtual void SetArriveNearRange(const float& range) final{
			m_nearRange = range;
		}
		virtual float GetArriveNearRange() const final{
			return m_nearRange;
		}
	};

}

//endbasecorss