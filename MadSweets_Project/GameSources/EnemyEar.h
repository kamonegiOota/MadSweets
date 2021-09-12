/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EarBase.h"
#include "AstarCtrl.h"

namespace basecross {

	class EnemyEar : public EarBase
	{
		float m_listenRange;  //聞こえる範囲

		bool IsListenRnage(const Vec3& targetPos);  //聞こえる範囲かどうかを判断する。

	public:
		EnemyEar(const std::shared_ptr<GameObject>& objPtr)
			:EarBase(objPtr),m_listenRange(10.0f)
		{}

		void OnCreate() override{}
		void OnUpdate() override{}

		void Listen(const Vec3& targetPos) override;
		
		//アクセッサ--------------------------------------------------------

		void SetListenRange(const float& range) {
			m_listenRange = range;
		}
		float GetListenRange() const {
			return m_listenRange;
		}

	};

}

//endbasecross