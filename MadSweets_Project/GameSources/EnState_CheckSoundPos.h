/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class EnState_CheckSoundPos : public maru::StateMachine<BaseEnemy>
	{
		Vec3 m_targetPos;

	public:

		EnState_CheckSoundPos(const std::shared_ptr<BaseEnemy>& owner,
			const Vec3& targetPos
		) :
			maru::StateMachine<BaseEnemy>(owner),
			m_targetPos(targetPos)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecross