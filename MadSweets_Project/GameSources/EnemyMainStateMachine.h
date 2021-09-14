/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EdgeBase.h"
#include "GraphBase.h"

namespace basecross {

	/// <summary>
	/// EnemyStateMachine�p�̃e���v���[�g�N���X�B
	/// �m�[�h��StateMachine���p������������������
	/// </summary>
	/// <typeparam name="NodeType">�g�p����m�[�h</typeparam>
	/// <typeparam name="EnumType">�g�p����񋓑�</typeparam>
	/// <typeparam name="TransitionStructMember">�J�ڏ����p�̍\���̃����o�[</typeparam>
	template<class NodeType, class EnumType, class TransitionStructMember>
	class EnemyMainStateMachine : public Component
	{
	public:
		//�O������Enum���g�����p��EnumType��public�ɂ���B
		using StateEnum = EnumType;
		using EdgeType = EdgeBase<EnumType, TransitionStructMember>;

	private:
		//using�f�B���N�e�B�u
		using GraphType = GraphBase<NodeType, EnumType, TransitionStructMember>;

		using NodeMap = std::map<EnumType, NodeType>;
		using EdgeVector = std::vector<std::shared_ptr<EdgeType>>;
		using EdgeVectorMap = std::map<EnumType, EdgeVector>;

		//private�����o�ϐ�------------------------

		std::shared_ptr<GraphType> m_graph;  //�O���t�̏��
		TransitionStructMember m_transitionStruct; //�J�ڏ����ɗ��p����\����

		//private�����o�֐�-------------------------

		//�X�e�[�g�̕ύX
		void ChangeState(const EnumType type) {
			m_nodes[m_nowNodeType]->Exit();

			m_nowNodeType = type;
			m_nodes[m_nowNodeType]->Start();
		}

	public:
		EnemyMainStateMachine(const std::shared_ptr<GameObject>& objPtr) 
			:Component(objPtr)
		{}

		//���ݎg���m�[�h�̎擾
		std::shared_ptr<NodeType> GetNowNode() const {
			return m_graph->GetNowNode();
		}
		
		//�w�肵���m�[�h�̎擾
		std::shared_ptr<NodeType> GetNode(const EnumType type) const {
			return m_graph->GetNode(type);
		}

		//�m�[�h�̔z����擾
		NodeMap GetNodes() const {
			return m_graph->GetNodes();
		}

		//����̃G�b�W���擾
		std::shared_ptr<EdgeType> GetEdge(const EnumType from, const EnumType to) const {
			return m_graph->GetEdge(from, to);
		}

		//�w�肵���m�[�h����L�т�G�b�W�̎擾
		EdgeVector GetEdges(const EnumType from) const{
			return m_graph->GetEdges(from);
		}

		//�m�[�h�̒ǉ�
		void AddNode(const EnumType type,const std::shared_ptr<NodeType>& node) {
			m_graph->addNode(type, node);
		}

		//�m�[�h�̍폜
		void RemoveNode(const std::shared_ptr<NodeType>& node) {
			//maru::MyUtility::RemoveVec(m_nodes, node);
		}

		/// <summary>
		/// �G�b�W�̒ǉ�
		/// </summary>
		/// <param name="edge">�ǉ�����G�b�W</param>
		void AddEdge(const std::shared_ptr<EdgeType>& edge) {
			m_graph->AddEdge(edge);
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
			m_graph->AddEdge(from, to, isTransitionFunc);
		}

		//�m�[�h�̐��̎擾
		int GetNumNode() const {
			return m_graph->GetNumNode();
		}

		//�G�b�W�̐��̎擾
		int GetNumEdge(const EnumType from) const {
			return m_graph->GetNumEdge(from);
		}

		//�G�b�W�}�b�v�̐����擾
		int GetNumEdgeMap() const {
			return m_graph->GetNumEdgeMap();
		}

		bool IsEmpty() const {
			return m_graph->IsEmpty();
		}

		/// <summary>
		/// �J�ڂɗ��p����\���̂��擾����B
		/// </summary>
		/// <returns>�\���̂̎Q�Ƃ�n��</returns>
		TransitionStructMember& GetTransitionStructMember() {
			return m_transitionStruct;
		}
		

		void OnCreate() override {}

		void OnUpdate() override {
			if (IsEmpty()) {
				return;
			}

			auto edges = m_graph->GetNowNodeEdges();
			for (auto& edge : edges) {
				if (edge->IsTransition(m_transitionStruct)) {
					ChangeState(edge->GetToType());
					break;
				}
			}
		}
	};

}