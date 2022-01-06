/*!
@file TitleStage.h
@brief TitleStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class TitleStage : public Stage {

		//�r���[�̍쐬
		void CreateViewLight();

		void CreateTitle();
		void CreateFadeCtrl(std::shared_ptr<Button>& startButton, std::shared_ptr<Button>& goOptionButton);

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void GoOption();
	};

}

//endbasecross