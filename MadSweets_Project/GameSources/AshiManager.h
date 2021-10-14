/*!
@file AshiManager.h
@brief AshiManager
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "I_Escape.h"
#include "I_ReturnPlowling.h"

namespace basecross {

	class AshiManager : public BaseEnemy, public I_Escape, public I_ReturnPlowling
	{

	public:

		AshiManager(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		//インターフェースの実装---------------------------------------------------

		//逃げるインターフェース
		void StartEscape() override;
		void SuccessEscape() override;

		//元の場所に戻る行為スタート
		void StartReturnPlowling() override;
		void EndReturnPlowling() override;
	};

}

//endbasecross