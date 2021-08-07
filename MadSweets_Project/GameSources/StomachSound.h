
/*!
@file MyRandom.h
@brief MyRandomクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//腹の音
	class StomachSound : public Component
	{
		float m_time = 5.0f;
		float m_timeElapsed = 0.0f;

		//音の出る確率
		float m_soundProbability = 50.0f;

		void OnSound();
		void TimeMgr();

	public:

		StomachSound(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		//アクセッサ--------------------------------------------------
		void SetTime(const float& time) {
			m_time = time;
		}
		float GetTime() const {
			return m_time;
		}

		void SetSoundProbability(const float& prob) {
			m_soundProbability = prob;
		}
		float GetSoundProbability() const {
			return m_soundProbability;
		}

	};

}

//endbasecross