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
				{GraphEdge(0,5)},{GraphEdge(0,7)},{GraphEdge(0,42)},
				{GraphEdge(1,6)},{GraphEdge(1,2)},{GraphEdge(1,42)},
				{GraphEdge(2,1)},{GraphEdge(2,3)},{GraphEdge(2,40)},
				{GraphEdge(3,2)},{GraphEdge(3,4)},
				{GraphEdge(4,3)},{GraphEdge(4,5)},
				{GraphEdge(5,4)},{GraphEdge(5,0)},{GraphEdge(5,11)},
				{GraphEdge(6,1)},{GraphEdge(6,12)},{GraphEdge(6,47)},
				{GraphEdge(7,8)},{GraphEdge(7,0)},
				{GraphEdge(8,7)},{GraphEdge(8,9)},
				{GraphEdge(9,8)},{GraphEdge(9,10)},{GraphEdge(9,13)},{GraphEdge(9,50)},
				{GraphEdge(10,9)},{GraphEdge(10,51)},
				{GraphEdge(11,5)},{GraphEdge(11,51)},
				{GraphEdge(12,13)},{GraphEdge(12,6)},
				{GraphEdge(13,12)},{GraphEdge(13,9)},
				{GraphEdge(14,15)},{GraphEdge(14,32)},{GraphEdge(14,35)},
				{GraphEdge(15,14)},{GraphEdge(15,34)},{GraphEdge(15,31)},
				{GraphEdge(16,17)},{GraphEdge(16,26)},{GraphEdge(16,31)},{GraphEdge(16,23)},
				{GraphEdge(17,16)},                   {GraphEdge(17,18)},
				{GraphEdge(18,19)},{GraphEdge(18,53)},{GraphEdge(18,17)},
				{GraphEdge(19,20)},{GraphEdge(19,18)},{GraphEdge(19,22)},
				{GraphEdge(20,21)},{GraphEdge(20,19)},
				{GraphEdge(21,20)},{GraphEdge(21,22)},
				{GraphEdge(22,21)},{GraphEdge(22,19)},
				{GraphEdge(23,24)},{GraphEdge(23,16)},
				{GraphEdge(24,23)},{GraphEdge(24,25)},
				{GraphEdge(25,24)},
				{GraphEdge(26,16)},{GraphEdge(26,27)},
				{GraphEdge(27,26)},{GraphEdge(27,28)},
				{GraphEdge(28,27)},{GraphEdge(28,29)},
				{GraphEdge(29,31)},{GraphEdge(29,30)},{GraphEdge(29,28)},
				{GraphEdge(30,29)},
				{GraphEdge(31,29)},{GraphEdge(31,15)},{GraphEdge(31,16)},
				{GraphEdge(32,14)},{GraphEdge(32,33)},
				{GraphEdge(33,32)},
				{GraphEdge(34,15)},
				{GraphEdge(35,36)},{GraphEdge(35,38)},{GraphEdge(35,14)},
				{GraphEdge(36,35)},{GraphEdge(36,37)},
				{GraphEdge(37,36)},
				{GraphEdge(38,39)},{GraphEdge(38,35)},{GraphEdge(38,40)},
				{GraphEdge(39,38)},
				{GraphEdge(40,41)},{GraphEdge(40,2)},{GraphEdge(40,38)},
				{GraphEdge(41,40)},
				{GraphEdge(42,43)},{GraphEdge(42,0)},{GraphEdge(42,1)},
				{GraphEdge(43,42)},{GraphEdge(43,44)},{GraphEdge(43,46)},
				{GraphEdge(44,43)},{GraphEdge(44,45)},
				{GraphEdge(45,44)},
				{GraphEdge(46,43)},
				{GraphEdge(47,6)},{GraphEdge(47,48)},
				{GraphEdge(48,47)},{GraphEdge(48,49)},
				{GraphEdge(49,48)},
				{GraphEdge(50,9)},
				{GraphEdge(51,52)},{GraphEdge(51,11)},{GraphEdge(51,10)},
				{GraphEdge(52,51)},
				{GraphEdge(53,18)},{GraphEdge(53,54)},
				{GraphEdge(54,53)},
			}
		},
		{L"Stage2.csv",
			{
				{GraphEdge(0,14)},{GraphEdge(0,26)},
				{GraphEdge(1,27)},{GraphEdge(1,3)},{GraphEdge(1,2)},
				{GraphEdge(2,1)},{GraphEdge(2,25)},
				{GraphEdge(3,1)},{GraphEdge(3,4)},
				{GraphEdge(4,3)},{GraphEdge(4,5)},
				{GraphEdge(5,4)},{GraphEdge(5,6)},
				{GraphEdge(6,5)},{GraphEdge(6,14)},
				{GraphEdge(7,8)},{GraphEdge(7,32)},
				{GraphEdge(8,7)},
				{GraphEdge(9,10)},
				{GraphEdge(10,9)},{GraphEdge(10,39)},
				{GraphEdge(11,12)},{GraphEdge(11,50)},
				{GraphEdge(12,11)},{GraphEdge(12,13)},
				{GraphEdge(13,12)},
				{GraphEdge(14,6)},{GraphEdge(14,0)},{GraphEdge(14,15)},{GraphEdge(14,20)},
				{GraphEdge(15,14)},{GraphEdge(15,16)},{GraphEdge(15,17)},{GraphEdge(15,20)},
				{GraphEdge(16,15)},
				{GraphEdge(17,15)},{GraphEdge(17,18)},{GraphEdge(17,19)},
				{GraphEdge(18,20)},{GraphEdge(18,17)},{GraphEdge(18,21)},{GraphEdge(18,19)},
				{GraphEdge(19,18)},{GraphEdge(19,21)},{GraphEdge(19,17)},{GraphEdge(19,29)},
				{GraphEdge(20,15)},{GraphEdge(20,18)},
				{GraphEdge(21,18)},{GraphEdge(21,19)},{GraphEdge(21,22)},
				{GraphEdge(22,21)},{GraphEdge(22,28)},{GraphEdge(22,23)},
				{GraphEdge(23,22)},{GraphEdge(23,24)},
				{GraphEdge(24,23)},{GraphEdge(24,25)},
				{GraphEdge(25,24)},{GraphEdge(25,2)},
				{GraphEdge(26,0)},{GraphEdge(26,1)},{GraphEdge(26,27)},
				{GraphEdge(27,26)},
				{GraphEdge(28,22)},
				{GraphEdge(29,19)},{GraphEdge(29,30)},{GraphEdge(29,40)},
				{GraphEdge(30,29)},{GraphEdge(30,31)},
				{GraphEdge(31,30)},{GraphEdge(31,32)},
				{GraphEdge(32,31)},{GraphEdge(32,7)},{GraphEdge(32,33)},
				{GraphEdge(33,32)},{GraphEdge(33,34)},
				{GraphEdge(34,33)},{GraphEdge(34,35)},{GraphEdge(34,36)},
				{GraphEdge(35,34)},
				{GraphEdge(36,34)},{GraphEdge(36,37)},
				{GraphEdge(37,36)},{GraphEdge(37,38)},{GraphEdge(37,39)},
				{GraphEdge(38,37)},
				{GraphEdge(39,37)},{GraphEdge(39,10)},
				{GraphEdge(40,29)},{GraphEdge(40,41)},
				{GraphEdge(41,40)},{GraphEdge(41,42)},{GraphEdge(41,43)},
				{GraphEdge(42,41)},
				{GraphEdge(43,41)},{GraphEdge(43,44)},
				{GraphEdge(44,43)},{GraphEdge(44,45)},
				{GraphEdge(45,44)},{GraphEdge(45,46)},
				{GraphEdge(46,45)},{GraphEdge(46,47)},{GraphEdge(46,50)},
				{GraphEdge(47,46)},{GraphEdge(47,48)},
				{GraphEdge(48,47)},{GraphEdge(48,49)},
				{GraphEdge(49,48)},
				{GraphEdge(50,46)},{GraphEdge(50,10)},{GraphEdge(50,51)},
				{GraphEdge(51,50)},{GraphEdge(51,52)},{GraphEdge(51,53)},
				{GraphEdge(52,51)},
				{GraphEdge(53,51)},{GraphEdge(53,54)},
				{GraphEdge(54,53)},{GraphEdge(54,55)},
				{GraphEdge(55,54)},
			}
		},
		{L"Stage3.csv",
			{
				{GraphEdge(0,1)},{GraphEdge(0,13)},
				{GraphEdge(1,0)},{GraphEdge(1,2)},
				{GraphEdge(2,1)},{GraphEdge(2,16)},{GraphEdge(2,3)},{GraphEdge(2,18)},
				{GraphEdge(3,2)},{GraphEdge(3,19)},{GraphEdge(3,4)},
				{GraphEdge(4,3)},{GraphEdge(4,5)},{GraphEdge(4,23)},
				{GraphEdge(5,4)},{GraphEdge(5,6)},{GraphEdge(5,24)},
				{GraphEdge(6,5)},{GraphEdge(6,7)},{GraphEdge(6,26)},
				{GraphEdge(7,6)},{GraphEdge(7,8)},
				{GraphEdge(8,7)},{GraphEdge(8,9)},{GraphEdge(8,27)},
				{GraphEdge(9,10)},{GraphEdge(9,8)},{GraphEdge(9,29)},
				{GraphEdge(10,9)},{GraphEdge(10,11)},
				{GraphEdge(11,12)},{GraphEdge(11,10)},{GraphEdge(11,14)},
				{GraphEdge(12,11)},{GraphEdge(12,13)},
				{GraphEdge(13,12)},{GraphEdge(13,0)},
				{GraphEdge(14,11)},{GraphEdge(14,15)},
				{GraphEdge(15,14)},
				{GraphEdge(16,15)},{GraphEdge(16,17)},
				{GraphEdge(17,16)},
				{GraphEdge(18,2)},{GraphEdge(18,19)},
				{GraphEdge(19,3)},{GraphEdge(19,18)},{GraphEdge(19,20)},
				{GraphEdge(20,19)},{GraphEdge(20,21)},
				{GraphEdge(21,20)},{GraphEdge(21,22)},
				{GraphEdge(22,21)},{GraphEdge(22,23)},
				{GraphEdge(23,22)},{GraphEdge(23,4)},
				{GraphEdge(24,5)},{GraphEdge(24,25)},
				{GraphEdge(25,24)},
				{GraphEdge(26,6)},
				{GraphEdge(27,8)},{GraphEdge(27,28)},
				{GraphEdge(28,27)},
				{GraphEdge(29,9)},{GraphEdge(29,30)},
				{GraphEdge(30,29)},{GraphEdge(30,31)},
				{GraphEdge(31,30)},{GraphEdge(31,32)},
				{GraphEdge(32,31)},
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