/*!
@file StageMap.h
@brief �Q�[���X�e�[�W�\�z�p�̃N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "LoadData.h"
#include "DebugObject.h"

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
			TorRotDirect,
			TorRotDegree,
			TorFrontRoom,
			TorBackRoom,
			tiling,
		};

		enum RotBoxIndex {
			RoomMember = CsvIndex::texture + 1,
		};

		wstring m_folderName;
		wstring m_fileName;
		CsvFile m_csvFile;

		std::vector<std::shared_ptr<StageObject>> m_stageObjs;

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

		void AddStageObject(const std::shared_ptr<StageObject>& obj) {
			m_stageObjs.push_back(obj);
		}

		//�}�b�v��ɃI�u�W�F�N�g�𐶐�
		template<class T>
		void CreateObject(const wstring& objName, const Vec3& offset = Vec3(0.0f))
		{
			vector<wstring> lineVec;
			m_csvFile.GetSelect(lineVec, 0, objName);

			for (auto& line : lineVec)
			{
				vector<wstring> tokens;
				Util::WStrToTokenVector(tokens, line, L',');

				Vec3 scale(     //�X�P�[���̎擾
					static_cast<float>(_wtof(tokens[CsvIndex::scaleX].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::scaleY].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::scaleZ].c_str()))
				);

				Vec3 rotation(  //���[�e�[�V�����擾
					XMConvertToRadians(static_cast<float>(_wtof(tokens[CsvIndex::rotX].c_str()))),
					XMConvertToRadians(static_cast<float>(_wtof(tokens[CsvIndex::rotY].c_str()))),
					XMConvertToRadians(static_cast<float>(_wtof(tokens[CsvIndex::rotZ].c_str())))
				);

				Vec3 position(  //�|�W�V�����擾
					static_cast<float>(_wtof(tokens[CsvIndex::posX].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::posY].c_str())),
					static_cast<float>(_wtof(tokens[CsvIndex::posZ].c_str()))
				);

				wstring texture = tokens[CsvIndex::texture].c_str();  //�e�N�X�`���̎擾
				
				auto stageObj = GetStage()->AddGameObject<T>(objName, scale, rotation, position + offset, texture);  //�I�u�W�F�N�g�̐���
				m_stageObjs.push_back(stageObj);  //�I�u�W�F�N�g�������̃��X�g�ɒǉ�
				//InstantiateSRP<FixedBox>(scale,rotation,position,L"FixedBox");

			}
		}
	};

}
