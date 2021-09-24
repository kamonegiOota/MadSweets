
/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "NodeBase.h"

namespace basecross {

	/// <summary>
	/// Graph�̊��N���X
	/// </summary>
	/// <typeparam name="NodeType">�g�p����m�[�h</typeparam>
	/// <typeparam name="EnumType">�g�p����񋓑�</typeparam>
	/// <typeparam name="TransitionStructMember">�J�ڏ����p�̍\���̃����o�[</typeparam>
	template<class node_type, class EnumType, class TransitionStructMember>
	class GraphBase
	{
	public:
		//using�f�B���N�e�B�u
		using EdgeType = EdgeBase<EnumType, TransitionStructMember>;

		using NodeType = NodeBase<node_type>;
		using NodeMap = std::map<EnumType, std::shared_ptr<NodeType>>;
		using EdgeVector = std::vector<std::shared_ptr<EdgeType>>;
		using EdgeVectorMap = std::map<EnumType, EdgeVector>;

	private:
		//�����o�ϐ�---------------

		EnumType m_nowNodeType;  //���݂̃m�[�h

		NodeMap m_nodes;          //�m�[�h���i�[����z��
		EdgeVectorMap m_edgesMap; //�G�b�W���i�[����z��

		//�A�N�e�B�u���ǂ���
		bool m_isActive = true;

	public:
		//���ݎg���m�[�h�̃^�C�v�̎擾
		EnumType GetNowType() const {
			return m_nowNodeType;
		}

		//���ݎg���m�[�h�̎擾
		std::shared_ptr<NodeType> GetNowNode() const {
			return m_nodes.at(m_nowNodeType);
		}

		//�w�肵���m�[�h�̎擾
		std::shared_ptr<NodeType> GetNode(const EnumType type) const {
			return m_nodes.at(type);
		}

		//�m�[�h�̔z����擾
		NodeMap GetNodes() const {
			return m_nodes;
		}

		//����̃G�b�W���擾
		std::shared_ptr<EdgeType> GetEdge(const EnumType from, const EnumType to) const {
			//���݂��Ȃ�������nullptr��Ԃ��B
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

		//�w�肵���m�[�h����L�т�G�b�W�̎擾
		EdgeVector GetEdges(const EnumType from) const {
			return m_edgesMap.at(from);
		}

		EdgeVector GetNowNodeEdges() const {
			return m_edgesMap.at(m_nowNodeType);
		}

		EdgeVectorMap GetEdgesMap() {
			return m_edgesMap;
		}

		//�m�[�h�̒ǉ�
		void AddNode(const EnumType type, const std::shared_ptr<NodeType>& node) {
			if (IsEmpty()) {
				m_nowNodeType = type;
				node->OnStart();
			}

			m_nodes[type] = node;
		}

		//�m�[�h�̍폜
		void RemoveNode(const std::shared_ptr<NodeType>& node) {
			//maru::MyUtility::RemoveVec(m_nodes, node);
		}

		/// <summary>
		/// �G�b�W�̒ǉ�
		/// </summary>
		/// <param name="edge">�ǉ��������G�b�W</param>
		void AddEdge(const std::shared_ptr<EdgeType>& edge) {
			m_edgesMap[edge->GetFromType()].push_back(edge);
		}

		/// <summary>
		/// �G�b�W�̒ǉ�
		/// </summary>
		/// <param name="from">���̃^�C�v</param>
		/// <param name="to">�J�ڐ�̃^�C�v</param>
		/// <param name="isTransitionFunc">�J�ڏ���</param>
		void AddEdge(const EnumType from, const EnumType to,
			const std::function<bool(const TransitionStructMember& transition)>& isTransitionFunc)
		{
			auto newEdge = make_shared<EdgeType>(from, to, isTransitionFunc);
			AddEdge(newEdge);
		}

		//�m�[�h�̐��̎擾
		int GetNumNode() const {
			return static_cast<int>(m_nodes.size());
		}

		//�G�b�W�̐��̎擾
		int GetNumEdge(const EnumType from) const {
			return static_cast<int>(m_edgesMap.count(from));
		}

		//�G�b�W�}�b�v�̐����擾
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

		//�X�e�[�g�̕ύX
		void ChangeState(const EnumType type) {
			m_nodes[m_nowNodeType]->OnExit();

			m_nowNodeType = type;
			m_nodes[m_nowNodeType]->OnStart();
		}
	};

}

//endbasecross


