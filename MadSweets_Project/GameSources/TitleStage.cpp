/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "TitleStage.h"

#include "MTestEnemyObject.h"
#include "DebugObject.h"

#include "UIHelper.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -15.0f);
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
	}

	void TitleStage::CreateTitle() {
		//�^�C�g���̉摜�̕\��
		auto ui = Instantiate<UIObject>();
		auto image = ui->AddComponent<Image>();
		image->SetTextureResource(L"TitleFont_Tx");
		image->GetGameObject()->GetComponent<RectTransform>()->SetRectSize(512.0f,256.0f);
	}

	void TitleStage::ChangeStage() {

	}

	void TitleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			LoadData();

			CreateTitle();

			AddGameObject<DebugObject>();
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {

	}

	void TitleStage::LoadData() {
		std::wstring mediaDir = App::GetApp()->GetDataDirWString();
		auto& app = App::GetApp();

		std::wstring textureDir = mediaDir + L"Textures\\";
		app->RegisterTexture(L"WeightGaugeBackground", textureDir + L"WeightGaugeBackGround.png");
		app->RegisterTexture(L"WeightGaugeColor", textureDir + L"WeightGaugeColor.png");
		app->RegisterTexture(L"WallCake_Tx", textureDir + L"Tx_Cake.png");
		app->RegisterTexture(L"WallCake2_Tx", textureDir + L"Tx_Cake2.png");
		app->RegisterTexture(L"WallCake3_Tx", textureDir + L"Tx_Cake3.png");
		app->RegisterTexture(L"WallSponge_Tx", textureDir + L"Tx_Sponge.png");
		app->RegisterTexture(L"WallSponge2_Tx", textureDir + L"Tx_Sponge2.png");
		app->RegisterTexture(L"TitleFont_Tx", textureDir + L"TitleFont.png");
		app->RegisterTexture(L"Title_Tx", textureDir + L"TitleChoco.png");

	}

}

//endbasecross