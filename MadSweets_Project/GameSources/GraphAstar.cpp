/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"
#include "DebugObject.h"
#include "MyUtility.h"
#include "UtilityAstar.h"

#include "HiddenComponent.h"

namespace basecross {

	//auto text = to_wstring(numDelete);
	//MessageBox(0, text.c_str(), L"test", 0);

	Vec3 GraphAstar::CalucTargetNode(const std::shared_ptr<GameObject>& objPtr) {
		if (m_shortRoutes.size() == 0) {
			m_isRouteEnd = true;
		}

		if (m_isRouteEnd) {
			return Vec3(0.0f);
		}

		//�I�u�W�F�N�g���T���m�[�h�̋߂��ɂ�����A���̃m�[�h�ɐ؂�ւ���B
		float nearRange = 2.0f;  //�߂��Ɣ��f����鋗��

		auto trans = objPtr->GetComponent<Transform>();
		auto objPos = trans->GetPosition();

		auto nodePos = m_shortRoutes[m_routeIndex].nextNode->GetPosition();  //���݂̖ڕW�m�[�h�̃|�W�V�������擾

		auto toNode = nodePos - objPos;
		if (toNode.length() <= nearRange) {  //�m�[�h�̋߂��܂ŗ�����B
			m_routeIndex++;
		}

		//�m�[�h�C���f�b�N�X���V���[�g�𒴂�����
		if (m_shortRoutes.size() <= m_routeIndex) {
			m_isRouteEnd = true;//�@�\��off�ɂ���B
		}

		return nodePos;
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		auto selfNearNode = UtilityAstar::SearchNearNode(*this, self);
		auto targetNearNode = UtilityAstar::SearchNearNode(*this, target);
		SearchAstarStart(selfNearNode, targetNearNode);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos) {
		auto selfNearNode = UtilityAstar::SearchNearNode(*this, self);
		auto targetNearNode = UtilityAstar::SearchNearNode(*this, targetPos);
		SearchAstarStart(selfNearNode, targetNearNode);
	}

	void GraphAstar::SearchAstarStart(const Vec3& selfPos, const Vec3& targetPos) {
		auto selfNearNode = UtilityAstar::SearchNearNode(*this,selfPos);
		auto targetNearNode = UtilityAstar::SearchNearNode(*this,targetPos);
		SearchAstarStart(selfNearNode, targetNearNode);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<NavGraphNode>& selfNearNode, const std::shared_ptr<NavGraphNode>& targetNearNode) {
		ResetAstar();

		m_heuristic.SetTargetNode(targetNearNode);  //�q���[���X�e�B�b�N�֐��ɖڕW�m�[�h��ݒ�

		if (selfNearNode->GetPosition() == targetNearNode->GetPosition()) {
			m_shortRoutes.push_back(AstarExpectData(selfNearNode, targetNearNode, 0, 0));
			return;
		}

		//���[�v���ď������s���B
		LoopSearchAstar(selfNearNode);
	}

	const std::shared_ptr<const NavGraphNode> GraphAstar::GetBeforeNode() const {
		if (m_shortRoutes.size() != 0) {
			auto index = m_shortRoutes.size() - 1;
			return m_shortRoutes[index].node.GetShard();
		}

		return nullptr;
	}

	bool GraphAstar::IsAstarEnd() {
		//�ŏI�I�ɔ��f������@��ς���B
		auto index = m_shortRoutes.size() - 1;

		//����Ȃ��ړI�n�ɋ߂��Ȃ�true
		float nearRange = 0.1f;
		if (m_shortRoutes[index].heuristic <= nearRange) {
			return true;
		}
		else {
			return false;
		}
	}

	bool GraphAstar::IsRouteLoop(const AstarExpectData& shortRoute) {
		for (auto& route : m_shortRoutes) {
			if (route.node == shortRoute.nextNode) {
				return true;
			}
		}

		return false;
	}

