/*!
@file EnemyRotationCtrl.h
@brief EnemyRotationCtrlなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	class SearchHidden
	{
	public:

		//指定した距離内のHiddenObjectを取得
		static vector<std::shared_ptr<GameObject>> SearchNearHiddenObjects(const std::shared_ptr<GameObject>& self, const float& nearRange = 10.0f);

		//SearchHidden(const std::shared_ptr<GameObject>& objPtr)
		//	:Component(objPtr)
		//{}

		//void OnCreate() override {}
		//void OnUpdate() override {}

		//近くのhideObjectの中からランダムに一つ選ぶ
		static std::shared_ptr<GameObject> SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange = 10.0f);

	};

}

//endbasecross