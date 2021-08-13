/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

#include "FadeChocoCtrl.h"

#include "MyUtility.h"

namespace basecross {

	void FadeChocoCtrl::CreateChocoUI() {
		//�`���R�̏����ݒ�
		m_ui = GetStage()->Instantiate<UIObject>();
		auto image = m_ui->AddComponent<Image>();
		image->SetTextureResource(L"FadeChoco_Tx");
		
		auto rectTrans = m_ui->GetComponent<RectTransform>();
		rectTrans->SetAnchor(AnchorType::Up);
		rectTrans->SetPivot(Vec2(0.0f, 1.0f));
		rectTrans->SetRectSize(m_uiSize.x, 0.0f);
	}

	void FadeChocoCtrl::FadeUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto rectTrans = m_ui->GetComponent<RectTransform>();
		auto height = rectTrans->GetHeight();
		height += m_direct * m_speed * delta;

		//�I���̔��f������֐�
		m_updateEndFunc(*this, height);

		rectTrans->SetHeight(height);
	}

	void FadeChocoCtrl::EndFadeIn(float& height) {
		if (height < 0.0f) {
			height = 0.0f;
			EndProcess();
		}
	}

	void FadeChocoCtrl::EndFadeOut(float& height) {
		if (height >= m_maxSize) {
			height = m_maxSize;
			EndProcess();
		}
	}

	void FadeChocoCtrl::EndProcess() {
		m_isEnd = true;
		m_updateFunc = nullptr;
		m_updateEndFunc = nullptr;

		m_endAction();
		m_endAction.Clear();
	}

	void FadeChocoCtrl::OnCreate() {
		CreateChocoUI();
	}

	void FadeChocoCtrl::OnUpdate() {
		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

	void FadeChocoCtrl::FadeInStart() {
		auto rectTrans = m_ui->GetComponent<RectTransform>();
		rectTrans->SetAnchor(AnchorType::Down);
		rectTrans->SetPivot(Vec2(0.0f, 1.0f));
		rectTrans->SetRectSize(m_uiSize.x, m_maxSize); //maxSize�͕ϐ��ɂ���B
		rectTrans->SetRotation(XM_PI);
		rectTrans->SetPosition(0.0f, 0.0f);
		m_direct = -1.0f;

		m_updateFunc = &FadeChocoCtrl::FadeUpdate;
		m_updateEndFunc = &FadeChocoCtrl::EndFadeIn;
		m_isEnd = false;
	}

	void FadeChocoCtrl::FadeOutStart() {
		auto rectTrans = m_ui->GetComponent<RectTransform>();
		rectTrans->SetAnchor(AnchorType::Up);
		rectTrans->SetPivot(Vec2(0.0f, 1.0f));
		rectTrans->SetRectSize(m_uiSize.x, 0.0f);
		rectTrans->SetRotation(0.0f);
		rectTrans->SetPosition(0.0f, 0.0f);
		m_direct = 1.0f;

		m_updateFunc = &FadeChocoCtrl::FadeUpdate;
		m_updateEndFunc = &FadeChocoCtrl::EndFadeOut;
		m_isEnd = false;
	}

	

}

//endbasecross