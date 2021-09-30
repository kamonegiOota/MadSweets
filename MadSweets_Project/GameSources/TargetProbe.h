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
		//std::shared_ptr<GameObject> m_target;  //捜索対象
		std::shared_ptr<GameObject> m_checkHideObj;  //チェックしている隠れるオブジェクト
		int m_newNodeIndex = 0;
		
		std::function<void(TargetProbe&)> m_moveFunc;

		//何回プレイヤーの捜索をするか？
		int m_numPorb = 1;
		int m_probCount = 0;  //実際に捜索した回数。

		float m_searchRange = 10.0f;  //探索する範囲
		float m_lostSeekTime = 3.0f;  //ターゲットとの間に障害物がある場合次のルート検索にうつるタイム。

		void AddNode(const Vec3& position);
		void RemoveNode();

		/// <summary>
		/// Astarに捜索先をセットする。
		/// </summary>
		void SetAstarRondomHideObject();

		/// <summary>
		/// 隠れるオブジェクトを調べる処理。
		/// </summary>
		void InvestigateHideObj();
		void RouteEnd();

		/// <summary>
		/// 隠れるオブジェクトを探すアニメーションの再生の終了を待つ
		/// </summary>
		void WaitInvestigateAnimationUpdateEnd();
		void TargetMove();
		void AstarMove();
		void Rotation(const Vec3& direct);

		void ResetProbe();
		/// <summary>
		/// HideObjectのColliderのOn,Offの切り替え(覗くときに一時的にoffにする。)
		/// </summary>
		/// <param name="isUpdate">Onならtrue</param>
		void SetHideObjCollisionUpdate(const bool isUpdate);

		void ChangeEndProbeState();  //ステートマシン変更時に生成

		void LostTimerStart();
		void LostTimerCancel();

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/// <summary>
		/// 捜索開始
		/// </summary>
		void StartProb();  
		/// <summary>
		/// 捜索開始
		/// </summary>
		/// <param name="target">捜索ターゲット</param>
		void StartProb(const shared_ptr<GameObject>& target);

		/// <summary>
		/// 探すアニメーションが終了したときの処理
		/// </summary>
		void EndInvestigateHideAnimation();

		//アクセッサ--------------------------------------------------------

		//void SetTarget(const std::shared_ptr<GameObject>& target) {
		//	m_target = target;
		//}
		//std::shared_ptr<GameObject> GetTarget() const {
		//	return m_target;
		//}

		void SetSearchRange(const float& range) {
			m_searchRange = range;
		}
		float GetSearchRange() const {
			return m_searchRange;
		}

		/// <summary>
		/// このステートを抜け出すときに呼ぶ関数
		/// </summary>
		void ExitProbState();
	};

}

//endbasecorss