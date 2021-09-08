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

		//ターゲットから一番近くのノードを検索する。
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target);
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const Vec3& targetPos,
			vector<std::shared_ptr<GameObject>> excluteObjs = vector<std::shared_ptr<GameObject>>());

		//自分のノードから伸びるノードで一番ターゲットに近いノードの選択
		static NavGraphNode SearchMyNodeToTargetNearNode(const GraphAstar& astar, 
			const std::shared_ptr<GameObject>& selfObject,const std::shared_ptr<GameObject>& target);

		//自分のノードからターゲット方向にあるノードを検索
		static NavGraphNode CalucTargetDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);

		//ターゲットから逃げるための方向のノードを検索する
		static NavGraphNode CalucTargetEscapeDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);

		//nodeのインデックスから隣接するエッジの生成する。
		//生成する場合に直接渡されたSparseGraphにAddする。
		template<class NodeClass, class EdgeClass>
		static vector<GraphEdge> CreateAdjacendEdges(SparseGraph<NodeClass, EdgeClass>& graph, const NavGraphNode& newNode,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto nodes = graph.GetNodes();

			vector<GraphEdge> reEdges;
			//for (const auto& node : nodes) {
				for (auto& node : nodes) {
					//障害物がなかったらエッジを追加する。
					if (!maru::MyUtility::IsRayObstacle(newNode.GetPosition(), node.GetPosition(), obstacleObjs, excluteObjs)) {
						//双方向にエッジを生成
						graph.AddEdge(GraphEdge(newNode.GetIndex(), node.GetIndex()));
						graph.AddEdge(GraphEdge(node.GetIndex(), newNode.GetIndex()));
						//どのようなエッジを生成したか返せるように別の配列に入れる。
						reEdges.push_back(GraphEdge(newNode.GetIndex(), node.GetIndex()));
						reEdges.push_back(GraphEdge(node.GetIndex(), newNode.GetIndex()));
					}
				}
			//}

			return reEdges;
		}
	};

}