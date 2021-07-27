/*!
@file PlowlingMove.h
@brief PlowlingMove
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EarBase.h"
#include "AstarCtrl.h"

namespace basecross {

	class EnemyEar : public EarBase
	{
		ex_weak_ptr<AstarCtrl> m_astar;

	public:
		EnemyEar(const std::shared_ptr<GameObject>& objPtr)
			:EarBase(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

		void SoundListen(const std::shared_ptr<GameObject>& target);  //‰¹‚ğ•·‚­ˆ—
		void SoundListen(const Vec3& targetPos);
	};

}

//endbasecross