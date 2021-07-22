/*!
@file CalucEscapeRoute.h
@brief CalucEscapeRoute
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "GraphAstar.h"

namespace basecross {

	/// <summary>
	/// 逃げるルートを構築するときのデータクラス
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