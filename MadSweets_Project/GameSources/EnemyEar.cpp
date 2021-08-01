/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyEar.h"

#include "EnState_TargetChase.h"
#include "EnState_CheckSoundPos.h"

namespace basecross {

	bool EnemyEar::IsListenRnage(const Vec3& targetPos) {
		auto toVec = targetPos - transform->GetPosition();

		//��������͈͓��ɂ�����true��Ԃ��B
		return toVec.length() < m_listenRange ? true : false;
	}

	void EnemyEar::SoundListen(const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		SoundListen(targetPos);
	}

	void EnemyEar::SoundListen(const Vec3& targetPos) {
		
		//����̃X�e�[�g�̎��͕ύX�ł��Ȃ��悤�ɂ���B
		//�G�𒼐ڌ��Ă���Ƃ��͖ڂ̑O�̓G������Ȃ�

		if (IsListenRnage(targetPos)) {  //��������͈͂ɂ��鎞
			auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
			if (enemy) {
				enemy->ChangeStateMachine<EnState_CheckSoundPos>(targetPos);
			}
		}
	}
}

//endbasecross