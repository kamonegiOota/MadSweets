/*!
@file StageMap.cpp
@brief �Q�[���X�e�[�W�\�z�p�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "ResetStageObj.h"
#include "LoadData.h"
#include "StageMapCSV.h"

namespace basecross {

	void StageMapCSV::OnCreate()
	{
		//�f�o�b�N�p
		//auto debug = AddComponent<StringSprite>();
		//debug->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		//debug->SetTextRect(Rect2D<float>(10.0f, 10.0f, 300.0f, 300.0f));

		LoadCSV();
		//CreateMap();

	}

	void StageMapCSV::LoadCSV()
	{
		auto load = LoadData(m_folderName);
		load.LoadCSV(m_csvFiles[m_fileName],m_fileName);
		m_csvFiles[m_fileName].ReadCsv();
	}


	void StageMapCSV::ResetMap()
	{
		auto objs = GetStage()->GetGameObjectVec();
		for (auto obj : objs) {
			auto reset = obj->GetComponent<ResetStageObj>(false);
			if (reset) {
				reset->ResetAll();
				auto stageObj = dynamic_pointer_cast<StageObject>(obj);
				if (stageObj) {
					stageObj->StageReset();
				}
			}
		}
	}

	bool StageMapCSV::ChangeMap(const wstring& fileName) {
		StageObjectActiveChange(false); //���݂̃X�e�[�W�𓖂��蔻��ƌ����ڂ�false

		m_fileName = fileName;

		//���[�h�p��CSV�����݂��Ȃ�������
		if (m_csvFiles.find(fileName) == m_csvFiles.end()) {
			LoadCSV();  //�V�������[�h�n�ɃZ�b�g
			return true;
		}
		else {
			StageObjectActiveChange(true);  //�����ڂƃR���W�������񕜁B
			return false;
		}
	}

	void StageMapCSV::StageObjectActiveChange(const bool isActive) {
		for (auto& obj : m_stageObjs[m_fileName]) {
			obj->SetUpdateActive(isActive);
			obj->SetDrawActive(isActive);
		}
	}
}