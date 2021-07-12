/*!
@file NavGraphNode.h
@brief NavGraphNodeクラス
担当者：丸山 裕喜
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