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

		/// <summary>
		/// ルートの構築
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="selfObj">自分自身</param>
		/// <param name="targetObj">ターゲット</param>
		/// <returns>逃げる方向のノード</returns>
		static NavGraphNode CalucRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);
		/// <summary>
		/// ルートの構築
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="selfPos">自分自身のポジション</param>
		/// <param name="targetPos">ターゲットのポジション</param>
		/// <returns>逃げる方向のノード</returns>
		static NavGraphNode CalucRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);


		/// <summary>
		/// 逃げるときの二回目以降のルート建築
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="selfObj">自分自身</param>
		/// <param name="targetObj">ターゲット</param>
		/// <returns>逃げる方向のノード</returns>
		static NavGraphNode CalucNextRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);
		/// <summary>
		/// 逃げるときの二回目以降のルート建築
		/// </summary>
		/// <param name="astar">Astarの参照</param>
		/// <param name="selfPos">自分自身のポジション</param>
		/// <param name="targetPos">ターゲットのポジション</param>
		/// <returns>逃げる方向のノード</returns>
		static NavGraphNode CalucNextRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);
	};

}

//endbasecross