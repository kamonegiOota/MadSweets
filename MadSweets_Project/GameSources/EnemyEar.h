/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EarBase.h"
#include "AstarCtrl.h"

namespace basecross {

	class EnemyEar : public EarBase
	{
		float m_listenRange;  //��������͈�

		bool IsListenRnage(const Vec3& targetPos);  //��������͈͂��ǂ����𔻒f����B

	public:
		EnemyEar(const std::shared_ptr<GameObject>& objPtr)
			:EarBase(objPtr),m_listenRange(10.0f)
		{}

		void OnCreate() override{}
		void OnUpdate() override{}

		void Listen(const Vec3& targetPos) override;
		
		//�A�N�Z�b�T--------------------------------------------------------

		void SetListenRange(const float& range) {
			m_listenRange = range;
		}
		float GetListenRange() const {
			return m_listenRange;
		}

	};

}

//endbasecross