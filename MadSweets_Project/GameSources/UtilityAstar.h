/*!
@file UtilityAstar.h
@brief UtilityAstar�Ȃ�
�S���ҁF�ێR �T��
*/

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

		/// <summary>
		/// �^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="target">�^�[�Q�b�g</param>
		/// <returns>�^�[�Q�b�g�̈�ԋ߂��̃m�[�h</returns>
		static std::shared_ptr<NavGraphNode> SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="targetPos">�^�[�Q�b�g�̃|�W�V����</param>
		/// <param name="excluteObjs">Ray�̑ΏۊO�ɂ���I�u�W�F�N�g�Q</param>
		/// <returns>�^�[�Q�b�g�����ԋ߂��m�[�h</returns>
		static std::shared_ptr<NavGraphNode> SearchNearNode(const GraphAstar& astar, const Vec3& targetPos,
			vector<std::shared_ptr<GameObject>> excluteObjs = vector<std::shared_ptr<GameObject>>());

		/// <summary>
		/// �����̃m�[�h����L�т�m�[�h�ň�ԃ^�[�Q�b�g�ɋ߂��m�[�h�̑I��
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="selfObject">�������g</param>
		/// <param name="target">�^�[�Q�b�g</param>
		/// <returns>��ԋ߂��m�[�h</returns>
		static std::shared_ptr<NavGraphNode> SearchMyNodeToTargetNearNode(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObject,const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// �����̃m�[�h����^�[�Q�b�g�����ɂ���m�[�h������
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="startNode">�J�n�m�[�h</param>
		/// <param name="targetPos">�^�[�Q�b�g�̃|�W�V����</param>
		/// <returns>�^�[�Q�b�g�����̃m�[�h</returns>
		static std::shared_ptr<NavGraphNode> CalucTargetDirectNode(const GraphAstar& astar,
			const std::shared_ptr<NavGraphNode>& startNode,
			const Vec3& targetPos);

		/// <summary>
		/// �^�[�Q�b�g���瓦���邽�߂̕����̃m�[�h����������
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="startNode">�J�n�m�[�h</param>
		/// <param name="targetPos">�^�[�Q�b�g�̃|�W�V����</param>
		/// <returns>�^�[�Q�b�g�����̃m�[�h</returns>
		static std::shared_ptr<NavGraphNode> CalucTargetEscapeDirectNode(const GraphAstar& astar,
			const std::shared_ptr<NavGraphNode>& startNode,
			const Vec3& targetPos);

		/// <summary>
		/// node�̃C���f�b�N�X����אڂ���G�b�W�̐�������B
		/// ��������ꍇ�ɒ��ړn���ꂽSparseGraph��Add����B
		/// </summary>
		/// <param name="graph">Graph�̎Q��</param>
		/// <param name="newNode">�V�K�m�[�h</param>
		/// <param name="obstacleObjs">��Q���̃I�u�W�F�N�g�z��</param>
		/// <param name="excluteObjs">��Q������Ȃ��I�u�W�F�N�g�z��</param>
		/// <returns>�������ꂽ�G�b�W�̔z��</returns>
		template<class NodeClass, class EdgeClass>
		static vector<GraphEdge> CreateAdjacendEdges(std::shared_ptr<SparseGraph<NodeClass, EdgeClass>>& graph, const std::shared_ptr<NavGraphNode>& newNode,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto nodes = graph->GetNodes();

			vector<GraphEdge> reEdges;
			//for (const auto& node : nodes) {
				for (auto& node : nodes) {
					//��Q�����Ȃ�������G�b�W��ǉ�����B
					if (!maru::MyUtility::IsRayObstacle(newNode->GetPosition(), node->GetPosition(), obstacleObjs, excluteObjs)) {
						//�o�����ɃG�b�W�𐶐�
						graph->AddEdge(GraphEdge(newNode->GetIndex(), node->GetIndex()));
						graph->AddEdge(GraphEdge(node->GetIndex(), newNode->GetIndex()));
						//�ǂ̂悤�ȃG�b�W�𐶐��������Ԃ���悤�ɕʂ̔z��ɓ����B
						reEdges.push_back(GraphEdge(newNode->GetIndex(), node->GetIndex()));
						reEdges.push_back(GraphEdge(node->GetIndex(), newNode->GetIndex()));
					}
				}
			//}

			return reEdges;
		}
	};

}