/*!
@file SparseGraph.cpp
@brief SparseGraph����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	template<class node_type, class edge_type>
	class SparseGraph 
	{
	public:
		//�N���C�A���g����O���t�Ŏg���Ă���G�b�W�ƃm�[�h�ւ̊ȈՂȃA�N�Z�X���\�ɂ���B
		using NodeType = node_type ;
		using EdgeType = edge_type ;

		typedef std::vector<node_type> NodeVector;
		typedef std::list<edge_type> EdgeList;
		typedef std::vector<EdgeList> EdgeListVector;

	private:
		//���̃N���X���\������m�[�h
		NodeVector m_nodes;

		//�אڃG�b�W���X�g�̃x�N�^�[
		//(�e�m�[�h�̃C���f�b�N�X�́A���̃m�[�h�Ɋ֘A�t����ꂽ�G�b�W�̃��X�g�̃L�[�ƂȂ�)
		EdgeListVector m_edges;

		//���̃m�[�h�͗L���O���t���H
		bool m_isDigraph;

		//�ǉ������ׂ����̃m�[�h�C���f�b�N�X
		int m_nextNodeIndex;

	public:
		SparseGraph(bool digraph):
			m_nextNodeIndex(0)
			m_isDigraph(diraph)
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
		/// �G�b�W�̎Q�Ƃ𓾂�
		/// </summary>
		/// <param name="from"></param>
		/// <param name="back"></param>
		/// <returns></returns>
		//const EdgeType& GetEdge(const int& from,const int& back) const {
		//	return 
		//}

		/// <summary>
		/// ���̃t���[�m�[�h�̃C���f�b�N�X���Q�Ƃ���B
		/// </summary>
		/// <returns></returns>
		//int GetNextFreeNodeIndex() const{

		//}

		/// <summary>
		/// ���̃O���t�̃m�[�h��ǉ����āA���̃C���f�b�N�X��Ԃ��B
		/// </summary>
		/// <param name="node">�ǉ��������m�[�h</param>
		/// <returns>�ǉ������m�[�h�̃C���f�b�N�X</returns>
		int AddNode(const NodeType& node) {
			m_nodes.push_back(node);
			return m_nodes.size() - 1;
		}

		/// <summary>
		/// �C���f�b�N�X��invalid_node_index�ɐݒ肷�邱�ƂŃm�[�h���폜����B
		/// </summary>
		/// <param name="index">�폜�������m�[�h�̃C���f�b�N�X</param>
		void RemoveNode(const int& index) {
			
		}

		/// <summary>
		/// �G�b�W�̒ǉ�
		/// </summary>
		/// <param name="edge">�ǉ��������G�b�W</param>
		void AddEdge(const EdgeType& edge) {
			//m_edges.push_back(edge);
		}

		/// <summary>
		/// �G�b�W�̍폜
		/// </summary>
		/// <param name="from"></param>
		/// <param name="back"></param>
		void RemoveEdge(const int& from, const int& back) {

		}

		/// <summary>
		/// ���̃O���t���̃m�[�h�̌���Ԃ��B
		/// </summary>
		/// <returns>�m�[�h�̌�</returns>
		//int GetNumNodes() const {

		//}

		/// <summary>
		/// ���̃O���t���ɑ��݂���A�N�e�B�u�ȃm�[�h�̌���Ԃ��B
		/// </summary>
		/// <returns>�A�N�e�B�u�ȃm�[�h�̌�</returns>
		//int GetNumActiveNodes() const {

		//}
	};

}