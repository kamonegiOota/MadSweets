/*!
@file MyRandom.h
@brief MyRandomクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "EatenComponent.h"

#include "TimerDamage.h"
#include "PulledSweets.h"
#include "StomachSound.h"

namespace basecross {

	enum class WeightState;


	class HungerCompCtrl : public Component
	{
		WeightState m_beforeWeightState;  //前回のステート

		ex_weak_ptr<TimerDamage> m_timerDamage;   //時間経過でダメージを受ける
		ex_weak_ptr<PulledSweets> m_pulledSweets; //お菓子の方向に移動し始める
		ex_weak_ptr<StomachSound> m_stomachSound; //音がなる処理

		/// <summary>
		/// 状態変更時に、関係するコンポーネントのOn,Offを切り替える。
		/// </summary>
		/// <param name="isActive">飢餓状態かどうか</param>
		void ChangeUpdateActive(const bool isActive);

		/// <summary>
		/// 飢餓状態かどうかの監視
		/// </summary>
		void HungerMgr();

	public:
		HungerCompCtrl(const std::shared_ptr<GameObject>& objPtr);

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override;


		//アクセッサ-----------------------------------------------------------
	};

}

//endbasecross