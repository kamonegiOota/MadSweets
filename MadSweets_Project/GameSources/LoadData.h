
/*!
@file LoadData.h
@brief ロードデータヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	struct LoadTxParam   //テクスチャのロード用の構造体
	{
		wstring m_keyName;
		wstring m_fileName;

		LoadTxParam(const wstring& keyName, const wstring& fileName):
			m_keyName(keyName),
			m_fileName(fileName)
		{

		}
	};

	struct LoadSoundParam   //テクスチャのロード用の構造体
	{
		wstring m_keyName;
		wstring m_fileName;

		LoadSoundParam(const wstring& keyName, const wstring& fileName) :
			m_keyName(keyName),
			m_fileName(fileName)
		{

		}
	};

	struct LoadParam
	{
		wstring m_keyName;
		wstring m_fileName;

		LoadParam(const wstring& keyName, const wstring& fileName) :
			m_keyName(keyName),
			m_fileName(fileName)
		{

		}
	};


	class LoadData
	{
		wstring m_media;
		wstring m_path;

	public:
		
		LoadData() :
			m_path(L"")
		{
			auto& app = App::GetApp();
			m_media = app->GetDataDirWString();
		}

		LoadData(const wstring& folderName) 
		{
			auto& app = App::GetApp();
			m_media = app->GetDataDirWString();
			m_path = m_media + folderName;
		}

		void SwitchPath(const wstring& folderName)
		{
			m_path = m_media + folderName;
		}

		//Csvファイルのロード
		void LoadCSV(CsvFile& csvFile, const wstring& fileName)
		{
			csvFile.SetFileName(m_path + fileName);
		}

		//Csvファイルのロード
		static void LoadCSV(CsvFile& csvFile, const wstring& folderName, const wstring& fileName);

		//テクスチャーのロード関数
		void LoadTextures(const vector<LoadTxParam>& params);

		//BGM,SEのロード
		static void LoadSound(const wstring& folderName, const vector<LoadSoundParam>& params);



		//メディアの取得
		static wstring GetMedia()
		{
			auto& app = App::GetApp();
			auto media = app->GetDataDirWString();
			return media;
		}

		//モデルのロード関数
		//void LoadModel(const wstring& folderName, const wstring& fileName);

		//void LoadModels();
	};

}

//endbasecross