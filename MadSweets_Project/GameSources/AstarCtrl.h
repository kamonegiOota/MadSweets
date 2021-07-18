/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/
#pragma once

#include "GraphAstar.h"

namespace basecross {

	class AstarCtrl : public Component
	{
		GraphAstar m_astar;

		void Move();

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

		//�A�N�Z�b�T-------------------------------------------------------------
		void SearchAstarStart(const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const Vec3& targetPos);
		
		void SearchAstarForecastStart(const std::shared_ptr<GameObject>& target);

		Vec3 GetCalucNodePos(){
			return m_astar.CalucTargetNode(GetGameObject());
		}

		bool IsRouteEnd() const {
			return m_astar.IsRouteEnd();
		}
	};

}

//endbasecross