/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
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
		/// ノードの場所
		/// </summary>
		Vec2 m_position;

		ExtraInfo m_extraInfo;

	public:
		
	};

}

//end basecross