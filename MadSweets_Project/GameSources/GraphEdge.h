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
		int m_front;
		int m_back;

		float m_cost;  //移動のコスト

	public:

		GraphEdge();
		GraphEdge(const int& front, const int& back);
		GraphEdge(const int& front, const int& back, const int& cost);
		virtual ~GraphEdge() {}

		//アクセッサ-------------------------------------------------------
		
		//フロント
		int GetFront() const {  
			return m_front;
		}
		void SetFront(const int& front) {
			m_front = front;
		}

		//バック
		int GetBack() const {   
			return m_back;
		}
		void SetBack(const int& back) {
			m_back = back;
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