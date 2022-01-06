
/*!
@file Number.h
@brief Numberクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Number : public Component
	{
		int m_number;
		float m_width = +50.0f;
		float m_height = +100.0f;
		float m_size = 1.0f;
		Col4 m_color = Col4(1.0f,1.0f,1.0f,0.5f);

		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		void CreateMesh();

	public:
		Number(const std::shared_ptr<GameObject>& objPtr, const int& number)
			:Component(objPtr),m_number(number)
		{}

		void OnCreate() override {}
		void OnStart() override;
		void OnUpdate() override;

		//アクセッサ------------------------------------------------------

		void SetNumber(const int& number);
		int GetNumber() const {
			return m_number;
		}

		void SetSize(const float& size) {
			m_size = size;
		}
		float GetSize() const {
			return m_size;
		}
	};

}

//endbasecross