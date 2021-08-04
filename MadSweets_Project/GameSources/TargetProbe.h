/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// ターゲットを捜索するコンポーネント
	/// </summary>
	class TargetProbe : public Component, public BaseUseVelocity
	{
		std::shared_ptr<GameObject> m_target;

		//何回プレイヤーの捜索をするか？
		int m_numPorb = 2;
		int m_probCount = 0;  //実際に捜索した回数。

		//Astarに捜索先をセットする。
		void SetAstarRondomHideObject();

		void ChangeState();
		void RouteEnd();
		void Move();

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartProb();  //捜索開始

		//アクセッサ--------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}
	};

}

//endbasecorss