	bool GraphAstar::IsShortRoute(const AstarExpectData& shortRoute) {
		//size��0�̏ꍇ�͏������s��Ȃ�
		if (m_shortRoutes.size() == 0) {
			return true;
		}

		auto beforeIndex = m_shortRoutes.size() - 1;
		auto beforeRoute = m_shortRoutes[beforeIndex];

		//�����Ă����f�[�^���O�񕪂�菬�������true
		if (beforeRoute.GetSumRange() >= shortRoute.GetSumRange()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool GraphAstar::IsBackShort(const AstarExpectData& newShortRoute) {
		if (m_shortRoutes.size() == 0) {  //�G���[�����o�����炱��if����Ȃ�����
			return false;
		}

		auto index = (int)m_shortRoutes.size() - 1;
		if (index < 0) {
			int i = 0;
		}
		auto beforeShort = m_shortRoutes[index];
		auto edges = m_graph->GetEdges(beforeShort.node->GetIndex());
		for (auto& edge : edges) {
			if (newShortRoute.nextNode->GetIndex() == edge.GetTo()) {
				//�m�[�h��߂鏈��		
				return true;
			}
		}

		return false;
	}

	void GraphAstar::ResetAstar() {
		m_isRouteEnd = false;
		m_routeIndex = 0;
		m_expectDatas.clear();
		m_shortRoutes.clear();
	}

	void GraphAstar::RemoveData(const AstarExpectData& data) {
		auto index = data.node->GetIndex();

		//�f�o�b�O�p
		if (m_expectDatas.size() == 0) {
			int i = 0;
		}

		if (m_expectDatas[index].size() == 0) {
			int i = 0;
		}

		if (index <= 0) {
			int i = 0;
		}

		auto iter = m_expectDatas[index].begin();
		//���v�̒������ꏏ�̃f�[�^���폜
		while (iter != m_expectDatas[index].end()) {
			if (iter->GetSumRange() == data.GetSumRange()) {
				//if (iter->nextNode == data.nextNode) {
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

	void GraphAstar::NextProcess(const AstarExpectData& newRoute) {
		m_shortRoutes.push_back(newRoute);
	}

	void GraphAstar::BackProcess(const AstarExpectData& shortRoute) {
		//�O�񕪂���ŏ��̕������Ȃ�
		RemoveData(shortRoute);
		//�Ō�̃V���[�g���[�g�̍폜
		BackShortRoute();
	}

	void GraphAstar::LoopSearchAstar(const std::shared_ptr<NavGraphNode>& initialNode) {
		int tempIndex = 0;
		int maxTempIndex = 100000;
		//�����I���̃o�O�Ȃ��Ȃ���������B
		while(tempIndex < maxTempIndex){
			tempIndex++;
			std::shared_ptr<NavGraphNode> startNode;
			if (m_shortRoutes.size() == 0) {  //�ŏ��̎��̂�
				startNode = initialNode;
			}
			else {
				auto index = m_shortRoutes.size() - 1;
				startNode = m_shortRoutes[index].nextNode.GetShard();
			}

			//���߂ɁA�S�Ă̗אڃm�[�h�̊��Ғl�𑪂�B
			auto datas = CalucNearNodeExpectData(startNode);

			//�m�[�h������Ȃ��ꍇ�́u�������΂��āvBackProcess������B
			if (datas.size() == 0) {
				auto index = (int)m_shortRoutes.size() - 1;
				if (index < 0) {
					int temp = 0;
					break;
				}
				BackProcess(m_shortRoutes[index]);  //��������m�[�h���Ȃ����߁A��ԍŏ��ɖ߂�B
				continue;
			}

			//���ꂼ��̍��v�̒��ň�ԏ��������z�l�����߂�B
			auto shortRoute = CalucMinRangeNode(datas);
			
			//�I�񂾃m�[�h������Ă����ꍇ�B���[�v����\�������邽��
			if(IsRouteLoop(shortRoute)){
				BackProcess(shortRoute);
				continue;
			}

			//��ԍŏ��ɑI�񂾃m�[�h���ŒZ���ǂ������f����B
			//�����łȂ��ꍇ�͏����������ǂ��B
			if (IsShortRoute(shortRoute)) {
				NextProcess(shortRoute);

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
					NextProcess(shortRoute);  //���ɐi�ށB

					if (IsAstarEnd()) {  //�����I��
						break;
					}
				}
			}
		}

		LastAdjust(initialNode);

		//�f�o�b�O
		if (tempIndex >= maxTempIndex) {
			DebugObject::sm_wss << endl << L"serchOver" << endl;
		}

		for (auto route : m_shortRoutes) {
			DebugObject::AddValue(route.nextNode->GetIndex(),false);
			DebugObject::AddString(L",",false);
		}
	}

	std::vector<AstarExpectData> GraphAstar::CalucNearNodeExpectData(const std::shared_ptr<NavGraphNode>& node) {
		//��x�����������Ƃ̂���m�[�h�͂��̕���Ԃ�
		if (m_expectDatas.count(node->GetIndex())) {
			return m_expectDatas[node->GetIndex()];
		}

		//�G�b�W�̋����𑪂��Ĕz��ŕԂ��B
		auto selfPos = node->GetPosition();
		auto index = node->GetIndex();
		auto edges = m_graph->GetEdges(index);

		std::vector<AstarExpectData> reExpectData;  //���^�[��������Ғl���܂ރf�[�^�B

		auto beforeNode = GetBeforeNode();

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph->GetNode(toIndex);

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

		m_expectDatas[node->GetIndex()] = reExpectData;
		return reExpectData;
	}

	float GraphAstar::CalucNearNodeRange(const std::shared_ptr<NavGraphNode>& selfNode, const std::shared_ptr<NavGraphNode>& targetNode) {
		auto selfPos = selfNode->GetPosition();
		auto targetPos = targetNode->GetPosition();

		auto toVec = targetPos - selfPos;
		return toVec.length();
	}

	AstarExpectData GraphAstar::CalucMinRangeNode(const std::vector<AstarExpectData>& datas) {
		//���O�Ńf�[�^��0�̎��̏��������Ă��邽�߁A�G���[����͂���Ȃ��B
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

	void GraphAstar::LastAdjust(const std::shared_ptr<NavGraphNode>& initialNode) {
		auto shortRoutes = m_shortRoutes;
		m_shortRoutes.clear();
		m_shortRoutes.push_back(AstarExpectData(initialNode,initialNode,0,0));
		for (auto route : shortRoutes) {
			m_shortRoutes.push_back(route);
		}
	}

	//�A�N�Z�b�T------------------------------------------------------------------------------------------------------

	int GraphAstar::AddNode(const Vec3& position) {
		//���̑Ώۂɓ���Ȃ��I�u�W�F�N�g
		vector<shared_ptr<GameObject>> excluteObjs;
		maru::MyUtility::AddComponents<HiddenComponent>(excluteObjs);

		return AddNode(position, MyUtility::GetStage()->GetGameObjectVec(), excluteObjs);
	}

	int GraphAstar::AddNode(const Vec3& position,
		const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
	{
		//�m�[�h�̐���
		auto index = m_graph->GetNextFreeNodeIndex();
		auto newNode = make_shared<NavGraphNode>(index, position);

		auto edges = UtilityAstar::CreateAdjacendEdges(m_graph, newNode, obstacleObjs, excluteObjs);

		//���݂̓G�b�W���쐬���ꂽ�Ƃ��̂ݐ�������悤�ɂ���B(�q�����ĂȂ��m�[�h��Ώۂɂ����ꍇ�ɏ������~�܂��Ă��܂����߁B)
		//���P���ꎟ��O���B
		if (edges.size() != 0) {
			//�m�[�h�̒ǉ�
			m_graph->AddNode(newNode);
		}

		return index++;
	}

	void GraphAstar::RemoveNode(const int& index) {
		m_graph->RemoveNode(index);
	}

	void GraphAstar::AddEdges(const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs) {
		auto nodes = m_graph->GetNodes();
		for (auto& node : nodes) {
			auto edges = UtilityAstar::CreateAdjacendEdges(m_graph, node, obstacleObjs, excluteObjs);
			if (edges.size() == 0) {
				//�m�[�h�̒ǉ�
				m_graph->RemoveNode(node->GetIndex());
			}
		}
	}
}

//endbasecross