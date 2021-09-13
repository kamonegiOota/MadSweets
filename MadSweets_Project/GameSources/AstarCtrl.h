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
		std::shared_ptr<GraphAstar> m_astar;

		float m_speed;

		void Rotation(const Vec3& direct);
		Vec3 CalucMoveVec();

	public:
		AstarCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<GraphAstar>& astar
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

		/// <summary>
		/// Astarのルート計算のスタート
		/// </summary>
		/// <param name="target">ルート目的のポインタ</param>
		void SearchAstarStart(const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const Vec3& targetPos);
		
		/// <summary>
		/// ターゲットの行先を予測してノードを選択する関数
		/// </summary>
		/// <param name="target"></param>
		//void SearchAstarForecastStart(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// 逃げ出すときのルート計算
		/// </summary>
		/// <param name="target">逃げ出すターゲット</param>
		void SearchAstarEscapeStart(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// 逃げているときのルート計算(二回目以降)
		/// </summary>
		/// <param name="target">逃げ出す対象</param>
		void SearchAstarEscapeNextRoute(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// ノードの追記
		/// </summary>
		/// <param name="position">ノードのポジション</param>
		/// <param name="obstacleObjs">障害物のオブジェクト配列</param>
		/// <param name="excluteObjs">障害物から省くオブジェクト配列</param>
		/// <returns>追加したノードのインデックス</returns>
		int AddNode(const Vec3& position,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

		/// <summary>
		/// ノードの削除
		/// </summary>
		/// <param name="index">削除したいノードのインデックス</param>
		void RemoveNode(const int& index);

		/// <summary>
		/// ターゲットから一番近いノードを見つけてポジションを取得
		/// </summary>
		/// <param name="target">ターゲットのポインタ</param>
		/// <returns>ノードのポジション</returns>
		Vec3 CalucTargetNearNodePosition(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// 自分のノードから一番ターゲットに近いノードを取得
		/// </summary>
		/// <param name="target">ターゲットのポインタ</param>
		/// <returns>ターゲットに近いノード</returns>
		NavGraphNode CalucMyNodeToTargetNearNode(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// 現在向かうノードのポジションを返す
		/// </summary>
		/// <returns>ノードのポジション</returns>
		Vec3 GetCalucNodePos(){
			return m_astar->CalucTargetNode(GetGameObject());
		}

		bool IsRouteEnd() const {
			return m_astar->IsRouteEnd();
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