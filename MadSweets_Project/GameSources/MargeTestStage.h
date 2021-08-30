/*!
@file MargeTestStage.h
@brief MargeTestStage
担当者：丸山 裕喜
*/

#pragma once

#include "AlphaFadeCtrl.h"
#include "StageMapCSV.h"

#include "GraphAstar.h"
#include "PlayerObject.h"

namespace basecross {

	class MargeTestStage : public Stage
	{
		//wstring m_nowMap;
		std::shared_ptr<StageMapCSV> m_mapCsv;
		std::shared_ptr<PlayerObject> m_player;

		//ビューの作成
		void CreateViewLight();

		virtual void CreateMap(const wstring& fileName, const Vec3& offset = Vec3(0.0f));
		virtual GraphAstar CreateAstar();
		//virtual void DeleteMap();

	public:
		//構築と破棄
		MargeTestStage() :Stage() {}
		virtual ~MargeTestStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//ステージの変更
		virtual void ChangeMap(const wstring& fileName,const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset = Vec3(0.0f));

		//テスト用-----------------------------------------------------------
		virtual void TempLoad();
		void CreateEnemy(const std::shared_ptr<GameObject>& player);
		void CreateEatItems();
		void CreatePointLight();
		void CreateSoundCookies();
		void CreateCrackCookies();
		void CreateHideObjects();
	};

}

//endbasecross