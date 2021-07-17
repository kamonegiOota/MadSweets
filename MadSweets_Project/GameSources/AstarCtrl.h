/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
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

		//アクセッサ-------------------------------------------------------------
		void SearchAstarStart(const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const Vec3& targetPos);
	};

}

//endbasecross