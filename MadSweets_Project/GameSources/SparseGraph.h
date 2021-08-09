/*!
@file SparseGraph.h
@brief SparseGraph
�S���ҁF�ێR �T��
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
		//�N���C�A���g����O���t�Ŏg���Ă���G�b�W�ƃm�[�h�ւ̊ȈՂȃA�N�Z�X���\�ɂ���B
		using NodeType = node_type ;
		using EdgeType = edge_type ;

		typedef std::vector<node_type> NodeVector;
		typedef std::vector<edge_type> EdgeVector; //�폜�̓s���ナ�X�g�ɂ��Ă���B
		typedef std::map<int,EdgeVector> EdgeMapVector;

	private:
		//���̃N���X���\������m�[�h
		NodeVector m_nodes;

		//�אڃG�b�W���X�g�̃x�N�^�[
		//(�e�m�[�h�̃C���f�b�N�X�́A���̃m�[�h�Ɋ֘A�t����ꂽ�G�b�W�̃��X�g�̃L�[�ƂȂ�)
		EdgeMapVector m_edges;

		//���̃m�[�h�͗L���O���t���H
		bool m_isDigraph;

		//�ǉ������ׂ����̃m�[�h�C���f�b�N�X
		int m_nextNodeIndex;

	public:
		SparseGraph(bool digraph):
			m_nextNodeIndex(0),
			m_isDigraph(digraph)
		{}

		/// <summary>
		/// �w�肳�ꂽ�C���f�b�N�X�̃m�[�h��Ԃ�
		/// </summary>
		/// <param name="index">�~�����m�[�h�̃C���f�b�N�X</param>
		/// <returns>�w�肳�ꂽ�C���f�N�X�̃m�[�h</returns>
		const NodeType& GetNode(const int& index) const {
			return m_nodes[index];
		}

		/// <summary>
		/// �S�Ẵm�[�h��n��
		/// </summary>
		/// <returns>�S�Ẵm�[�h</returns>
		const std::vector<NodeType>& GetNodes() const {
			return m_nodes;
		}

		/// <summary>
		/// �G�b�W�̎Q�Ƃ𓾂�
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
		/// �^����ꂽ��������n�܂�G�b�W���X�g��S�Ď擾
		/// </summary>
		/// <param name="from">�~�����G�b�W���X�g�̃C���f�b�N�X</param>
		/// <returns>�G�b�W���X�g</returns>
		const std::vector<EdgeType>& GetEdges(const int& from) const{
			return m_edges.at(from);
		}

		/// <summary>
		/// ���̃t���[�m�[�h�̃C���f�b�N�X���Q�Ƃ���B
		/// </summary>
		/// <returns></returns>
		int GetNextFreeNodeIndex() const{
			return m_nextNodeIndex;
		}

		/// <summary>
		/// ���̃O���t�̃m�[�h��ǉ����āA���̃C���f�b�N�X��Ԃ��B
		/// </summary>
		/// <param name="node">�ǉ��������m�[�h</param>
		/// <returns>�ǉ������m�[�h�̃C���f�b�N�X</returns>
		int AddNode(const NodeType& node) {
			m_nodes.push_back(node);
			m_nextNodeIndex++;
			return (int)m_nodes.size() - 1;
		}

		/// <summary>
		/// �C���f�b�N�X��invalid_node_index�ɐݒ肷�邱�ƂŃm�[�h���폜����B
		/// </summary>
		/// <param name="index">�폜�������m�[�h�̃C���f�b�N�X</param>
		void RemoveNode(const int& index) {
			//�m�[�h�̍폜
			MyUtility::RemoveVec(m_nodes, m_nodes[index]);
			//���̃m�[�h��edges�̍폜
			m_edges.erase(index);

			//�폜�����C���f�N�X���܂܂��G�b�W���폜
			for (int i = 0; i < m_edges.size(); i++) {
				for (auto& edge : m_edges[i]) {
					if (edge.GetTo() == index) {  //�s�悪index�ƈꏏ�Ȃ�
						RemoveEdge(edge.GetFrom(), edge.GetTo());
					}
				}
			}

		}

		/// <summary>
		/// �G�b�W�̒ǉ�
		/// </summary>
		/// <param name="edge">�ǉ��������G�b�W</param>
		void AddEdge(const EdgeType& edge) {
			m_edges[edge.GetFrom()].push_back(edge);
		}

		/// <summary>
		/// �G�b�W�̍폜
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
		/// �n���ꂽ�C���f�b�N�X���܂܂��G�b�W��S�č폜����B
		/// </summary>
		/// <param name="index">�폜�������C���f�b�N�X</param>
		//void RemoveEdge(const int& index) {
		//	
		//}

		/// <summary>
		/// ���̃O���t���̃m�[�h�̌���Ԃ��B
		/// </summary>
		/// <returns>�m�[�h�̌�</returns>
		int GetNumNodes() const {
			return m_nodes.size();
		}

		/// <summary>
		/// ���̃O���t���ɑ��݂���A�N�e�B�u�ȃm�[�h�̌���Ԃ��B
		/// </summary>
		/// <returns>�A�N�e�B�u�ȃm�[�h�̌�</returns>
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
		/// �w�肵���C���f�b�N�X�����m�[�h�����̃O���t���ɑ��݂���ꍇ�Atrue��Ԃ��B
		/// </summary>
		/// <param name="index">�w�肵���C���f�b�N�X</param>
		/// <returns>�w�肵���C���f�b�N�X�����m�[�h�����݂���ꍇ��true</returns>
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