/*!
@file MaruStage.cpp
@brief MaruStage����
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MaruStage : public Stage {

		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		MaruStage() :Stage() {}
		virtual ~MaruStage() {}
		//������
		virtual void OnCreate()override;


		//�e�X�g�����p�̊֐�----------------------------------------------------
		void CreateGraphTest();
	};

}

//endbasecross