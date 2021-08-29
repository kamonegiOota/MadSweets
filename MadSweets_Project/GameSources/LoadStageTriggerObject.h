/*!
@file StageObject.h
@brief ステージに配置するオブジェクトなど　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

class StageObject;

namespace basecross {
	
	class LoadStageTriggerObject : public StageObject
	{
		wstring m_nextMap = L"Stage2.csv";

	public:
		LoadStageTriggerObject(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		) :
			StageObject(stage, name, scale, rotation, position)
		{
		}

		LoadStageTriggerObject(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& map
		) :
			StageObject(stage, name, scale, rotation, position),
			m_nextMap(map)
		{
		}

		void OnCreate() override;
		void OnUpdate() override {};

		void StageReset() override {};

	};

}

//endbasecross