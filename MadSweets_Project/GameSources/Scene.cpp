
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"
#include "ItabashiStage.h"
#include"MargeTestStage.h"
#include"TitleStage.h"
#include "LoadStage.h"
#include"OptionStage.h"
#include"GameOverStage.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToLoadStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToItabashiStage")
		{
			ResetActiveStage<ItabashiStage>();
		}
		if (event->m_MsgStr == L"ToLoadStage")
		{
			ResetActiveStage<LoadStage>(L"ToMargeTestStage");
		}
		if (event->m_MsgStr == L"ToTitleStage")
		{
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToMargeTestStage")
		{
			ResetActiveStage<MargeTestStage>();
		}

		if (event->m_MsgStr == L"ToOptionStage")
		{
			ResetActiveStage<OptionStage>();
		}

		if (event->m_MsgStr == L"ToGameOverStage")
		{
			ResetActiveStage<GameOverStage>();
		}
	}

}
//end basecross
