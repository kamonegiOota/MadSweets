#pragma once

#include "NavGraphNode.h"
#include "GraphAstar.h"

namespace basecross {

	/// <summary>
	/// Astar�ł悭�g���v�Z���܂Ƃ߂��N���X
	/// GraphAstar���]��ɂ��֐��������������߁A�v�Z�n�𕪂��邽�߂ɐ���
	/// </summary>
	class UtilityAstar
	{
	public:

		//�^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target);
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const Vec3& targetPos,
			vector<std::shared_ptr<GameObject>> excluteObjs = vector<std::shared_ptr<GameObject>>());

		//�����̃m�[�h����L�т�m�[�h�ň�ԃ^�[�Q�b�g�ɋ߂��m�[�h�̑I��
		static NavGraphNode SearchMyNodeToTargetNearNode(const GraphAstar& astar, 
			const std::shared_ptr<GameObject>& selfObject,const std::shared_ptr<GameObject>& target);

		//�����̃m�[�h����^�[�Q�b�g�����ɂ���m�[�h������
		static NavGraphNode CalucTargetDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);

		//�^�[�Q�b�g���瓦���邽�߂̕����̃m�[�h����������
		static NavGraphNode CalucTargetEscapeDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);

		//node�̃C���f�b�N�X����אڂ���G�b�W�̐�������B
		//��������ꍇ�ɒ��ړn���ꂽSparseGraph��Add����B
		template<class NodeClass, class EdgeClass>
		static vector<GraphEdge> CreateAdjacendEdges(SparseGraph<NodeClass, EdgeClass>& graph, const NavGraphNode& newNode,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto nodes = graph.GetNodes();

			vector<GraphEdge> reEdges;
			//for (const auto& node : nodes) {
				for (auto& node : nodes) {
					//��Q�����Ȃ�������G�b�W��ǉ�����B
					if (!maru::MyUtility::IsRayObstacle(newNode.GetPosition(), node.GetPosition(), obstacleObjs, excluteObjs)) {
						//�o�����ɃG�b�W�𐶐�
						graph.AddEdge(GraphEdge(newNode.GetIndex(), node.GetIndex()));
						graph.AddEdge(GraphEdge(node.GetIndex(), newNode.GetIndex()));
						//�ǂ̂悤�ȃG�b�W�𐶐��������Ԃ���悤�ɕʂ̔z��ɓ����B
						reEdges.push_back(GraphEdge(newNode.GetIndex(), node.GetIndex()));
						reEdges.push_back(GraphEdge(node.GetIndex(), newNode.GetIndex()));
					}
				}
			//}

			return reEdges;
		}
	};

}