/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// ターゲットを捜索するコンポーネント
	/// </summary>
	class TargetProbe : public Component, public BaseUseVelocity
	{
		std::shared_ptr<GameObject> m_target;  //捜索対象
		std::shared_ptr<GameObject> m_checkHideObj;  //チェックしている隠れるオブジェクト
		int m_newNodeIndex = 0;
		
		std::function<void(TargetProbe&)> m_moveFunc;

		//何回プレイヤーの捜索をするか？
		int m_numPorb = 1;
		int m_probCount = 0;  //実際に捜索した回数。

		float m_searchRange = 3.0f;  //探索する範囲

		//Nodeの追加
		void AddNode(const Vec3& position);
		void RemoveNode();

		//Astarに捜索先をセットする。
		void SetAstarRondomHideObject();

		void InvestigateHideObj();  //隠れるオブジェクトを調べる処理。
		void RouteEnd();

		//隠れるオブジェクトを探すアニメーションの再生の終了を待つ
		void WaitInvestigateAnimationUpdateEnd();
		void TargetMove();
		void AstarMove();

		void ResetProbe();
		void SetHideObjCollisionUpdate(const bool isUpdate);

		template<class T, class... Ts>
		void ChangeState(Ts&&... params) {
			//m_probCount = 0;
			auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
			if (enemy) {
				enemy->ChangeStateMachine<T>(params...);  //見失った状態にする。
			}
		}

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartProb();  //捜索開始
		void StartProb(const shared_ptr<GameObject>& target);  //捜索開始

		//探すアニメーションが終了したときの処理
		void EndInvestigateHideAnimation();

		//アクセッサ--------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

		void ExitProbState();
	};

}

//endbasecorss