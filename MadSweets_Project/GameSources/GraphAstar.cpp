/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"
#include "DebugObject.h"


namespace basecross {

	const NavGraphNode *GraphAstar::GetBeforeNode() const {
		if (m_shortRoutes.size() != 0) {
			auto index = m_shortRoutes.size() - 1;
			return &m_shortRoutes[index].node;
		}

		return nullptr;
	}

	void GraphAstar::RemoveData(const AstarExpectData& data) {
		auto index = m_expectDatas.size() - 1;
		if (m_isReturnPhase) {  //���^�[����ԏo������ꍇ�́A�ŐV�̃f�[�^�������B
			auto end = m_expectDatas.end();
			m_expectDatas.erase(end);
			index--;
		}

		auto iter = m_expectDatas[index].begin();
		
		while (iter != m_expectDatas[index].end()) {
			if(iter->GetSumRange() == data.GetSumRange()){
				m_expectDatas[index].erase(iter);
				return;
			}
			iter++;
		}
	}

	void GraphAstar::BackShortRoute() {
		auto end = m_shortRoutes.end();
		end--;
		m_shortRoutes.erase(end);
	}

	bool GraphAstar::IsAstarEnd() {
		//�ŏI�I�ɔ��f������@��ς���B
		auto index = m_shortRoutes.size() - 1;

		if (m_shortRoutes[index].heuristic <= 0.1f){
			return true;
		}
		else {
			return false;
		}
	}

	NavGraphNode GraphAstar::SearchNearNode(const std::shared_ptr<GameObject>& target) {
		//��ԋ߂��m�[�h�̌���
		auto targetTrans = target->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();

		auto reNode = SearchNearNode(targetPos);
		return reNode;
	}

	NavGraphNode GraphAstar::SearchNearNode(const Vec3& targetPos) {
		auto nodes = m_graph.GetNodes();

		float minRange = 10000.0f;
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
		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		SearchAstarStart(self, targetPos);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos) {
		m_isRouteEnd = false;
		m_routeIndex = 0;
		m_expectDatas.clear();
		m_shortRoutes.clear();
		m_isCreateNewData = true;
		m_isReturnPhase = false;

		auto selfNearNode = SearchNearNode(self);
		auto targetNearNode = SearchNearNode(targetPos);
		//DebugObject::AddVector(targetNearNode.GetPosition());
		m_heuristic.SetTargetNode(targetNearNode);  //�q���[���X�e�B�b�N�֐��ɖڕW�m�[�h��ݒ�

		//���[�v���ď������s���B
		LoopSearchAstar(selfNearNode);
	}

	void GraphAstar::SearchAstarForecastStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		auto targetNearNode = SearchNearNode(target);
		auto startNodePos = targetNearNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;
		toTargetVec.y = 0.0f;

		float minRad = 360.0f;
		NavGraphNode targetNode;
		auto edges = m_graph.GetEdges(targetNearNode.GetIndex());
		for (const auto& edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);
			auto nextPos = nextNode.GetPosition();

			auto toNextNodeVec = nextPos - startNodePos;
			toNextNodeVec.y = 0.0f;

