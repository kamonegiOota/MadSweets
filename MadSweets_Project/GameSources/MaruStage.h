/*!
@file MaruStage.h
@brief MaruStage
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MaruStage : public Stage {

		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		MaruStage() :Stage() {}
		virtual ~MaruStage() {}
		//初期化
		virtual void OnCreate()override;


		//テスト実装用の関数----------------------------------------------------
		void CreateGraphTest();
	};

}

//endbasecross