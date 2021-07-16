/*!
@file GraphEdge.h
@brief GraphEdge
�S���ҁF�ێR �T��
*/

#pragma once

#include "NavGraphNode.h"

namespace basecross {

	/// <summary>
	/// �ړI�̃m�[�h���L�����āA���̃m�[�h�Ƃ̌v�Z������N���X�B
	/// </summary>
	class Heuristic
	{
		NavGraphNode m_targetNode;  //�ړI�n�ɐݒ肵���m�[�h

	public:

		Heuristic() :
			Heuristic(NavGraphNode())
		{}

		Heuristic(const NavGraphNode& node):
			m_targetNode(node)
		{}

		/// <summary>
		/// �n���ꂽ�m�[�h����^�[�Q�b�g�m�[�h�܂ł̋����𑪂��ĕԂ��B
		/// </summary>
		/// <param name="node">�J�n�n�_�̃m�[�h</param>
		/// <returns>targetNode.position - node.position</returns>
		float CalucHeuristicRange(const NavGraphNode& node);


		//�A�N�Z�b�T-------------------------------------------------
		void SetTargetNode(const NavGraphNode& node) {
			m_targetNode = node;
		}
	};

}

//endbasecross