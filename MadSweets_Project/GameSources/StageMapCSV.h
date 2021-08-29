/*!
@file StageMap.h
@brief ゲームステージ構築用のクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "LoadData.h"
#include "DebugObject.h"

#include "LoadStageTrigger.h"

namespace basecross {

	class StageMapCSV : public GameObject
	{
		enum CsvIndex
		{
			name,
			scaleX, scaleY, scaleZ,
			rotX, rotY, rotZ,
			posX, posY, posZ,
			texture,
		};

		enum LoadStageCsvIndex {
			nextMap = CsvIndex::texture,
			nextPosX, nextPosY, nextPosZ,
		};

		enum RotBoxIndex {
			RoomMember = CsvIndex::texture + 1,
		};

		wstring m_folderName;
		wstring m_fileName;
		map<wstring, CsvFile> m_csvFiles;

		map<wstring ,std::vector<std::shared_ptr<StageObject>>> m_stageObjs;

	public:

		StageMapCSV(const std::shared_ptr<Stage>& stage,
			const std::wstring& folderName,
			const std::wstring& fileName
		) :
			GameObject(stage),
			m_folderName(folderName),
			m_fileName(fileName)
		{}

		void OnCreate() override;

		void LoadCSV();
		//void CreateMap();

		void ResetMap();
		/// <summary>
		/// マップの切り替え
		/// </summary>
		/// <param name="fileName">切り替えたいマップの情報の入ったcsvファイル名</param>
		/// <returns>マップを新規作成する必要がある場合はtureを返す。</returns>
		bool ChangeMap(const wstring& fileName);

		void StageObjectActiveChange(const bool isActive);

		void AddStageObject(const wstring& fileName,const std::shared_ptr<StageObject>& obj) {
			m_stageObjs[fileName].push_back(obj);
		}

		//マップ上にオブジェクトを生成
		template<class T>
		void CreateObject(const wstring& objName, const Vec3& offset = Vec3(0.0f))
		{
			vector<wstring> lineVec;
			m_csvFiles[m_fileName].GetSelect(lineVec, 0, objName);

			for (auto& line : lineVec)
			{
				vector<wstring> tokens;
				Util::WStrToTokenVector(tokens, line, L',');

				Vec3 scale(     //スケールの取得
					static_cast<float>(_wtof(tokens[CsvIndex::scaleX].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::scaleY].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::scaleZ].c_str()))
				);

				Vec3 rotation(  //ローテーション取得
					XMConvertToRadians(static_cast<float>(_wtof(tokens[CsvIndex::rotX].c_str()))),
					XMConvertToRadians(static_cast<float>(_wtof(tokens[CsvIndex::rotY].c_str()))),
					XMConvertToRadians(static_cast<float>(_wtof(tokens[CsvIndex::rotZ].c_str())))
				);

				Vec3 position(  //ポジション取得
					static_cast<float>(_wtof(tokens[CsvIndex::posX].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::posY].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::posZ].c_str()))
				);

				wstring texture = tokens[CsvIndex::texture].c_str();  //テクスチャの取得
				
				auto stageObj = GetStage()->AddGameObject<T>(objName, scale, rotation, position + offset, texture);  //オブジェクトの生成
				m_stageObjs[m_fileName].push_back(stageObj);  //オブジェクトを自分のリストに追加

				//トリガーだったら
				auto loadStageTrigger = stageObj->GetComponent<LoadStageTrigger>(false);
				if (loadStageTrigger) {
					Vec3 pos(  //ポジション取得
						static_cast<float>(_wtof(tokens[LoadStageCsvIndex::nextPosX].c_str())),
						static_cast<float>(_wtof(tokens[LoadStageCsvIndex::nextPosY].c_str())),
						static_cast<float>(_wtof(tokens[LoadStageCsvIndex::nextPosZ].c_str()))
					);
					DebugObject::AddVector(pos);
					loadStageTrigger->SetMovePosition(pos);
				}
			}
		}
	};

}
