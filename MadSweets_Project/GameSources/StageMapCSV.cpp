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

	map<wstring, vector<GraphEdge>> StageMapCSV::sm_astarEdges = {
		{L"Stage1.csv",
			{
				{GraphEdge(0,1)},{GraphEdge(0,5)},{GraphEdge(0,7)},
				{GraphEdge(1,0)},{GraphEdge(1,12)},{GraphEdge(1,2)},
				{GraphEdge(2,1)},{GraphEdge(2,3)},
				{GraphEdge(3,2)},{GraphEdge(3,4)},
				{GraphEdge(4,3)},{GraphEdge(4,5)},
				{GraphEdge(5,4)},{GraphEdge(5,0)},{GraphEdge(5,11)},
				{GraphEdge(6,1)},{GraphEdge(6,12)},
				{GraphEdge(7,1)},{GraphEdge(7,8)},
				{GraphEdge(8,7)},{GraphEdge(8,9)},{GraphEdge(8,12)},
				{GraphEdge(9,8)},{GraphEdge(9,13)},
				{GraphEdge(10,11)},
				{GraphEdge(11,10)},{GraphEdge(11,5)},
				{GraphEdge(12,6)},{GraphEdge(12,13)},{GraphEdge(12,8)},
				{GraphEdge(13,12)},{GraphEdge(13,9)},
				{GraphEdge(14,15)},
				{GraphEdge(15,14)},{GraphEdge(15,16)},
				{GraphEdge(16,15)},{GraphEdge(16,17)},
				{GraphEdge(17,16)},
			}
		},
		{L"Stage2.csv",
			{
				//{GraphEdge(0,1)},{GraphEdge(0,5)},{GraphEdge(0,7)},
				//{GraphEdge(1,0)},{GraphEdge(1,12)},{GraphEdge(1,2)},
				//{GraphEdge(2,1)},{GraphEdge(2,3)},
				//{GraphEdge(3,2)},{GraphEdge(3,4)},
				//{GraphEdge(4,3)},{GraphEdge(4,5)},
				//{GraphEdge(5,4)},{GraphEdge(5,0)},{GraphEdge(5,11)},
				//{GraphEdge(6,1)},{GraphEdge(6,12)},
				//{GraphEdge(7,1)},{GraphEdge(7,8)},
				//{GraphEdge(8,7)},{GraphEdge(8,9)},{GraphEdge(8,12)},
				//{GraphEdge(9,8)},{GraphEdge(9,13)},
				//{GraphEdge(10,11)},
				//{GraphEdge(11,10)},{GraphEdge(11,5)},
				//{GraphEdge(12,6)},{GraphEdge(12,13)},{GraphEdge(12,8)},
				//{GraphEdge(13,12)},{GraphEdge(13,9)},
				//{GraphEdge(14,15)},
				//{GraphEdge(15,14)},{GraphEdge(15,16)},
				//{GraphEdge(16,15)},{GraphEdge(16,17)},
				//{GraphEdge(17,16)},
			}
		},
		{L"Stage3.csv",
			{
				//{GraphEdge(0,1)},{GraphEdge(0,5)},{GraphEdge(0,7)},
				//{GraphEdge(1,0)},{GraphEdge(1,12)},{GraphEdge(1,2)},
				//{GraphEdge(2,1)},{GraphEdge(2,3)},
				//{GraphEdge(3,2)},{GraphEdge(3,4)},
				//{GraphEdge(4,3)},{GraphEdge(4,5)},
				//{GraphEdge(5,4)},{GraphEdge(5,0)},{GraphEdge(5,11)},
				//{GraphEdge(6,1)},{GraphEdge(6,12)},
				//{GraphEdge(7,1)},{GraphEdge(7,8)},
				//{GraphEdge(8,7)},{GraphEdge(8,9)},{GraphEdge(8,12)},
				//{GraphEdge(9,8)},{GraphEdge(9,13)},
				//{GraphEdge(10,11)},
				//{GraphEdge(11,10)},{GraphEdge(11,5)},
				//{GraphEdge(12,6)},{GraphEdge(12,13)},{GraphEdge(12,8)},
				//{GraphEdge(13,12)},{GraphEdge(13,9)},
				//{GraphEdge(14,15)},
				//{GraphEdge(15,14)},{GraphEdge(15,16)},
				//{GraphEdge(16,15)},{GraphEdge(16,17)},
				//{GraphEdge(17,16)},
			}
		},
	};

	void StageMapCSV::OnCreate()
	{
		//デバック用
		//auto debug = AddComponent<StringSprite>();
		//debug->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		//debug->SetTextRect(Rect2D<float>(10.0f, 10.0f, 300.0f, 300.0f));

		LoadCSV();
		//CreateMap();

	}

	void StageMapCSV::OnUpdate() {
		//wstring fileNames[] = {
		//	L"Stage1.csv",
		//	//L"Stage2.csv",
		//	//L"Stage3.csv"
		//};

		//vector<std::shared_ptr<StageObject>> deleteObjs;

		//for (auto& name : fileNames) {
		//	for (auto& obj : m_stageObjs[name]) {
		//		if (!obj) {
		//			deleteObjs.push_back(obj);
		//		}
		//	}

		//	for (auto& obj : deleteObjs) {
		//		maru::MyUtility::RemoveVec(m_stageObjs[name], obj);
		//	}
		//}
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
		StageObjectActiveChange(false); //現在のステージを当たり判定と見た目をfalse

		m_fileName = fileName;

		//ロード用のCSVが存在しなかったら
		if (m_csvFiles.find(fileName) == m_csvFiles.end()) {
			LoadCSV();  //新しくロード系にセット
			return true;
		}
		else {
			StageObjectActiveChange(true);  //見た目とコリジョンを回復。
			return false;
		}
	}

	void StageMapCSV::StageObjectActiveChange(const bool isActive) {
		for (auto& obj : m_stageObjs[m_fileName]) {
			if (obj) {
				obj->SetUpdateActive(isActive);
				obj->SetDrawActive(isActive);
			}
		}
	}

	vector<Vec3> StageMapCSV::GetPositions(const wstring& objName) {
		vector<Vec3> rePositions;

		vector<wstring> lineVec;
		m_csvFiles[m_fileName].GetSelect(lineVec, 0, objName);

		for (auto& line : lineVec)
		{
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, line, L',');

			Vec3 position(  //ポジション取得
				static_cast<float>(_wtof(tokens[CsvIndex::posX].c_str())),
				static_cast<float>(_wtof(tokens[CsvIndex::posY].c_str())),
				static_cast<float>(_wtof(tokens[CsvIndex::posZ].c_str()))
			);

			rePositions.push_back(position);
		}

		return rePositions;

	}

	vector<wstring> StageMapCSV::GetTextures(const wstring& objName) {

		vector<wstring> reTextrues;

		vector<wstring> lineVec;
		m_csvFiles[m_fileName].GetSelect(lineVec, 0, objName);

		for (auto& line : lineVec)
		{
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, line, L',');

			wstring texture = tokens[CsvIndex::texture].c_str();  //テクスチャの取得

			reTextrues.push_back(texture);
		}

		return reTextrues;
	}
}