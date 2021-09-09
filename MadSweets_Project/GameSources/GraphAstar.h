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
		SparseGraph<NavGraphNode, GraphEdge> m_graph;  //グラフデータ
		/// <summary>
		/// ヒュースリック計算をしてくれるクラス
		/// </summary>
		Heuristic m_heuristic;  //ヒュースリックの数値を計算する。

		std::map<int,std::vector<AstarExpectData>> m_expectDatas;  //計測した期待値のデータを計測

		std::vector<AstarExpectData> m_shortRoutes;  //最短経路を格納した配列。
		int m_routeIndex = 0;   //現在どのノードを目標としているかを判断するインデックス。
		bool m_isRouteEnd = true;  //ルートの最後に来たかどうか？
		
	public:

		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph)//, m_countIndex(0)
		{}

		/// <summary>
		/// 最短ノードの中で今欲しいノードの場所を取得する。
		/// </summary>
		/// <param name="objPtr">現在この処理を行っているオブジェクト</param>
		/// <returns>現在向かうべきノードのポジション</returns>
		Vec3 CalucTargetNode(const std::shared_ptr<GameObject>& objPtr);
		
		/// <summary>
		/// 自分ノードとエッジから、どのルートが一番近いか検索
		/// </summary>
		/// <param name="self">開始のオブジェクト</param>
		/// <param name="target">ターゲットとなるオブジェクト</param>
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos);
		void SearchAstarStart(const Vec3& selfPos, const Vec3& targetPos);

	private:
		//実際の処理の開始
		void SearchAstarStart(const NavGraphNode& selfNearNode, const NavGraphNode& targetNearNode);

		//前のノードの情報を取得する。
		const NavGraphNode* GetBeforeNode() const;

		/// <summary>
		/// Astarのループ計算が終了すべきかを判断する。
		/// </summary>
		/// <returns></returns>
		bool IsAstarEnd();
		/// <summary>
		/// 被ったルートがある場合にtrueを返す。(被りがある場合はルートがループする可能性があるため)
		/// </summary>
		/// <param name="shortRoute">新しく計算した最短ルート</param>
		/// <returns>被りがあるならtrue</returns>
		bool IsRouteLoop(const AstarExpectData& shortRoute);
		/// <summary>
		/// 求めた距離が本当に最短かどうかを判断する。
		/// </summary>
		/// <param name="shortRoute">新しいルート</param>
		/// <returns>最短ルートならtrue</returns>
		bool IsShortRoute(const AstarExpectData& shortRoute);
		/// <summary>
		/// 前のノードから今回の最短ルートが繋がっている場合は、戻った方が最短の可能性が高い。それを判断
		/// </summary>
		/// <param name="newShortRoute">新しいルート</param>
		/// <returns>戻った方が最短ならtrue</returns>
		bool IsBackShort(const AstarExpectData& newShortRoute);

		void ResetAstar();  //情報をリセットするときの関数
		void RemoveData(const AstarExpectData& data); //データのリムーブ
		void BackShortRoute(); //一旦前のルートに戻る。

		/// <summary>
		/// 仮で最短ルートを確定する処理
		/// </summary>
		/// <param name="newRoute">新規ルート</param>
		void NextProcess(const AstarExpectData& newRoute);
		/// <summary>
		/// 最短ルートでないと判断し、前のノードに戻る処理
		/// </summary>
		/// <param name="shortRoute">現在最短と思われているルート</param>
		void BackProcess(const AstarExpectData& shortRoute);

		/// <summary>
		/// ループして探索経路を測る。
		/// </summary>
		/// <param name="initialNode">初期スタートノード</param>
		void LoopSearchAstar(const NavGraphNode& initialNode);

		/// <summary>
		/// 隣接ノードの距離とヒューリスティック距離の合計を測り、そのデータを返す。
		/// </summary>
		/// <param name="node">基準となるノード(スタート地点)</param>
		/// <returns>計算された配列を返す</returns>
		std::vector<AstarExpectData> CalucNearNodeExpectData(const NavGraphNode& node);

		/// <summary>
		/// 隣接ノードの距離を測る
		/// </summary>
		/// <param name="fromNode">開始のノード</param>
		/// <param name="toNode">対象のノード</param>
		/// <returns>隣接ノードの距離</returns>
		float CalucNearNodeRange(const NavGraphNode& fromNode, const NavGraphNode& toNode);

		/// <summary>
		/// 計測した隣接ノードの期待値の中で,一番小さい数のノードを引き抜く。
		/// </summary>
		/// <param name="datas">計算に使うデータ群</param>
		/// <returns>期待値が一番小さいデータ</returns>
		AstarExpectData CalucMinRangeNode(const std::vector<AstarExpectData>& datas);

		/// <summary>
		/// 最終調整
		/// </summary>
		void LastAdjust(const NavGraphNode& initialNode);

		//アクセッサ-------------------------------------------------------
	public:

		/// <summary>
		/// 検索したルートの最後まで来たらtrue
		/// </summary>
		/// <returns>最後まで来たらtrue</returns>
		bool IsRouteEnd() const {
			return m_isRouteEnd;
		}

		const SparseGraph<NavGraphNode, GraphEdge>& GetGraph() const {
			return m_graph;
		}

		/// <summary>
		/// ノードの追加
		/// </summary>
		/// <param name="position">追加したいノードのポジション</param>
		/// <returns>追加したノードのインデックス</returns>
		int AddNode(const Vec3& position);
		/// <summary>
		/// ノードの追加
		/// </summary>
		/// <param name="position">追加したいノードのポジション</param>
		/// <param name="obstacleObjs">障害物対象のオブジェクト</param>
		/// <param name="excluteObjs">障害物から除く対象のオブジェクト</param>
		/// <returns>追加したノードのインデックス</returns>
		int AddNode(const Vec3& position,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);
		/// <summary>
		/// ノードの削除
		/// </summary>
		/// <param name="index">削除したいノードのインデックス</param>
		void RemoveNode(const int& index);

		/// <summary>
		/// エッジの追加
		/// </summary>
		/// <param name="obstacleObjs">障害物判定のオブジェクト</param>
		/// <param name="excluteObjs">障害物の中でも特別に外す処理</param>
		void AddEdges(const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);
	};

}

//endbasecross