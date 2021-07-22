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
		static void CalucRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);

		static void CalucRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);

	};

}

//endbasecross