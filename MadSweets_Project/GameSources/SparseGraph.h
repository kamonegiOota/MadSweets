/*!
@file SparseGraph.h
@brief SparseGraph
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

//#include "NavGraphNode.h"
//#include "GraphEdge.h"

#include "MyUtility.h"

namespace basecross {

	using maru::MyUtility;

	template<class node_type, class edge_type>
	class SparseGraph 
	{
	public:
		//クライアントからグラフで使われているエッジとノードへの簡易なアクセスを可能にする。
		using NodeType = node_type ;
		using EdgeType = edge_type ;

		typedef std::vector<node_type> NodeVector;
		typedef std::vector<edge_type> EdgeVector; //削除の都合上リストにしてある。
		typedef std::map<int,EdgeVector> EdgeMapVector;

	private:
		//このクラスを構成するノード
		NodeVector m_nodes;

		//隣接エッジリストのベクター
		//(各ノードのインデックスは、そのノードに関連付けられたエッジのリストのキーとなる)
		EdgeMapVector m_edges;

		//このノードは有効グラフか？
		bool m_isDigraph;

		//追加されるべき次のノードインデックス
		int m_nextNodeIndex;

	public:
		SparseGraph(bool digraph):
			m_nextNodeIndex(0),
			m_isDigraph(digraph)
		{}

		/// <summary>
		/// 指定されたインデックスのノードを返す
		/// </summary>
		/// <param name="index">欲しいノードのインデックス</param>
		/// <returns>指定されたインデクスのノード</returns>
		const NodeType& GetNode(const int& index) const {
			return m_nodes[index];
		}

		/// <summary>
		/// 全てのノードを渡す
		/// </summary>
		/// <returns>全てのノード</returns>
		const std::vector<NodeType>& GetNodes() const {
			return m_nodes;
		}

		/// <summary>
		/// エッジの参照を得る
		/// </summary>
		/// <param name="from"></param>
		/// <param name="back"></param>
		/// <returns></returns>
		const EdgeType& GetEdge(const int& from,const int& to) const {
			for (auto edge : m_edges[from]) {
				if (edge.GetTo() == to) {
					return edge;
				}
			}

			return nullptr;
		}

		/// <summary>
		/// 与えられた引数から始まるエッジリストを全て取得
		/// </summary>
		/// <param name="from">欲しいエッジリストのインデックス</param>
		/// <returns>エッジリスト</returns>
		const std::vector<EdgeType>& GetEdges(const int& from) const{
			return m_edges.at(from);
		}

		/// <summary>
		/// 次のフリーノードのインデックスを参照する。
		/// </summary>
		/// <returns></returns>
		int GetNextFreeNodeIndex() const{
			return m_nextNodeIndex;
		}

		/// <summary>
		/// このグラフのノードを追加して、そのインデックスを返す。
		/// </summary>
		/// <param name="node">追加したいノード</param>
		/// <returns>追加したノードのインデックス</returns>
		int AddNode(const NodeType& node) {
			m_nodes.push_back(node);
			m_nextNodeIndex++;
			return (int)m_nodes.size() - 1;
		}

		/// <summary>
		/// インデックスをinvalid_node_indexに設定することでノードを削除する。
		/// </summary>
		/// <param name="index">削除したいノードのインデックス</param>
		void RemoveNode(const int& index) {
			//ノードの削除
			MyUtility::RemoveVec(m_nodes, m_nodes[index]);
			//そのノードのedgesの削除
			m_edges.erase(index);

			//削除したインデクスが含まれるエッジを削除
			for (int i = 0; i < m_edges.size(); i++) {
				for (auto& edge : m_edges[i]) {
					if (edge.GetTo() == index) {  //行先がindexと一緒なら
						RemoveEdge(edge.GetFrom(), edge.GetTo());
					}
				}
			}

		}

		/// <summary>
		/// エッジの追加
		/// </summary>
		/// <param name="edge">追加したいエッジ</param>
		void AddEdge(const EdgeType& edge) {
			m_edges[edge.GetFrom()].push_back(edge);
		}

		/// <summary>
		/// エッジの削除
		/// </summary>
		/// <param name="from"></param>
		/// <param name="back"></param>
		void RemoveEdge(const int& from, const int& to) {
			auto& edges = m_edges[from];
			auto iter = edges.begin();
			while (iter != edges.end()) {
				if (iter->GetTo() == to) {
					iter = edges.erase(iter);
					break;
				}

				iter++;
			}
		}

		/// <summary>
		/// 渡されたインデックスが含まれるエッジを全て削除する。
		/// </summary>
		/// <param name="index">削除したいインデックス</param>
		//void RemoveEdge(const int& index) {
		//	
		//}

		/// <summary>
		/// このグラフ内のノードの個数を返す。
		/// </summary>
		/// <returns>ノードの個数</returns>
		int GetNumNodes() const {
			return m_nodes.size();
		}

		/// <summary>
		/// このグラフ内に存在するアクティブなノードの個数を返す。
		/// </summary>
		/// <returns>アクティブなノードの個数</returns>
		int GetNumActiveNodes() const {
			int num = 0;
			for (auto node : m_nodes) {
				if (node.IsActive()) {
					num++;
				}
			}
			return num;
		}

		int GetNumEdges() const {
			int num = 0;
			for (auto edges : m_edges) {
				num += edges.size();
			}

			return num;
		}

		bool IsDigraph() const {
			return m_isDigraph;
		}

		bool IsEmpty() const {
			return m_nodes.size() == 0 ? true, false;
		}

		/// <summary>
		/// 指定したインデックスを持つノードがこのグラフ内に存在する場合、trueを返す。
		/// </summary>
		/// <param name="index">指定したインデックス</param>
		/// <returns>指定したインデックスを持つノードが存在する場合はtrue</returns>
		bool IsPresent(int index) const {
			for (auto node : m_nodes) {
				if (node.GetIndex() == index) {
					return true;
				}
			}
			
			return false;
		}


	};

}