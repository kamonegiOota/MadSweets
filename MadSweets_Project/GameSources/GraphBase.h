
/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "NodeBase.h"

namespace basecross {

	/// <summary>
	/// Graphの基底クラス
	/// </summary>
	/// <typeparam name="NodeType">使用するノード</typeparam>
	/// <typeparam name="EnumType">使用する列挙体</typeparam>
	/// <typeparam name="TransitionStructMember">遷移条件用の構造体メンバー</typeparam>
	template<class node_type, class EnumType, class TransitionStructMember>
	class GraphBase
	{
	public:
		//usingディレクティブ
		using EdgeType = EdgeBase<EnumType, TransitionStructMember>;

		using NodeType = NodeBase<node_type>;
		using NodeMap = std::map<EnumType, std::shared_ptr<NodeType>>;
		using EdgeVector = std::vector<std::shared_ptr<EdgeType>>;
		using EdgeVectorMap = std::map<EnumType, EdgeVector>;

	private:
		//メンバ変数---------------

		EnumType m_nowNodeType;  //現在のノード

		NodeMap m_nodes;          //ノードを格納する配列
		EdgeVectorMap m_edgesMap; //エッジを格納する配列

		//アクティブかどうか
		bool m_isActive = true;

	public:
		//現在使うノードのタイプの取得
		EnumType GetNowType() const {
			return m_nowNodeType;
		}

		//現在使うノードの取得
		std::shared_ptr<NodeType> GetNowNode() const {
			return m_nodes.at(m_nowNodeType);
		}

		//指定したノードの取得
		std::shared_ptr<NodeType> GetNode(const EnumType type) const {
			return m_nodes.at(type);
		}

		//ノードの配列を取得
		NodeMap GetNodes() const {
			return m_nodes;
		}

		//特定のエッジを取得
		std::shared_ptr<EdgeType> GetEdge(const EnumType from, const EnumType to) const {
			//存在しなかったらnullptrを返す。
			if (m_edgesMap.count[from] == 0) {
				return nullptr;
			}

			auto edges = m_edgesMap[from];
			for (auto& edge : edges) {
				if (edge->GetToType() == to) {
					return edge;
				}
			}

			return nullptr;
		}

		//指定したノードから伸びるエッジの取得
		EdgeVector GetEdges(const EnumType from) const {
			return m_edgesMap.at(from);
		}

		EdgeVector GetNowNodeEdges() const {
			return m_edgesMap.at(m_nowNodeType);
		}

		EdgeVectorMap GetEdgesMap() {
			return m_edgesMap;
		}

		//ノードの追加
		void AddNode(const EnumType type, const std::shared_ptr<NodeType>& node) {
			if (IsEmpty()) {
				m_nowNodeType = type;
				node->OnStart();
			}

			m_nodes[type] = node;
		}

		//ノードの削除
		void RemoveNode(const std::shared_ptr<NodeType>& node) {
			//maru::MyUtility::RemoveVec(m_nodes, node);
		}

		/// <summary>
		/// エッジの追加
		/// </summary>
		/// <param name="edge">追加したいエッジ</param>
		void AddEdge(const std::shared_ptr<EdgeType>& edge) {
			m_edgesMap[edge->GetFromType()].push_back(edge);
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
			auto newEdge = make_shared<EdgeType>(from, to, isTransitionFunc);
			AddEdge(newEdge);
		}

		//ノードの数の取得
		int GetNumNode() const {
			return static_cast<int>(m_nodes.size());
		}

		//エッジの数の取得
		int GetNumEdge(const EnumType from) const {
			return static_cast<int>(m_edgesMap.count(from));
		}

		//エッジマップの数を取得
		int GetNumEdgeMap() const {
			return static_cast<int>(m_edgesMap.size());
		}

		bool IsActive() {
			return m_isActive;
		}
		void SetActive(const bool isActive) {
			m_isActive = isActive;
		}

		bool IsEmpty() const {
			return static_cast<int>(m_nodes.size()) == 0 ? true : false;
		}

		//ステートの変更
		void ChangeState(const EnumType type) {
			m_nodes[m_nowNodeType]->OnExit();

			m_nowNodeType = type;
			m_nodes[m_nowNodeType]->OnStart();
		}
	};

}

//endbasecross


