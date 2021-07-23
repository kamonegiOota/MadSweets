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
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const Vec3& targetPos);

		//�����̃m�[�h����^�[�Q�b�g�����ɂ���m�[�h������
		static NavGraphNode CalucTargetDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);

		//�^�[�Q�b�g���瓦���邽�߂̕����̃m�[�h����������
		static NavGraphNode CalucTargetEscapeDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);
	};

}