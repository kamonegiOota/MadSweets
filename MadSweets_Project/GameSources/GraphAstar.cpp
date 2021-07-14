/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"

namespace basecross {

	NavGraphNode GraphAstar::SearchNearNode(const std::shared_ptr<GameObject>& target) {
		//��ԋ߂��m�[�h�̌���
		auto nodes = m_graph.GetNodes();
		auto targetTrans = target->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();

		float minRange = 0.0f;
		NavGraphNode minNode;  //��ԋ������Z���m�[�h

		//�����J�n
		for (const auto& node : nodes) {
			auto pos = node.GetPosition();
			auto toNode = pos - targetPos;
			const auto& range = toNode.length();

			//�������Z�������炱��ɂ���B
			if (range <= minRange) {
				minRange = range;
				minNode = node;
			}
		}

		return minNode;
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		m_rangeIndex = 0;
		auto selfNearNode = SearchNearNode(self);
		auto targetNearNode = SearchNearNode(target);
		m_heuristic.SetTargetNode(targetNearNode);  //�q���[���X�e�B�b�N�֐��ɖڕW�m�[�h��ݒ�
		m_shortNodes.push_back(selfNearNode);  //�X�^�[�g�ʒu�̃m�[�h�̃C���f�b�N�X�̊i�[

		//���ɂ������ɓ����s���𓥂ށB
		while (true) {
			auto node = m_shortNodes[m_rangeIndex];

			//���߂ɁA�S�Ă̗אڃm�[�h�̒����𑪂�B
			auto toRanges = CalucNearNodeSumRange(node);
			m_nodeRanges.push_back(toRanges);  //���̍��v��nodeRanges�Ɋi�[

			//���ꂼ��̍��v�̒��ň�ԏ��������z�l�����߂�B
			auto minRangeNode = CalucMinRangeNode(toRanges);
			m_shortNodes.push_back(minRangeNode);

			//��ԍŏ��ɑI�񂾃m�[�h���ŒZ���ǂ������f����B
			//�����łȂ��ꍇ�͏����������ǂ��B
			//�����i�ޏꍇ�̓C���f�b�N�X��i�߂�B
			
		}
	}

	std::vector<float> GraphAstar::CalucNearNodeSumRange(const NavGraphNode& node) {
		//�G�b�W�̋����𑪂��Ĕz��ŕԂ��B
		auto selfPos = node.GetPosition();
		auto index = node.GetIndex();
		auto edges = m_graph.GetEdges(index);

		std::vector<float> reRanges;  //���^�[�����鋗����z��ł܂Ƃ߂�ϐ��B

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);

			auto toRange = CalucNearNodeRange(node,nextNode);
			auto toHeuriRange = m_heuristic.CalucHeuristicRange(nextNode);  //���m�[�h����ړI�m�[�h�܂ł̃q���[���X�e�B�b�N���������߂�B

			auto sumValue = toRange + toHeuriRange;  //�����W�ƃq���[���X�e�B�b�N�����̍��v
			reRanges.push_back(sumValue);
		}

		return reRanges;
	}

	float GraphAstar::CalucNearNodeRange(const NavGraphNode& selfNode, const NavGraphNode& targetNode) {
		auto selfPos = selfNode.GetPosition();
		auto targetPos = targetNode.GetPosition();

		auto toVec = targetPos - selfPos;
		return toVec.length();
	}

	NavGraphNode GraphAstar::CalucMinRangeNode(const std::vector<float>& ranges) {
		//���󂾂Ƃ�����Ƃ����C���f�b�N�X���擾�ł��Ă��Ȃ��B
		int index = 0;
		float minRange = 0.0f;
		for (int i = 0; i < ranges.size(); i++) {
			if (ranges[i] <= minRange) {
				minRange = ranges[i];
				index = i;
			}
		}

		return m_graph.GetNode(index);
	}

}

//endbasecross