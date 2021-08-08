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
#include "TitleNameCtrl.h"
#include "TitleNameObject.h"
#include "TitleFadeCtrl.h"
#include "FadeChocoCtrl.h"
#include "MyUtility.h"

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
		Instantiate<TitleNameObject>();
	}

	void TitleStage::CreateFadeCtrl() {
		//TitleFadeCtrl�𐶐�
		Instantiate<GameObject>()->AddComponent<TitleFadeCtrl>();

		//�`���R�t�F�[�h�̎���
		Instantiate<GameObject>()->AddComponent<FadeChocoCtrl>();
	}

	void TitleStage::ChangeStage() {
		//�����I�ɂ�������Ƃ���Inputer��p��
		auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();

		if (key.IsInputDown(itbs::Input::KeyCode::F)) {
			auto fade = maru::MyUtility::GetComponent<TitleFadeCtrl>();
			fade->FadeStart();
		}
	}

	void TitleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			LoadData();

			CreateTitle();
			CreateFadeCtrl();

			AddGameObject<DebugObject>();
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		ChangeStage();
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
		app->RegisterTexture(L"TitleChoco_Tx", textureDir + L"TitleChoco.png");
		app->RegisterTexture(L"FadeChoco_Tx", textureDir + L"FadeChoco.png");

	}

}

//endbasecross