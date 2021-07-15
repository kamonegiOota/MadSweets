/*!
@file GraphEdge.h
@brief GraphEdge
担当者：丸山 裕喜
*/

#pragma once

#include "NavGraphNode.h"

namespace basecross {

	/// <summary>
	/// 目的のノードを記憶して、そのノードとの計算をするクラス。
	/// </summary>
	class Heuristic
	{
		NavGraphNode m_targetNode;  //目的地に設定したノード

	public:

		Heuristic() :
			Heuristic(NavGraphNode())
		{}

		Heuristic(const NavGraphNode& node):
			m_targetNode(node)
		{}

		/// <summary>
		/// 渡されたノードからターゲットノードまでの距離を測って返す。
		/// </summary>
		/// <param name="node">開始地点のノード</param>
		/// <returns>targetNode.position - node.position</returns>
		float CalucHeuristicRange(const NavGraphNode& node);


		//アクセッサ-------------------------------------------------
		void SetTargetNode(const NavGraphNode& node) {
			m_targetNode = node;
		}
	};

}

//endbasecross