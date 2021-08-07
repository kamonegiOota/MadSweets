/*!
@file GameManager.cpp
@brief GameManager�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "StomachSound.h"
#include "I_Damaged.h"
#include "MyRandom.h"
#include "MyUtility.h"
#include "EarBase.h"

#include "DebugObject.h"

namespace basecross {

	void StomachSound::OnSound() {
		//�m���v�Z
		auto isSound = maru::MyRandom::RandomProbability(m_soundProbability);
		if (isSound) {
			//�����o���B
			
			//�G�ɒm�点��B
			auto ears = maru::MyUtility::GetComponents<EarBase>();
			for (auto& ear : ears) {
				ear->Listen(transform->GetPosition());
			}
		}
	}

	void StomachSound::TimeMgr() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_timeElapsed += delta;

		if (m_timeElapsed > m_time) {
			m_timeElapsed = 0.0f;
			OnSound();
		}
	}

	void StomachSound::OnCreate() {
		//SetUpdateActive(false);
	}

	void StomachSound::OnUpdate() {
		TimeMgr();
	}

}

//endbasecross