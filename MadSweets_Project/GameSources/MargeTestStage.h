/*!
@file MargeTestStage.h
@brief MargeTestStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "AlphaFadeCtrl.h"
#include "StageMapCSV.h"

namespace basecross {

	class MargeTestStage : public Stage
	{
		wstring m_nowMap;
		std::shared_ptr<StageMapCSV> m_mapCsv;

		//�r���[�̍쐬
		void CreateViewLight();

		virtual void CreateMap(const wstring& fileName, const Vec3& offset = Vec3(0.0f));
		virtual void DeleteMap();

	public:
		//�\�z�Ɣj��
		MargeTestStage() :Stage() {}
		virtual ~MargeTestStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�X�e�[�W�̕ύX
		virtual void ChangeMap(const wstring& fileName,const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset = Vec3(0.0f));

		//�e�X�g�p-----------------------------------------------------------
		virtual void TempLoad();
		void CreateEnemy(const std::shared_ptr<GameObject>& player);
		void CreateEatItems();
		void CreatePointLight();
		void CreateSoundCookies();
		void CreateCrackCookies();
		void CreateHideObjects();
	};

}

//endbasecross