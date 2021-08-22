/*!
@file StageMap.cpp
@brief ゲームステージ構築用のクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "ResetStageObj.h"
#include "LoadData.h"
#include "StageMapCSV.h"

namespace basecross {

	void StageMapCSV::OnCreate()
	{
		//デバック用
		//auto debug = AddComponent<StringSprite>();
		//debug->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		//debug->SetTextRect(Rect2D<float>(10.0f, 10.0f, 300.0f, 300.0f));

		LoadCSV();
		//CreateMap();

	}

	void StageMapCSV::LoadCSV()
	{
		auto load = LoadData(m_folderName);
		load.LoadCSV(m_csvFile,m_fileName);
		m_csvFile.ReadCsv();
	}


	void StageMapCSV::ResetMap()
	{
		//for (auto& obj : m_stageObjs)
		//{
		//	//obj->GetComponent<Collision>()->SetUpdateActive(false);
		//	obj->GetComponent<ResetStageObj>()->ResetAll();
		//	obj->StageReset();
		//	//GetStage()->RemoveGameObject<GameObject>(obj);
		//}

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

		//for (auto& obj : m_stageObjs)
		//{
		//	//obj->GetComponent<Collision>()->SetUpdateActive(true);
		//}

		//m_stageObjs.clear();
	}

	void StageMapCSV::CollisionOffAll(const wstring& name) {
		for (auto& obj : m_stageObjs) {
			auto col = obj->GetComponent<Collision>();
			if (col) {
				col->SetUpdateActive(false);
			}
		}
	}
}