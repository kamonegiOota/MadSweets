/*!
@file SearchHidden.h
@brief SearchHiddenなど
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

		//近くのhideObjectの中からランダムに一つ選ぶ
		//excuteObj == 対象外するオブジェクト
		static std::shared_ptr<GameObject> SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange,
			const std::shared_ptr<GameObject>& excluteObj = nullptr);

	};

}

//endbasecross