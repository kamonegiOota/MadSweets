/*!
@file MargeTestStage.h
@brief MargeTestStage
�S���ҁF�ێR �T��
*/

#pragma once

namespace basecross {

	class MargeTestStage : public Stage
	{

		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		MargeTestStage() :Stage() {}
		virtual ~MargeTestStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override {}

		virtual void CreateMap(const wstring& fileName);

	};

}

//endbasecross