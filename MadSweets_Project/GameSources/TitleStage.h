/*!
@file MaruStage.h
@brief MaruStage
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
		void ChangeStage();

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;


	private:
		//�e�X�g�����p�̊֐�----------------------------------------------------
		void LoadData();
	};

}

//endbasecross