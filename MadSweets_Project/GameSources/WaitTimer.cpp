
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "WaitTimer.h"

#include "DebugObject.h"

namespace basecross {

	void WaitTimer::TimerUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		for (pair<type_index, std::shared_ptr<WaitTimerParametor>> paramPair : m_params) {
			auto& param = paramPair.second;

			if (param->isEnd) {  //�I�����Ă�����continue
				continue;
			}

			//���Ԃ̌v���ƏI������Ď�
			param->timeElapsed += delta * param->countSpeed;
			if (param->timeElapsed >= param->time) {
				param->EndTimer();
			}
		}
	}

	void WaitTimer::OnUpdate() {

		TimerUpdate();
	}

	

}

//endbasecross