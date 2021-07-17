#include"ItabashiStage.h"
#include"PlayerObject.h"

namespace basecross
{
	void ItabashiStage::OnCreate()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

		std::wstring mediaDir = App::GetApp()->GetDataDirWString();
		auto& app = App::GetApp();

		//���f��
		std::wstring modelDir = mediaDir + L"Models\\";
		auto modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandStay\\", L"PlayerStandStay.bmf");
		app->RegisterResource(L"PlayerStandStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\CrouchStay\\", L"PlayerCrouchStay.bmf");
		app->RegisterResource(L"PlayerCrouchStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandToCrouch\\", L"PlayerStandToCrouch.bmf");
		app->RegisterResource(L"PlayerStandToCrouch", modelMesh);

		auto playerObject = Instantiate<PlayerObject>();

		std::vector<std::shared_ptr<GameObject>> gameobjects;

		for (int i = 0; i < 4; i++)
		{
			auto gameobject = Instantiate<GameObject>();

			auto draw = gameobject->AddComponent<PNTStaticDraw>();
			draw->SetMeshResource(L"DEFAULT_CUBE");

			auto collision = gameobject->AddComponent<CollisionObb>();
			collision->SetFixed(true);
			gameobjects.push_back(gameobject);
		}

		gameobjects[0]->GetComponent<Transform>()->SetPosition(-2, 0, -2);
		gameobjects[1]->GetComponent<Transform>()->SetPosition( 2, 0, -2);
		gameobjects[2]->GetComponent<Transform>()->SetPosition(-2, 0,  2);
		gameobjects[3]->GetComponent<Transform>()->SetPosition( 2, 0,  2);
	}
}