			auto newDot = dot(toTargetVec.GetNormalized(), toNextNodeVec.GetNormalized());
			auto newRad = acosf(newDot);
			if (newRad < minRad) {
				minRad = newRad;
				targetNode = nextNode;
			}
		}

		SearchAstarStart(self, targetNode.GetPosition());
	}

	void GraphAstar::NextProcess(const AstarExpectData& newRoute, const vector<AstarExpectData>& newDatas) {
		m_shortRoutes.push_back(newRoute);
		m_expectDatas.push_back(newDatas);
		m_isCreateNewData = true;
		m_isReturnPhase = false;
	}

	void GraphAstar::BackProcess(const AstarExpectData& shortRoute) {
		//�O�񕪂���ŏ��̕������Ȃ�
		RemoveData(shortRoute);
		//�O��̕�����ŏ��̃f�[�^�����߂�
		BackShortRoute();
		//���ȏ�߂����ꍇ�ɔ��f
		m_isReturnPhase = true;
	}

	void GraphAstar::LoopSearchAstar(const NavGraphNode& stdNode) {
		//���ɂ������ɓ����s���𓥂ށB
		
		//for (int i = 0; i < 5; i++) {
		while(true){
			NavGraphNode node;
			if (m_shortRoutes.size() == 0) {  //�ŏ��̎��̂�
				node = stdNode;
			}
			else {
				auto index = m_shortRoutes.size() - 1;
				node = m_shortRoutes[index].nextNode;
			}

			//���߂ɁA�S�Ă̗אڃm�[�h�̊��Ғl�𑪂�B
			auto datas = CalucNearNodeExpectData(node);

			//�m�[�h������Ȃ��ꍇ�́u�������΂��āv�߂�
			if (datas.size() == 0) {
				auto index = (int)m_shortRoutes.size() - 1;
				BackProcess(m_shortRoutes[index]);
				continue;
			}

			//���ꂼ��̍��v�̒��ň�ԏ��������z�l�����߂�B
			auto shortRoute = CalucMinRangeNode(datas);
			//DebugObject::AddVector(shortRoute.nextNode.GetPosition());
			
			//��ԍŏ��ɑI�񂾃m�[�h���ŒZ���ǂ������f����B
			//�����łȂ��ꍇ�͏����������ǂ��B
			if (IsShortRoute(shortRoute)) {
				NextProcess(shortRoute, datas);

				if (IsAstarEnd()) {  //�����I��
					break;
				}
			}
			else {
				//nextNode���O��node����̃G�b�W�������Ă��邩�ǂ����H
				if (IsBackShort(shortRoute)) {
					BackProcess(shortRoute);  //�߂�
				}
				else {
					NextProcess(shortRoute, datas);  //���ɐi�ށB

					if (IsAstarEnd()) {  //�����I��
						break;
					}
				}
			}
		}
	}

	std::vector<AstarExpectData> GraphAstar::CalucNearNodeExpectData(const NavGraphNode& node) {
		if (m_isCreateNewData == false) {  //�V�����������Ȃ��ėǂ��̂Ȃ�
			int index = (int)m_expectDatas.size() - 1;
			return m_expectDatas[index];  //�O�񕪂̃C���f�b�N�X��Ԃ��B
		}

		//�G�b�W�̋����𑪂��Ĕz��ŕԂ��B
		auto selfPos = node.GetPosition();
		auto index = node.GetIndex();
		auto edges = m_graph.GetEdges(index);

		std::vector<AstarExpectData> reExpectData;  //���^�[��������Ғl���܂ރf�[�^�B

		auto beforeNode = GetBeforeNode();

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);

			//�����̑O�̃m�[�h�̏ꍇ�͓���Ȃ�
			if (beforeNode) {  //beforeNode�����݂���ꍇ
				if (beforeNode->GetIndex() == toIndex) {
					continue;
				}
			}

			auto toRange = CalucNearNodeRange(node,nextNode);
			auto toHeuriRange = m_heuristic.CalucHeuristicRange(nextNode);  //���m�[�h����ړI�m�[�h�܂ł̃q���[���X�e�B�b�N���������߂�B

			AstarExpectData data(node,nextNode,toRange,toHeuriRange);
			reExpectData.push_back(data);
		}

		m_isCreateNewData = false;
		return reExpectData;
	}

	float GraphAstar::CalucNearNodeRange(const NavGraphNode& selfNode, const NavGraphNode& targetNode) {
		auto selfPos = selfNode.GetPosition();
		auto targetPos = targetNode.GetPosition();

		auto toVec = targetPos - selfPos;
		return toVec.length();
	}

	AstarExpectData GraphAstar::CalucMinRangeNode(const std::vector<AstarExpectData>& datas) {
		int index = 0;
		float minRange = 100000.0f;
		for (int i = 0; i < datas.size(); i++) {
			auto range = datas[i].GetSumRange();
			if (range < minRange) {
				minRange = range;
				index = i;
			}
		}

		return datas[index];
	}

	bool GraphAstar::IsShortRoute(const AstarExpectData& data) {
		//size��0�̏ꍇ�͏������s��Ȃ�
		if (m_shortRoutes.size() == 0) {
			return true;
		}

		auto beforeIndex = m_shortRoutes.size() - 1;
		auto beforeRoute = m_shortRoutes[beforeIndex];

		//�����Ă����f�[�^���O�񕪂�菬�������true
		if (beforeRoute.GetSumRange() >= data.GetSumRange()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool GraphAstar::IsBackShort(const AstarExpectData& newShortRoute) {
		auto index = (int)m_shortRoutes.size() - 1;
		auto beforeShort = m_shortRoutes[index];
		auto edges = m_graph.GetEdges(beforeShort.node.GetIndex());
		for (auto& edge : edges) {
			if (newShortRoute.nextNode.GetIndex() == edge.GetTo()) {
				//�m�[�h��߂鏈��		
				return true;
			}
		}

		return false;
	}

	Vec3 GraphAstar::CalucTargetNode(const std::shared_ptr<GameObject>& objPtr) {
		//m_isRouteEnd = true;
		//DebugObject::m_wss.str(L"");
		if (m_isRouteEnd) {
			//DebugObject::m_wss << to_wstring(m_shortRoutes.size());
			return Vec3(0.0f);
		}

		//�I�u�W�F�N�g���T���m�[�h�̋߂��ɂ�����A���̃m�[�h�ɐ؂�ւ���B
		float nearRange = 0.1f;  //�߂��Ɣ��f����鋗��

		auto trans = objPtr->GetComponent<Transform>();
		auto objPos = trans->GetPosition();
		
		auto nodePos = m_shortRoutes[m_routeIndex].nextNode.GetPosition();  //���݂̖ڕW�m�[�h�̃|�W�V�������擾
		//DebugObject::AddVector(nodePos);

		auto toNode = nodePos - objPos;
		if (toNode.length() <= nearRange) {  //�m�[�h�̋߂��܂ŗ�����B
			m_routeIndex++;
		}

		//�m�[�h�C���f�b�N�X���V���[�g�𒴂�����B
		if (m_shortRoutes.size() <= m_routeIndex) {
			m_isRouteEnd = true;//�@�\��off�ɂ���B
		}

		return nodePos;
	}
}

//endbasecross