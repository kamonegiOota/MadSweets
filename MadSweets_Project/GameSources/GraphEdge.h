/*!
@file GraphEdge.cpp
@brief GraphEdge実体
*/

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
		GraphEdge(const int& front, const int& back);
		GraphEdge(const int& front, const int& back, const int& cost);
		virtual ~GraphEdge() {}

		//アクセッサ-------------------------------------------------------
		
		//フロント
		int GetFront() const {  
			return m_from;
		}
		void SetFront(const int& from) {
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