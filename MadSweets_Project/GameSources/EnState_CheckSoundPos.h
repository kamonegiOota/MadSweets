/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"
#include "EnemyStateNodeBase.h"

namespace basecross {

	class EnState_CheckSoundPos : public EnemyStateNodeBase<BaseEnemy>
	{
		Vec3 m_targetPos;

	public:

		EnState_CheckSoundPos(const std::shared_ptr<BaseEnemy>& owner,
			const Vec3& targetPos
		) :
			EnemyStateNodeBase<BaseEnemy>(owner),
			m_targetPos(targetPos)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecross