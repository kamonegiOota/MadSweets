/*!
@file GraphAstar.h
@brief GraphAstar�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once
#include "stdafx.h"

#include "SparseGraph.h"
#include "Heuristic.h"

//#include "NavGraphNode.h"
#include "GraphEdge.h"

namespace basecross {

	/// <summary>
	/// Astar�ɂ�����A���Ғl�̌v�Z�ɗp����\����
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
		/// �m�[�h�ƃG�b�W���Ǘ�����
		/// </summary>
		SparseGraph<NavGraphNode, GraphEdge> m_graph;  //�O���t�f�[�^
		/// <summary>
		/// �q���[�X���b�N�v�Z�����Ă����N���X
		/// </summary>
		Heuristic m_heuristic;  //�q���[�X���b�N�̐��l���v�Z����B

		std::map<int,std::vector<AstarExpectData>> m_expectDatas;  //�v���������Ғl�̃f�[�^���v��

		std::vector<AstarExpectData> m_shortRoutes;  //�ŒZ�o�H���i�[�����z��B
		int m_routeIndex = 0;   //���݂ǂ̃m�[�h��ڕW�Ƃ��Ă��邩�𔻒f����C���f�b�N�X�B
		bool m_isRouteEnd = true;  //���[�g�̍Ō�ɗ������ǂ����H
		
	public:

		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph)//, m_countIndex(0)
		{}

		/// <summary>
		/// �ŒZ�m�[�h�̒��ō��~�����m�[�h�̏ꏊ���擾����B
		/// </summary>
		/// <param name="objPtr">���݂��̏������s���Ă���I�u�W�F�N�g</param>
		/// <returns>���݌������ׂ��m�[�h�̃|�W�V����</returns>
		Vec3 CalucTargetNode(const std::shared_ptr<GameObject>& objPtr);
		
		/// <summary>
		/// �����m�[�h�ƃG�b�W����A�ǂ̃��[�g����ԋ߂�������
		/// </summary>
		/// <param name="self">�J�n�̃I�u�W�F�N�g</param>
		/// <param name="target">�^�[�Q�b�g�ƂȂ�I�u�W�F�N�g</param>
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos);
		void SearchAstarStart(const Vec3& selfPos, const Vec3& targetPos);

	private:
		//���ۂ̏����̊J�n
		void SearchAstarStart(const NavGraphNode& selfNearNode, const NavGraphNode& targetNearNode);

		//�O�̃m�[�h�̏����擾����B
		const NavGraphNode* GetBeforeNode() const;

		/// <summary>
		/// Astar�̃��[�v�v�Z���I�����ׂ����𔻒f����B
		/// </summary>
		/// <returns></returns>
		bool IsAstarEnd();
		/// <summary>
		/// ��������[�g������ꍇ��true��Ԃ��B(��肪����ꍇ�̓��[�g�����[�v����\�������邽��)
		/// </summary>
		/// <param name="shortRoute">�V�����v�Z�����ŒZ���[�g</param>
		/// <returns>��肪����Ȃ�true</returns>
		bool IsRouteLoop(const AstarExpectData& shortRoute);
		/// <summary>
		/// ���߂��������{���ɍŒZ���ǂ����𔻒f����B
		/// </summary>
		/// <param name="shortRoute">�V�������[�g</param>
		/// <returns>�ŒZ���[�g�Ȃ�true</returns>
		bool IsShortRoute(const AstarExpectData& shortRoute);
		/// <summary>
		/// �O�̃m�[�h���獡��̍ŒZ���[�g���q�����Ă���ꍇ�́A�߂��������ŒZ�̉\���������B����𔻒f
		/// </summary>
		/// <param name="newShortRoute">�V�������[�g</param>
		/// <returns>�߂��������ŒZ�Ȃ�true</returns>
		bool IsBackShort(const AstarExpectData& newShortRoute);

		void ResetAstar();  //�������Z�b�g����Ƃ��̊֐�
		void RemoveData(const AstarExpectData& data); //�f�[�^�̃����[�u
		void BackShortRoute(); //��U�O�̃��[�g�ɖ߂�B

		/// <summary>
		/// ���ōŒZ���[�g���m�肷�鏈��
		/// </summary>
		/// <param name="newRoute">�V�K���[�g</param>
		void NextProcess(const AstarExpectData& newRoute);
		/// <summary>
		/// �ŒZ���[�g�łȂ��Ɣ��f���A�O�̃m�[�h�ɖ߂鏈��
		/// </summary>
		/// <param name="shortRoute">���ݍŒZ�Ǝv���Ă��郋�[�g</param>
		void BackProcess(const AstarExpectData& shortRoute);

		/// <summary>
		/// ���[�v���ĒT���o�H�𑪂�B
		/// </summary>
		/// <param name="initialNode">�����X�^�[�g�m�[�h</param>
		void LoopSearchAstar(const NavGraphNode& initialNode);

		/// <summary>
		/// �אڃm�[�h�̋����ƃq���[���X�e�B�b�N�����̍��v�𑪂�A���̃f�[�^��Ԃ��B
		/// </summary>
		/// <param name="node">��ƂȂ�m�[�h(�X�^�[�g�n�_)</param>
		/// <returns>�v�Z���ꂽ�z���Ԃ�</returns>
		std::vector<AstarExpectData> CalucNearNodeExpectData(const NavGraphNode& node);

		/// <summary>
		/// �אڃm�[�h�̋����𑪂�
		/// </summary>
		/// <param name="fromNode">�J�n�̃m�[�h</param>
		/// <param name="toNode">�Ώۂ̃m�[�h</param>
		/// <returns>�אڃm�[�h�̋���</returns>
		float CalucNearNodeRange(const NavGraphNode& fromNode, const NavGraphNode& toNode);

		/// <summary>
		/// �v�������אڃm�[�h�̊��Ғl�̒���,��ԏ��������̃m�[�h�����������B
		/// </summary>
		/// <param name="datas">�v�Z�Ɏg���f�[�^�Q</param>
		/// <returns>���Ғl����ԏ������f�[�^</returns>
		AstarExpectData CalucMinRangeNode(const std::vector<AstarExpectData>& datas);

		/// <summary>
		/// �ŏI����
		/// </summary>
		void LastAdjust(const NavGraphNode& initialNode);

		//�A�N�Z�b�T-------------------------------------------------------
	public:

		/// <summary>
		/// �����������[�g�̍Ō�܂ŗ�����true
		/// </summary>
		/// <returns>�Ō�܂ŗ�����true</returns>
		bool IsRouteEnd() const {
			return m_isRouteEnd;
		}

		const SparseGraph<NavGraphNode, GraphEdge>& GetGraph() const {
			return m_graph;
		}

		/// <summary>
		/// �m�[�h�̒ǉ�
		/// </summary>
		/// <param name="position">�ǉ��������m�[�h�̃|�W�V����</param>
		/// <returns>�ǉ������m�[�h�̃C���f�b�N�X</returns>
		int AddNode(const Vec3& position);
		/// <summary>
		/// �m�[�h�̒ǉ�
		/// </summary>
		/// <param name="position">�ǉ��������m�[�h�̃|�W�V����</param>
		/// <param name="obstacleObjs">��Q���Ώۂ̃I�u�W�F�N�g</param>
		/// <param name="excluteObjs">��Q�����珜���Ώۂ̃I�u�W�F�N�g</param>
		/// <returns>�ǉ������m�[�h�̃C���f�b�N�X</returns>
		int AddNode(const Vec3& position,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);
		/// <summary>
		/// �m�[�h�̍폜
		/// </summary>
		/// <param name="index">�폜�������m�[�h�̃C���f�b�N�X</param>
		void RemoveNode(const int& index);

		/// <summary>
		/// �G�b�W�̒ǉ�
		/// </summary>
		/// <param name="obstacleObjs">��Q������̃I�u�W�F�N�g</param>
		/// <param name="excluteObjs">��Q���̒��ł����ʂɊO������</param>
		void AddEdges(const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);
	};

}

//endbasecross