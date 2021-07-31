/*!
@file MargeTestStage.h
@brief MargeTestStage
担当者：丸山 裕喜
*/

#pragma once

namespace basecross {

	class MargeTestStage : public Stage
	{

		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		MargeTestStage() :Stage() {}
		virtual ~MargeTestStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void CreateMap(const wstring& fileName);

		//テスト用-----------------------------------------------------------
		virtual void TempLoad();
		void CreateEnemy(const std::shared_ptr<GameObject>& player);
		void CreateEatItems();
		void CreatePointLight();
	};

}

//endbasecross