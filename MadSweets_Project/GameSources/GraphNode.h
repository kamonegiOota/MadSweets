/*!
@file GraphNode.h
@brief GraphNode�Ȃ�
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

		//�A�N�Z�b�T
		int GetIndex() const{
			return m_index;
		};

		void SetIndex(const int& index) {
			m_index = index;
		}
	};
	
}
//end basecross