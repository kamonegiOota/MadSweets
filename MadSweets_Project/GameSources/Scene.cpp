
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"
#include "ItabashiStage.h"
#include "MainStage.h"
#include "TitleStage.h"
#include "LoadStage.h"
#include "OptionStage.h"
#include "GameOverStage.h"
#include "ClearStage.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			//Col.set(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
			Col.set(0.0f / 255.0f, 0.0f / 255.0f, 25.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToLoadStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToItabashiStage")
		{
			ResetActiveStage<ItabashiStage>();
		}
		if (event->m_MsgStr == L"ToLoadStage")
		{
			ResetActiveStage<LoadStage>(L"ToMainStage");
			//ResetActiveStage<LoadStage>(L"ToTitleStage");
		}
		if (event->m_MsgStr == L"ToTitleStage")
		{
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToMargeTestStage")
		{
			ResetActiveStage<MainStage>();
		}
		if (event->m_MsgStr == L"ToMainStage") 
		{
			ResetActiveStage<MainStage>();
		}
		if (event->m_MsgStr == L"ToOptionStage")
		{
			ResetActiveStage<OptionStage>();
		}
		if (event->m_MsgStr == L"ToGameOverStage")
		{
			ResetActiveStage<GameOverStage>();
		}
		if (event->m_MsgStr == L"ToClearStage")
		{
			ResetActiveStage<ClearStage>();
		}
	}

}
//end basecross
