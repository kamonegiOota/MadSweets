/*!
@file MaruStage.h
@brief MaruStage
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class TitleStage : public Stage {

		//ビューの作成
		void CreateViewLight();

		void CreateTitle();
		void ChangeStage();

	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;


	private:
		//テスト実装用の関数----------------------------------------------------
		void LoadData();
	};

}

//endbasecross