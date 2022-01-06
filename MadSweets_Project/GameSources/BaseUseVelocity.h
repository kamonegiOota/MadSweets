
/*!
@file BaseUseVelocity.h
@brief BaseUseVelocity�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// Velocity���g���ꍇ�ɍŒ���K�v�ȏ��
	/// </summary>
	class BaseUseVelocity
	{
		float m_maxSpeed = 3.0f;
		float m_nearRange = 1.0f;  //�߂��Ɣ��f���鋗��

	protected:
		virtual void SetVelocityMaxSpeed(const float& speed) final {
			m_maxSpeed = speed;
		}
		virtual float GetVelocityMaxSpeed() const final{
			return m_maxSpeed;
		}

		//�����s�����ɋ߂��Ɣ��f���鋗��
		virtual void SetArriveNearRange(const float& range) final{
			m_nearRange = range;
		}
		virtual float GetArriveNearRange() const final{
			return m_nearRange;
		}
	};

}

//endbasecorss