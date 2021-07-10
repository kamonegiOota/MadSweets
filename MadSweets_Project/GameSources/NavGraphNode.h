/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"
#include "GraphNode.h"

namespace basecross {

	template<class ExtraInfo>
	class NavGraphNode : public GraphNode
	{
	protected:
		/// <summary>
		/// �m�[�h�̏ꏊ
		/// </summary>
		Vec2 m_position;

		ExtraInfo m_extraInfo;

	public:
		
	};

}

//end basecross