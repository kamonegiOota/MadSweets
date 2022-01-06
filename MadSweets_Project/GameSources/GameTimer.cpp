
/*!
@file GameTimer.cpp
@brief GameTimer�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "GameTimer.h"

#include "DebugObject.h"

namespace basecross {

	//�p�����[�^--------------------------------------------------------------------------

	GameTimer::Parametor::Parametor(float intervalTime, const std::function<void()>& func)
		:intervalTime(intervalTime), endFunc(func)
	{}

	void GameTimer::Parametor::EndTimer(bool isEndFunc) {
		if (isEndFunc && endFunc) {
			endFunc();
		}

		endFunc = nullptr;
	}

	//-------------------------------------------------------------------------------------


	GameTimer::GameTimer(const float& intervalTime, const std::function<void()>& func)
		:GameTimer(Parametor(intervalTime, func))
	{}

	GameTimer::GameTimer(const Parametor& param)
		:m_param(param)
	{}

	bool GameTimer::UpdateTimer(const float& countSpeed) {
		if (IsTimeUp()) {  //�o�ߎ��Ԃ��߂��Ă�������Z���Ȃ��B
			return true;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		m_param.elapsedTime += countSpeed * delta;

		if (IsTimeUp()) {
			m_param.EndTimer();
		}

		return IsTimeUp();
	}

}

//endbasecross