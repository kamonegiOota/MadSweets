
/*!
@file Number.cpp
@brief Number�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "Number.h"

namespace basecross {

	void Number::CreateMesh() {
		float fNumber = static_cast<float>(m_number);
		float width = m_size;
		float height = -m_size;

		m_vertices = {
			{Vec3(0.0f, 0.0f, 0.0f),    m_color, Vec2(m_width * fNumber / 512.0f       , 300.0f / 512.0f)},
			{Vec3(width , 0.0f, 0.0f),  m_color, Vec2(m_width * (fNumber + 1) / 512.0f , 300.0f / 512.0f)},
			{Vec3(0.0f, height, 0.0f),  m_color, Vec2(m_width * fNumber / 512.0f       , 400.0f / 512.0f)},
			{Vec3(width, height, 0.0f), m_color, Vec2(m_width * (fNumber + 1) / 512.0f , 400.0f / 512.0f)},
		};
		
		m_indices = {
			0, 1, 2,
			2, 1, 3
		};
	}

	void Number::OnStart() {
		wstring texture = L"Number_Tx";
		auto obj = GetGameObject();
		auto draw = obj->AddComponent<PCTStaticDraw>();

		CreateMesh();

		//���b�V���̐���
		draw->CreateOriginalMesh(m_vertices, m_indices);
		draw->SetOriginalMeshUse(true);
		draw->SetTextureResource(texture);

		GetGameObject()->SetAlphaActive(true);
	}

	void Number::OnUpdate() {

	}

	void Number::SetNumber(const int& number) {
		m_number = number;

		// UV���W���X�V����
		float fNumber = static_cast<float>(number);
		m_vertices[0].textureCoordinate = Vec2((fNumber + 0) * m_width / 512.0f, 300.0f / 512.0f);
		m_vertices[1].textureCoordinate = Vec2((fNumber + 1) * m_width / 512.0f, 300.0f / 512.0f);
		m_vertices[2].textureCoordinate = Vec2((fNumber + 0) * m_width / 512.0f, 400.0f / 512.0f);
		m_vertices[3].textureCoordinate = Vec2((fNumber + 1) * m_width / 512.0f, 400.0f / 512.0f);

		// �V�������_�f�[�^�Ń��b�V�����X�V����
		auto drawComp = GetGameObject()->GetComponent<PCTStaticDraw>();
		drawComp->UpdateVertices(m_vertices);
	}
}

//endbasecross