/*!
@file GraphNode.h
@brief GraphNode�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class GraphNode
	{
	protected:
		int m_index;
		bool m_isActive;

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

		bool IsActive() {
			return m_isActive;
		}

		void SetIsActive(bool b) {
			m_isActive = b;
		}
	};
	
}
//end basecross