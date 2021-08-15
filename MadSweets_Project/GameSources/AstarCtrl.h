/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/
#pragma once

#include "GraphAstar.h"

namespace basecross {

	class AstarCtrl : public Component
	{
		GraphAstar m_astar;

		float m_speed;

		Vec3 CalucMoveVec();

	public:
		AstarCtrl(const std::shared_ptr<GameObject>& objPtr,
			const GraphAstar& astar
		):
			Component(objPtr),
			m_astar(astar),
			m_speed(3.0f)
		{}

		void OnCreate() override;
		void OnUpdate() override{}
		void OnDraw() override {}

		void UpdateMove();
		void UpdateVelocityMove(const float& maxSpeedd, const float& nearRange = 3.0f);

		//アクセッサ-------------------------------------------------------------
		void SearchAstarStart(const std::shared_ptr<GameObject>& target, const bool isCreateNode = false);
		void SearchAstarStart(const Vec3& targetPos, const bool isCreateNode = false);
		
		/// <summary>
		/// ターゲットの行先を予測してノードを選択する関数
		/// </summary>
		/// <param name="target"></param>
		void SearchAstarForecastStart(const std::shared_ptr<GameObject>& target);

		//逃げ出すときのルート計算
		void SearchAstarEscapeStart(const std::shared_ptr<GameObject>& target);
		//逃げているときのルート計算
		void SearchAstarEscapeNextRoute(const std::shared_ptr<GameObject>& target);

		//ノードの追記
		int AddNode(const Vec3& position,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

		//ノードの削除
		void RemoveNode(const int& index);

		Vec3 GetCalucNodePos(){
			return m_astar.CalucTargetNode(GetGameObject());
		}

		bool IsRouteEnd() const {
			return m_astar.IsRouteEnd();
		}

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}
	};

}

//endbasecross