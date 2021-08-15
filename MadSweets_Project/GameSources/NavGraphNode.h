/*!
@file NavGraphNode.h
@brief NavGraphNodeクラス
担当者：丸山 裕喜
*/

#pragma once
#include "stdafx.h"
#include "GraphNode.h"

namespace basecross {

	class NavGraphNode : public GraphNode
	{
	protected:
		/// <summary>
		/// ノードの場所
		/// </summary>
		Vec3 m_position;

	public:

		NavGraphNode() :
			NavGraphNode(0)
		{}

		NavGraphNode(const int& index) :
			NavGraphNode(index,Vec3(0.0f))
		{}

		NavGraphNode(const int& index, const Vec3& position) :
			GraphNode(index),m_position(position)
		{}
		
		void SetPosition(const Vec3& position) {
			m_position = position;
		}

		Vec3 GetPosition() const{
			return m_position;
		}

		bool operator==(NavGraphNode node) const{
			return m_index == node.GetIndex() ? true : false;
		}

	};

}

//end basecross