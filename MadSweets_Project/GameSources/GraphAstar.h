/*!
@file GraphAstar.h
@brief GraphAstarなど
担当者：丸山 裕喜
*/

#pragma once
#include "stdafx.h"

#include "SparseGraph.h"
#include "Heuristic.h"

//#include "NavGraphNode.h"
#include "GraphEdge.h"

namespace basecross {

	/// <summary>
	/// Astarにおける、期待値の計算に用いる構造体
	/// </summary>
	struct AstarExpectData {
		NavGraphNode node;
		NavGraphNode nextNode;
		float range;
		float heuristic;

		AstarExpectData():
			AstarExpectData(NavGraphNode(),NavGraphNode(),0.0f,0.0f)
		{}

		AstarExpectData(const NavGraphNode& node, const NavGraphNode& nextNode,
			const float& range, const float& heuristic
		) :
			node(node),nextNode(nextNode),
			range(range),heuristic(heuristic)
		{}

		float GetSumRange() const {
			return range + heuristic;
		}
	};

	class GraphAstar
	{
		/// <summary>
		/// ノードとエッジを管理する
		/// </summary>
		SparseGraph<NavGraphNode, GraphEdge> m_graph;
		/// <summary>
		/// ヒュースリック計算をしてくれるクラス
		/// </summary>
		Heuristic m_heuristic;

		std::vector<std::vector<AstarExpectData>> m_expectDatas;  //計測した期待値のデータを計測
		//int m_countIndex;  //現在探索計算が何回目かを判断する。

		std::vector<AstarExpectData> m_shortRoutes;  //最短経路を格納した配列。
		int m_routeIndex = 0;   //現在どのノードを目標としているかを判断するインデックス。
		bool m_isRouteEnd = true;

		bool m_isCreateNewData = true;
		bool m_isReturnPhase = false;  //一度戻っている状態かどうか

		const NavGraphNode *GetBeforeNode() const;  //前のノードの情報を取得する。
		void RemoveData(const AstarExpectData& data);
		void BackShortRoute(); //一旦前のルートに戻る。
		bool IsAstarEnd();  //Astarの終了を判断

		//目的ノードの設定
		//ターゲットから一番近くのノードを検索する。
		NavGraphNode SearchNearNode(const std::shared_ptr<GameObject>& target);
		NavGraphNode SearchNearNode(const Vec3& targetPos);
		
	public:
		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph)//, m_countIndex(0)
		{}
		
		//自分ノードとエッジから、どのルートが一番近いか検索
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos);

		//ターゲットの行先を予測してその方向ノードに向かうルートを構築する処理(Forecast == 予測、予想)
		void SearchAstarForecastStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);

		//最短ノードの中で今欲しいノードの場所を取得する。
		Vec3 CalucTargetNode(const std::shared_ptr<GameObject>& objPtr);

		//アクセッサ-------------------------------------------------------
		
		//検索したルートの最後まで来たらtrue
		bool IsRouteEnd() const {
			return m_isRouteEnd;
		}

	private:

		//進む時の処理
		void NextProcess(const AstarExpectData& newRoute, const vector<AstarExpectData>& newDatas);

		//戻る時の処理
		void BackProcess(const AstarExpectData& shortRoute);

		//ループして探索経路を測る。
		void LoopSearchAstar(const NavGraphNode& stdNode);

		//隣接ノードの距離とヒューリスティック距離の合計を測り、そのデータを返す。
		std::vector<AstarExpectData> CalucNearNodeExpectData(const NavGraphNode& node);

		//隣接ノードの距離を測る
		float CalucNearNodeRange(const NavGraphNode& fromNode, const NavGraphNode& toNode);

		//計測した隣接ノードの期待値の中で,一番小さい数のノードを引き抜く。
		AstarExpectData CalucMinRangeNode(const std::vector<AstarExpectData>& datas);

		//求めた距離が本当に最短かどうかを判断する。
		bool IsShortRoute(const AstarExpectData& data);

		//前のノードから今回の最短ルートが繋がっている場合は、戻った方が最短の可能性が高い。それを判断
		bool IsBackShort(const AstarExpectData& newShortRoute);
	};

}

//endbasecross