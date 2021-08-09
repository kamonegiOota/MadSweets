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
		SparseGraph<NavGraphNode, GraphEdge> m_graph;
		/// <summary>
		/// �q���[�X���b�N�v�Z�����Ă����N���X
		/// </summary>
		Heuristic m_heuristic;

		//std::shared_ptr<GameObject> m_selfObj;

		std::vector<std::vector<AstarExpectData>> m_expectDatas;  //�v���������Ғl�̃f�[�^���v��

		std::vector<AstarExpectData> m_shortRoutes;  //�ŒZ�o�H���i�[�����z��B
		int m_routeIndex = 0;   //���݂ǂ̃m�[�h��ڕW�Ƃ��Ă��邩�𔻒f����C���f�b�N�X�B
		bool m_isRouteEnd = true;  //���[�g�̍Ō�ɗ������ǂ����H

		bool m_isCreateNewData = true;  //�V�������[�g����邩�ǂ���
		bool m_isReturnPhase = false;  //��x�߂��Ă����Ԃ��ǂ���

		bool m_isForecase = false;  //�\�������m�[�h���^�[�Q�b�g�ɂ��Ă��邩�ǂ���


		const NavGraphNode *GetBeforeNode() const;  //�O�̃m�[�h�̏����擾����B
		void RemoveData(const AstarExpectData& data); //�f�[�^�̃����[�u
		void BackShortRoute(); //��U�O�̃��[�g�ɖ߂�B
		bool IsAstarEnd();  //Astar�̏I���𔻒f
		
	public:
		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph)//, m_countIndex(0)
		{}


		//�^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		//const NavGraphNode SearchNearNode(const std::shared_ptr<GameObject>& target);
		//const NavGraphNode SearchNearNode(const Vec3& targetPos);
		
		//�����m�[�h�ƃG�b�W����A�ǂ̃��[�g����ԋ߂�������
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos);
		void SearchAstarStart(const Vec3& selfPos, const Vec3& targetPos);

		//�^�[�Q�b�g�̍s���\�����Ă��̕����m�[�h�Ɍ��������[�g���\�z���鏈��(Forecast == �\���A�\�z)
		void SearchAstarForecastStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);

		//�ŒZ�m�[�h�̒��ō��~�����m�[�h�̏ꏊ���擾����B
		Vec3 CalucTargetNode(const std::shared_ptr<GameObject>& objPtr);

		//�A�N�Z�b�T-------------------------------------------------------
		
		//�����������[�g�̍Ō�܂ŗ�����true
		bool IsRouteEnd() const {
			return m_isRouteEnd;
		}

		const SparseGraph<NavGraphNode, GraphEdge>& GetGraph() const {
			return m_graph;
		}

		void SetShortRoutes(const vector<AstarExpectData> shortRoutes) {
			m_isRouteEnd = false;
			m_shortRoutes = shortRoutes;
		}

		//�m�[�h�̒ǉ�
		void AddNode(const Vec3& position);
		//�m�[�h�̍폜
		void RemoveNode(const int& index);

	private:

		//�������Z�b�g����Ƃ��̊֐�
		void ResetAstar();

		//�ŏI����
		void LastAdjust(const AstarExpectData& startData);

		//�i�ގ��̏���
		void NextProcess(const AstarExpectData& newRoute, const vector<AstarExpectData>& newDatas);

		//�߂鎞�̏���
		void BackProcess(const AstarExpectData& shortRoute);

		//���[�v���ĒT���o�H�𑪂�B
		void LoopSearchAstar(const AstarExpectData& startData);

		//�אڃm�[�h�̋����ƃq���[���X�e�B�b�N�����̍��v�𑪂�A���̃f�[�^��Ԃ��B
		std::vector<AstarExpectData> CalucNearNodeExpectData(const NavGraphNode& node);

		//�אڃm�[�h�̋����𑪂�
		float CalucNearNodeRange(const NavGraphNode& fromNode, const NavGraphNode& toNode);

		//�v�������אڃm�[�h�̊��Ғl�̒���,��ԏ��������̃m�[�h�����������B
		AstarExpectData CalucMinRangeNode(const std::vector<AstarExpectData>& datas);

		//���߂��������{���ɍŒZ���ǂ����𔻒f����B
		bool IsShortRoute(const AstarExpectData& data);

		//�O�̃m�[�h���獡��̍ŒZ���[�g���q�����Ă���ꍇ�́A�߂��������ŒZ�̉\���������B����𔻒f
		bool IsBackShort(const AstarExpectData& newShortRoute);
	};

}

//endbasecross