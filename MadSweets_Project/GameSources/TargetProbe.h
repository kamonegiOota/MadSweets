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
		std::shared_ptr<GameObject> m_target;  //捜索対象
		std::shared_ptr<GameObject> m_checkHideObj;  //チェックしている隠れるオブジェクト

		std::function<void(TargetProbe&)> m_moveFunc;

		//何回プレイヤーの捜索をするか？
		int m_numPorb = 1;
		int m_probCount = 0;  //実際に捜索した回数。

		float m_searchRange = 20.0f;  //探索する範囲

		//Astarに捜索先をセットする。
		void SetAstarRondomHideObject();

		void ChangeState();
		void RouteEnd();

		void TargetMove();
		void AstarMove();

		void ResetProbe();

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartProb();  //捜索開始
		void StartProb(const shared_ptr<GameObject>& target);  //捜索開始

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