#include"ItabashiStage.h"
#include"PlayerObject.h"
#include"PlayerCameraObject.h"

namespace basecross
{
	void ItabashiStage::OnCreate()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
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

		auto playerObject = AddGameObject<PlayerObject>();
		auto cameraObject = AddGameObject<PlayerCameraObject>();
		cameraObject->SetParent(playerObject);

	}
}