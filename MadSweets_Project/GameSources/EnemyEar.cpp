/*!
@file EnemyEar.cpp
@brief EnemyEarなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyEar.h"

#include "EnState_TargetChase.h"
#include "EnState_CheckSoundPos.h"

#include "I_Ear.h";

namespace basecross {

	bool EnemyEar::IsListenRnage(const Vec3& targetPos) {
		auto toVec = targetPos - transform->GetPosition();

		//聞こえる範囲内にいたらtrueを返す。
		return toVec.length() < m_listenRange ? true : false;
	}

	void EnemyEar::Listen(const Vec3& targetPos) {
		//特定のステートの時は変更できないようにする。
		//敵を直接見ているときは目の前の敵を見るなど
		if (IsListenRnage(targetPos)) {  //聞こえる範囲にいる時
			//ステートマシン変更時
			auto ear = GetGameObject()->GetComponent<I_Ear>(false);
			if (ear) {
				ear->Listen();
			}

			//auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
			//if (enemy) {
			//	enemy->ChangeStateMachine<EnState_CheckSoundPos>(targetPos);
			//}
		}
	}
}

//endbasecross