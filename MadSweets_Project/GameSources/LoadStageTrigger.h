
/*!
@file LoadData.h
@brief ���[�h�f�[�^�w�b�_�@
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "AlphaFadeCtrl.h"
#include "AlphaFadeObject.h"

namespace basecross {

	class LoadStageTrigger : public Component
	{
		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;

		wstring m_nextMap;

		void ChangeStage();
		void FadeStart();

	public:
		LoadStageTrigger(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override {}
		
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

		//�A�N�Z�b�T---------------------------------------------------------------
		void SetNextMap(const wstring& nextMap) {
			m_nextMap = nextMap;
		}
	};

}

//basecross