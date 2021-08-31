#include"ClearStage.h"
#include"GameMessageWindowObject.h"
#include"MessageWindow.h"
#include"AlphaFadeCtrl.h"
#include"PlayerInputer.h"

namespace basecross
{
	ClearStage::ClearStage() : Stage() {}

	void ClearStage::FadeInEnd()
	{
		EventSystem::GetInstance(GetThis<Stage>())->PushSelectable(m_messageWindow.GetShard());
		m_messageWindow->PlayMessage();
		
	}

	void ClearStage::FadeOutEnd()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToTitleStage");
	}

	void ClearStage::OnCreate()
	{
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
		//PtrMultiLight->SetAmbientLightColor(Col4(1.0f,0.1f,0.1f,0.1f));

		Vec3 poss[] = {
			{Vec3(0.0f,0.5f,0.0f)},
			{Vec3(0.0f,-0.5f,0.0f)},
			{Vec3(-0.5f,0.0f,0.0f)},
		};

		//���C�g�̐ݒ�
		for (int i = 0; i < 3; i++) {
			auto& light = PtrMultiLight->GetLight(i);
			light.m_DiffuseColor = Col4(0.35f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.35f);
			//light.m_Directional = poss[i];
		}

		auto imageObject = Instantiate<UIObject>();
		imageObject->SetDrawLayer(-100);
		auto rectTransform = imageObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(1280, 800);
		auto image = imageObject->AddComponent<Image>();

		image->SetTextureResource(L"FadeBack_Tx");
		image->SetDiffuse(Col4(0.25f, 0.25f, 0.25f, 1.0f));

		auto messageWindowObject = Instantiate<GameMessageWindowObject>();
		messageWindowObject->SetDrawLayer(0);
		messageWindowObject->GetComponent<RectTransform>()->SetPosition(0, 0);
		m_messageWindow = messageWindowObject->GetComponent<MessageWindow>();

		std::wstring messageText =
			L"���̂����́A�������̂����B�����������������������񂠂�́I\n"
			L"�ł��A�������̂����͂��ǂ���������B\n"
			L"�����A�����ǂ񂾂�A�����͒Z�����ǂ���5�{��������Ă����~�~�~�~�ƁA\n"
			L"�ӂ����Ȃ��悤�̓������܂�ۂ́~�~�~�~�~�~�ɂ͋C�����āB\n"
			L"����͂����Ɓ~�~�́~�~����~�~�~�ꂽ\n"
			L"�ڂ��́A�܂���������ׂ邽�߂ɁA�~�~����";

		m_messageWindow->SetMessageText(messageText);

		auto alphaFade = Instantiate<UIObject>()->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(2.0f);
		alphaFade->AddEndAction(GetThis<ClearStage>(), &ClearStage::FadeInEnd);
		alphaFade->FadeInStart();

		auto uiobject = Instantiate<UIObject>();
		uiobject->SetDrawLayer(1000);
		alphaFade = uiobject->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(2.0f);
		alphaFade->AddEndAction(GetThis<ClearStage>(), &ClearStage::FadeOutEnd);

		m_messageWindow->finishPushEvent.AddFunc(alphaFade, &AlphaFadeCtrl::FadeOutStart);

		EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());
	}
}