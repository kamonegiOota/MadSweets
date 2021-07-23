/*!
@file CalucEscapeRoute.h
@brief CalucEscapeRoute
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "GraphAstar.h"

namespace basecross {

	/// <summary>
	/// �����郋�[�g���\�z����Ƃ��̃f�[�^�N���X
	/// </summary>
	class CalucEscapeRoute
	{

	public:
		static NavGraphNode CalucRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);

		static NavGraphNode CalucRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);

		//������Ƃ��̓��ڈȍ~�̃��[�g���z
		static NavGraphNode CalucNextRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);

		static NavGraphNode CalucNextRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);
	};

}

//endbasecross