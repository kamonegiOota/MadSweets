/*!
@file GraphNode.h
@brief GraphNodeなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class GraphNode
	{
	protected:
		int m_index;

	public:

		GraphNode();
		GraphNode(const int& index);
		virtual ~GraphNode() {}

		//アクセッサ
		int GetIndex() const{
			return m_index;
		};

		void SetIndex(const int& index) {
			m_index = index;
		}
	};
	
}
//end basecross