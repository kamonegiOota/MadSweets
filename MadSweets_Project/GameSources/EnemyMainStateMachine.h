/*!
@file EnemyMainStateMachine.h
@brief EnemyMainStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EdgeBase.h"
#include "GraphBase.h"

#include "DebugObject.h"

namespace basecross {

	/// <summary>
	/// EnemyStateMachine用のテンプレートクラス。
	/// </summary>
	/// <typeparam name="NodeType">使用するノード</typeparam>
	/// <typeparam name="EnumType">使用する列挙体</typeparam>
	/// <typeparam name="TransitionStructMember">遷移条件用の構造体メンバー</typeparam>
	template<class node_type, class EnumType, class TransitionStructMember>
	class EnemyMainStateMachine
	{
		//切替先候補のパラメータ
		struct TransitionCandidateParametor
		{
			EnumType type;
			int priority;

			TransitionCandidateParametor(const EnumType type)
				:TransitionCandidateParametor(type)
			{}

			TransitionCandidateParametor(const EnumType type, const int priority)
				:type(type), priority(priority)
			{ }
		};

	public:
		//外部からEnumを使う時用にEnumTypeをpublicにする。
		using StateEnum = EnumType;
		using EdgeType = EdgeBase<EnumType, TransitionStructMember>;

	private:
		//usingディレクティブ
		using GraphType = GraphBase<node_type, EnumType, TransitionStructMember>;

		using NodeType = NodeBase<node_type>;
		using NodeMap = std::map<EnumType, NodeType>;
		using EdgeVector = std::vector<std::shared_ptr<EdgeType>>;
		using EdgeVectorMap = std::map<EnumType, EdgeVector>;

		//privateメンバ変数------------------------

		std::shared_ptr<GraphType> m_graph;  //グラフの情報
		TransitionStructMember m_transitionStruct; //遷移条件に利用する構造体

		std::map<EnumType ,std::function<void()>> m_changeOnceFuncs;  //切り替え時に一度だけ呼ぶファンクション

		std::vector<TransitionCandidateParametor> m_transitionCandidates;  //遷移先候補パラメータ群

		//privateメンバ関数-------------------------

		//ステートの変更
		void ChangeState(const EnumType type) {
			//切り替え時に一度だけ呼ぶファンクション
			int i = 0;
			if (m_changeOnceFuncs.count(type)) {
				m_changeOnceFuncs[type]();
			}
			m_changeOnceFuncs.clear();

			m_graph->ChangeState(type);
		}

	public:
		EnemyMainStateMachine() 
			:m_graph(std::make_shared<GraphType>())
		{}

		//現在使っているノードのタイプ
		EnumType GetNowType() const {
			return m_graph->GetNowType();
		}

		//現在使うノードの取得
		std::shared_ptr<NodeType> GetNowNode() const {
			return m_graph->GetNowNode();
		}
		
		//指定したノードの取得
		std::shared_ptr<NodeType> GetNode(const EnumType type) const {
			return m_graph->GetNode(type);
		}

		//ノードの配列を取得
		NodeMap GetNodes() const {
			return m_graph->GetNodes();
		}

		//特定のエッジを取得
		std::shared_ptr<EdgeType> GetEdge(const EnumType from, const EnumType to) const {
			return m_graph->GetEdge(from, to);
		}

		//指定したノードから伸びるエッジの取得
		EdgeVector GetEdges(const EnumType from) const{
			return m_graph->GetEdges(from);
		}

		//ノードの追加
		void AddNode(const EnumType type,const std::shared_ptr<NodeType>& node) {
			m_graph->AddNode(type, node);
		}

		//ノードの削除
		void RemoveNode(const std::shared_ptr<NodeType>& node) {
			//maru::MyUtility::RemoveVec(m_nodes, node);
		}

		/// <summary>
		/// エッジの追加
		/// </summary>
		/// <param name="edge">追加するエッジ</param>
		void AddEdge(const std::shared_ptr<EdgeType>& edge) {
			m_graph->AddEdge(edge);
		}

		/// <summary>
		/// エッジの追加
		/// </summary>
		/// <param name="from">元のタイプ</param>
		/// <param name="to">遷移先のタイプ</param>
		/// <param name="isTransitionFunc">遷移条件</param>
		void AddEdge(const EnumType from, const EnumType to, 
			const std::function<bool(const TransitionStructMember& transition)>& isTransitionFunc)
		{
			m_graph->AddEdge(from, to, isTransitionFunc);
		}

		//ノードの数の取得
		int GetNumNode() const {
			return m_graph->GetNumNode();
		}

		//エッジの数の取得
		int GetNumEdge(const EnumType from) const {
			return m_graph->GetNumEdge(from);
		}

		//エッジマップの数を取得
		int GetNumEdgeMap() const {
			return m_graph->GetNumEdgeMap();
		}

		bool IsEmpty() const {
			return m_graph->IsEmpty();
		}

		/// <summary>
		/// 遷移に利用する構造体を取得する。
		/// </summary>
		/// <returns>構造体の参照を渡す</returns>
		TransitionStructMember& GetTransitionStructMember() {
			return m_transitionStruct;
		}

		/// <summary>
		/// クロスフェード
		/// </summary>
		/// <param name="type">切り替えたいステート</param>
		/// <param name="priority">優先度</param>
		void CrossFade(EnumType type, int priority)
		{
			m_transitionCandidates.push_back(TransitionCandidateParametor(type, priority));
		}
		
		/// <summary>
		/// ステート切り替え時に一度だけ呼ぶファンクションのセット
		/// </summary>
		/// <param name="changeType">切り替え先のステートタイプ</param>
		/// <param name="func">切り替え時に呼ぶ関数ポインタ</param>
		void SetChangeOnceFunc(const EnumType changeType, const std::function<void()>& func) {
			m_changeOnceFuncs[changeType] = func;
		}

		void OnUpdate() {
			if (IsEmpty()) {
				return;
			}

			//ノードのUpdate
			NodeUpdate();

			//エッジの切替判断
			TransitionCheck();

			//トリガーのリセット
			TriggerReset();

			//遷移
			Transition();

			//遷移先候補のクリア
			m_transitionCandidates.clear();
		}

		void NodeUpdate() {
			auto node = m_graph->GetNowNode();
			node->OnUpdate();
		}

		/// <summary>
		/// 遷移チェック
		/// </summary>
		void TransitionCheck() {
			auto edges = m_graph->GetNowNodeEdges();
			for (auto& edge : edges) {
				if (edge->IsTransition(m_transitionStruct)) {
					const auto type = edge->GetToType();
					const auto priority = edge->GetPriority();
					m_transitionCandidates.push_back(TransitionCandidateParametor(type, priority));
					//ChangeState(edge->GetToType());
					//break;
				}
			}
		}

		/// <summary>
		/// トリガーのリセット
		/// </summary>
		void TriggerReset() {
			EdgeVectorMap edgesMap = m_graph->GetEdgesMap();
			for (std::pair<EnumType, EdgeVector> edgePair : edgesMap) {
				for (auto& edge : edgePair.second) {
					edge->IsTransition(m_transitionStruct);
				}
			}
		}

		/// <summary>
		/// 遷移
		/// </summary>
		void Transition() {
			if (m_transitionCandidates.size() == 0) {  //遷移先候補が0なら処理を飛ばす。
				return;
			}

			//遷移先候補のソート
			std::sort(m_transitionCandidates.begin(), m_transitionCandidates.end(),
				[](const TransitionCandidateParametor& left, const TransitionCandidateParametor& right) 
				{ return left.priority > right.priority ? true : false; }); //優先度が高い順から遷移する。
			
			ChangeState(m_transitionCandidates[0].type);
		}
	};

}