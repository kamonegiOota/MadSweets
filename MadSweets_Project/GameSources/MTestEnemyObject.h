/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MTestEnemyObject : public GameObject
	{


	public:
		MTestEnemyObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;


		//アクセッサ-----------------------------------------------------------
		void SetColor(const Col4& color) {
			auto draw = GetComponent<BcPNTStaticDraw>();
			draw->SetDiffuse(color);
		}

		//徘徊行動テスト
		void StartPlowlingTest();

		//ステート変更テスト
	};

}

//endbasecross