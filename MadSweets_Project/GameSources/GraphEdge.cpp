/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphEdge.h"

namespace basecross {

	GraphEdge::GraphEdge()
		:GraphEdge(0,0,0.0f)
	{}

	GraphEdge::GraphEdge(const int& front, 
		const int& back
	):
		GraphEdge(front,back,0.0f)
	{}

	GraphEdge::GraphEdge(const int& front, 
		const int& back, 
		const int& cost
	):
		m_front(front),
		m_back(back),
		m_cost(cost)
	{}

}
//end basecross