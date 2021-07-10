/*!
@file SparseGraph.cpp
@brief SparseGraph実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	template<class node_type, class edge_type>
	class SparseGraph 
	{
	public:
		//クライアントからグラフで使われているエッジとノードへの簡易なアクセスを可能にする。
		using NodeType = node_type ;
		using EdgeType = edge_type ;

		typedef std::vector<node_type> NodeVector;
		typedef std::list<edge_type> EdgeList;
		typedef std::vector<EdgeList> EdgeListVector;

	private:
		//このクラスを構成するノード
		NodeVector m_nodes;

		//隣接エッジリストのベクター
		//(各ノードのインデックスは、そのノードに関連付けられたエッジのリストのキーとなる)
		EdgeListVector m_edges;

		//このノードは有効グラフか？
		bool m_isDigraph;

		//追加されるべき次のノードインデックス
		int m_nextNodeIndex;

	public:
		SparseGraph(bool digraph):
			m_nextNodeIndex(0)
			m_isDigraph(diraph)
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
		/// エッジの参照を得る
		/// </summary>
		/// <param name="from"></param>
		/// <param name="back"></param>
		/// <returns></returns>
		//const EdgeType& GetEdge(const int& from,const int& back) const {
		//	return 
		//}

		/// <summary>
		/// 次のフリーノードのインデックスを参照する。
		/// </summary>
		/// <returns></returns>
		//int GetNextFreeNodeIndex() const{

		//}

		/// <summary>
		/// このグラフのノードを追加して、そのインデックスを返す。
		/// </summary>
		/// <param name="node">追加したいノード</param>
		/// <returns>追加したノードのインデックス</returns>
		int AddNode(const NodeType& node) {
			m_nodes.push_back(node);
			return m_nodes.size() - 1;
		}

		/// <summary>
		/// インデックスをinvalid_node_indexに設定することでノードを削除する。
		/// </summary>
		/// <param name="index">削除したいノードのインデックス</param>
		void RemoveNode(const int& index) {
			
		}

		/// <summary>
		/// エッジの追加
		/// </summary>
		/// <param name="edge">追加したいエッジ</param>
		void AddEdge(const EdgeType& edge) {
			//m_edges.push_back(edge);
		}

		/// <summary>
		/// エッジの削除
		/// </summary>
		/// <param name="from"></param>
		/// <param name="back"></param>
		void RemoveEdge(const int& from, const int& back) {

		}

		/// <summary>
		/// このグラフ内のノードの個数を返す。
		/// </summary>
		/// <returns>ノードの個数</returns>
		//int GetNumNodes() const {

		//}

		/// <summary>
		/// このグラフ内に存在するアクティブなノードの個数を返す。
		/// </summary>
		/// <returns>アクティブなノードの個数</returns>
		//int GetNumActiveNodes() const {

		//}
	};

}