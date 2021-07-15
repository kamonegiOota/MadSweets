/*!
@file GraphEdge.h
@brief GraphEdge
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class GraphEdge
	{
	protected:
		//エッジは二つのノードを連結する。
		//有効ノードは常に正
		int m_from;
		int m_to;

		float m_cost;  //移動のコスト

	public:

		GraphEdge();
		GraphEdge(const int& from, const int& to);
		GraphEdge(const int& from, const int& to, const float& cost);
		virtual ~GraphEdge() {}

		//アクセッサ-------------------------------------------------------
		
		//フロント
		int GetFrom() const {
			return m_from;
		}
		void SetFrom(const int& from) {
			m_from = from;
		}

		//バック
		int GetTo() const {   
			return m_to;
		}
		void SetTo(const int& to) {
			m_to = to;
		}

		//コスト
		float GetCost() const { 
			return m_cost;
		}
		void SetCost(const float& cost) {
			m_cost = cost;
		}
	};

}
//end basecross