
/*!
@file LoadData.h
@brief ���[�h�f�[�^�w�b�_�@
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	struct LoadTxParam   //�e�N�X�`���̃��[�h�p�̍\����
	{
		wstring m_keyName;
		wstring m_fileName;

		LoadTxParam(const wstring& keyName, const wstring& fileName):
			m_keyName(keyName),
			m_fileName(fileName)
		{

		}
	};

	struct LoadSoundParam   //�e�N�X�`���̃��[�h�p�̍\����
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

		//Csv�t�@�C���̃��[�h
		void LoadCSV(CsvFile& csvFile, const wstring& fileName)
		{
			csvFile.SetFileName(m_path + fileName);
		}

		//Csv�t�@�C���̃��[�h
		static void LoadCSV(CsvFile& csvFile, const wstring& folderName, const wstring& fileName);

		//�e�N�X�`���[�̃��[�h�֐�
		void LoadTextures(const vector<LoadTxParam>& params);

		//BGM,SE�̃��[�h
		static void LoadSound(const wstring& folderName, const vector<LoadSoundParam>& params);



		//���f�B�A�̎擾
		static wstring GetMedia()
		{
			auto& app = App::GetApp();
			auto media = app->GetDataDirWString();
			return media;
		}

		//���f���̃��[�h�֐�
		//void LoadModel(const wstring& folderName, const wstring& fileName);

		//void LoadModels();
	};

}

//endbasecross