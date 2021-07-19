/*!
@file FixedBox.h
@brief FixedBoxなど
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {

	class FixedBox : public StageObject
	{
	protected:
		wstring m_texture;

		vector<VertexPositionNormalTexture> m_vertices;
		vector<uint16_t> m_indices;
		
	public:
		FixedBox(const std::shared_ptr<Stage>& stage,
			const std::wstring& name
		) :
			FixedBox(stage, name, L"")
		{
		}

		FixedBox(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const std::wstring& texture
		) :
			StageObject(stage, name),
			m_texture(texture)
		{
		}


		FixedBox(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		) :
			StageObject(stage, name, scale, rotation, position),
			m_texture(L"")
		{
		}

		FixedBox(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& texture
		) :
			StageObject(stage, name, scale, rotation, position),
			m_texture(texture)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;
		
		void StageReset() override {};

		////アクセッサ
		//void SetRotCenter(const std::shared_ptr<GameObject>& target)
		//{
		//	auto targetRot = GetComponent<TargetRotSeek>();
		//	targetRot->SetTarget(target);
		//}
	};

}

//endbasecross