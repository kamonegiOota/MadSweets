
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
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

			if (param->isEnd) {  //終了していたらcontinue
				continue;
			}

			//時間の計測と終了判定監視
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