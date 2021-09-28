/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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

		//��������͈͓��ɂ�����true��Ԃ��B
		return toVec.length() < m_listenRange ? true : false;
	}

	void EnemyEar::Listen(const Vec3& targetPos) {
		//����̃X�e�[�g�̎��͕ύX�ł��Ȃ��悤�ɂ���B
		//�G�𒼐ڌ��Ă���Ƃ��͖ڂ̑O�̓G������Ȃ�
		if (IsListenRnage(targetPos)) {  //��������͈͂ɂ��鎞
			//�X�e�[�g�}�V���ύX��
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