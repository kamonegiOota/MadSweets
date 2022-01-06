/*!
@file UtilityAstar.h
@brief UtilityAstarなど
担当者：丸山 裕喜
*/

#pragma once

#include "NavGraphNode.h"
#include "GraphAstar.h"

namespace basecross {

	/// <summary>
	/// Astarでよく使う計算をまとめたクラス
	/// GraphAstarが余りにも関数が増えたたため、計算系を分けるために生成
	/// </summary>
	class UtilityAstar
	{
	public:

		/// <summary>
		/// ターゲットから一番近くのノードを検索する。
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="target">ターゲット</param>
		/// <returns>ターゲットの一番近くのノード</returns>
		static std::shared_ptr<NavGraphNode> SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ターゲットから一番近くのノードを検索する。
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="targetPos">ターゲットのポジション</param>
		/// <param name="excluteObjs">Rayの対象外にするオブジェクト群</param>
		/// <returns>ターゲットから一番近いノード</returns>
		static std::shared_ptr<NavGraphNode> SearchNearNode(const GraphAstar& astar, const Vec3& targetPos,
			vector<std::shared_ptr<GameObject>> excluteObjs = vector<std::shared_ptr<GameObject>>());

		/// <summary>
		/// 自分のノードから伸びるノードで一番ターゲットに近いノードの選択
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="selfObject">自分自身</param>
		/// <param name="target">ターゲット</param>
		/// <returns>一番近いノード</returns>
		static std::shared_ptr<NavGraphNode> SearchMyNodeToTargetNearNode(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObject,const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// 自分のノードからターゲット方向にあるノードを検索
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="startNode">開始ノード</param>
		/// <param name="targetPos">ターゲットのポジション</param>
		/// <returns>ターゲット方向のノード</returns>
		static std::shared_ptr<NavGraphNode> CalucTargetDirectNode(const GraphAstar& astar,
			const std::shared_ptr<NavGraphNode>& startNode,
			const Vec3& targetPos);

		/// <summary>
		/// ターゲットから逃げるための方向のノードを検索する
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="startNode">開始ノード</param>
		/// <param name="targetPos">ターゲットのポジション</param>
		/// <returns>ターゲット方向のノード</returns>
		static std::shared_ptr<NavGraphNode> CalucTargetEscapeDirectNode(const GraphAstar& astar,
			const std::shared_ptr<NavGraphNode>& startNode,
			const Vec3& targetPos);

		/// <summary>
		/// nodeのインデックスから隣接するエッジの生成する。
		/// 生成する場合に直接渡されたSparseGraphにAddする。
		/// </summary>
		/// <param name="graph">Graphの参照</param>
		/// <param name="newNode">新規ノード</param>
		/// <param name="obstacleObjs">障害物のオブジェクト配列</param>
		/// <param name="excluteObjs">障害物から省くオブジェクト配列</param>
		/// <returns>生成されたエッジの配列</returns>
		template<class NodeClass, class EdgeClass>
		static vector<GraphEdge> CreateAdjacendEdges(std::shared_ptr<SparseGraph<NodeClass, EdgeClass>>& graph, const std::shared_ptr<NavGraphNode>& newNode,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto nodes = graph->GetNodes();

			vector<GraphEdge> reEdges;
			//for (const auto& node : nodes) {
				for (auto& node : nodes) {
					//障害物がなかったらエッジを追加する。
					if (!maru::MyUtility::IsRayObstacle(newNode->GetPosition(), node->GetPosition(), obstacleObjs, excluteObjs)) {
						//双方向にエッジを生成
						graph->AddEdge(GraphEdge(newNode->GetIndex(), node->GetIndex()));
						graph->AddEdge(GraphEdge(node->GetIndex(), newNode->GetIndex()));
						//どのようなエッジを生成したか返せるように別の配列に入れる。
						reEdges.push_back(GraphEdge(newNode->GetIndex(), node->GetIndex()));
						reEdges.push_back(GraphEdge(node->GetIndex(), newNode->GetIndex()));
					}
				}
			//}

			return reEdges;
		}
	};

}