/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"

#include "BaseUseVelocity.h"
#include "AstarCtrl.h"

namespace basecross {

	//探索中にAstarを利用して移動したい時のコンポーネント
	class ProbeAstarMove : public Component , public BaseUseVelocity
	{

		void Rotation(const Vec3& moveVec);

	public:

		ProbeAstarMove(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override{}

		//Astarを利用した移動
		void Move();
		//ルートの構築
		void CalucRoute(const std::shared_ptr<GameObject>& target);


		//アクセッサ-----------------------------------------------------------
		bool IsRouteEnd() const {
			auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
			return astar->IsRouteEnd();
		}

	};

}

//endbasecross