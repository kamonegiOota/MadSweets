/*!
@file OriginalMeshObject.h
@brief OriginalMeshObjectクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
//#include "AdvanceComponent.h"

namespace basecross {

	class OriginalMeshObject : public StageObject
	{
		wstring m_mesh;

	public:
		OriginalMeshObject(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& mesh
		) :
			StageObject(stage, name, scale, rotation, position),
			m_mesh(name)
		{}

		void OnCreate() override;

	};

}

//endbasecross