
/*!
@file MargeTestStage.h
@brief MargeTestStage
�S���ҁF�ێR �T��
*/

#include "MargeTestStage.h"
#include "StageMapCSV.h"
#include "FixedBox.h"

#include "DebugObject.h"

#include "PlayerObject.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void MargeTestStage::CreateViewLight() {
		const Vec3 eye(0.0f, +15.0f, -30.0f);
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

	void MargeTestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
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