/*!
@file PlowlingMove.cpp
@brief PlowlingMove����
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"

#include "GraphAstar.h"

namespace basecross {

	class AstarCtrl : public Component
	{

		GraphAstar m_astar;

	public:
		AstarCtrl(const std::shared_ptr<GameObject>& objPtr,
			const GraphAstar& astar
		):
			Component(objPtr),
			m_astar(astar)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {};

	};

}

//endbasecross