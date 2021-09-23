/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
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
	/// ノードはStateMachineを継承した物を扱うこと
	/// </summary>
	/// <typeparam name="NodeType">使用するノード</typeparam>
	/// <typeparam name="EnumType">使用する列挙体</typeparam>
	/// <typeparam name="TransitionStructMember">遷移条件用の構造体メンバー</typeparam>
	template<class NodeType, class EnumType, class TransitionStructMember>
	class EnemyMainStateMachine : public Component
	{
	public:
		//外部からEnumを使う時用にEnumTypeをpublicにする。
		using StateEnum = EnumType;
		using EdgeType = EdgeBase<EnumType, TransitionStructMember>;

	private:
		//usingディレクティブ
		using GraphType = GraphBase<NodeType, EnumType, TransitionStructMember>;

		using NodeMap = std::map<EnumType, NodeType>;
		using EdgeVector = std::vector<std::shared_ptr<EdgeType>>;
		using EdgeVectorMap = std::map<EnumType, EdgeVector>;

		//privateメンバ変数------------------------

		std::shared_ptr<GraphType> m_graph;  //グラフの情報
		TransitionStructMember m_transitionStruct; //遷移条件に利用する構造体

		std::map<EnumType ,std::function<void()>> m_changeOnceFuncs;  //切り替え時に一度だけ呼ぶファンクション

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
		EnemyMainStateMachine(const std::shared_ptr<GameObject>& objPtr) 
			:Component(objPtr),m_graph(std::make_shared<GraphType>())
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
		/// ステート切り替え時に一度だけ呼ぶファンクションのセット
		/// </summary>
		/// <param name="changeType">切り替え先のステートタイプ</param>
		/// <param name="func">切り替え時に呼ぶ関数ポインタ</param>
		void SetChangeOnceFunc(const EnumType changeType, const std::function<void()>& func) {
			m_changeOnceFuncs[changeType] = func;
		}

		void OnCreate() override {}

		void OnUpdate() override {
			if (IsEmpty()) {
				return;
			}

			//ノードのUpdate

			//エッジの切替判断
			auto edges = m_graph->GetNowNodeEdges();
			for (auto& edge : edges) {
				if (edge->IsTransition(m_transitionStruct)) {
					ChangeState(edge->GetToType());
					break;
				}
			}

			//トリガーのリセット

		}
	};

}