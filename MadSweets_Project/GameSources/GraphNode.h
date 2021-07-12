/*!
@file GraphNode.h
@brief GraphNodeなど
担当者：丸山 裕喜
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

		//アクセッサ
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