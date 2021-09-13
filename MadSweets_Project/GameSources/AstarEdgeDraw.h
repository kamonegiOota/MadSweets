/*!
@file PositionDrawComp.h
@brief PositionDrawComp
�S���ҁF�ێR �T��
*/

#pragma once

class GraphAstar;

namespace basecross {

	class AstarEdgeDraw : public Component {

		ex_weak_ptr<GraphAstar> m_astar;

		void CreateDrawBox(const Vec3& startPosition, const Vec3& endPosition);

	public:

		AstarEdgeDraw(const std::shared_ptr<GameObject>& objPtr,const std::shared_ptr<GraphAstar>& astar)
			:Component(objPtr),m_astar(astar)
		{}

		void OnCreate();
		void OnUpdate(){}
	};

}

//endbasecross