
/*!
@file MargeTestStage.h
@brief MargeTestStage
担当者：丸山 裕喜
*/

#include "MargeTestStage.h"
#include "StageMapCSV.h"
#include "FixedBox.h"

#include "DebugObject.h"

#include "PlayerObject.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void MargeTestStage::CreateViewLight() {
		const Vec3 eye(0.0f, +15.0f, -30.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void MargeTestStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateMap(L"TempStage.csv");

			Instantiate<PlayerObject>(Vec3(0.0f, 0.0f, 0.0f),Quat());

			AddGameObject<DebugObject>();
		}
		catch (...) {
			throw;
		}
	}

	void MargeTestStage::CreateMap(const wstring& fileName)
	{
		auto map = AddGameObject<StageMapCSV>(L"MapDatas/", fileName);

		map->CreateObject<FixedBox>(L"StageRotBox");
		map->CreateObject<FixedBox>(L"Plane");
	}

}

//endbasecross