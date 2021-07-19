/*!
@file StageObject.h
@brief ステージに配置するオブジェクトなど　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
//#include "AdvanceGameObject.h"

namespace basecross {

	class StageObject : public GameObject
	{
	protected:

		wstring m_name;

		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;

	public:
		StageObject(const std::shared_ptr<Stage>& stage,
			const wstring& name
		) :
			StageObject(stage, name, Vec3(1.0f), Vec3(0.0f), Vec3(0.0f))
		{
		}

		StageObject(const std::shared_ptr<Stage>& stage,
			const wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		) :
			GameObject(stage),
			m_name(name),
			m_scale(scale),
			m_rotation(rotation),
			m_position(position)
		{
		}

		virtual void OnCreate() override;

		virtual void StageReset() {};

		//アクセッサ

		const wstring& GetName() const
		{
			return m_name;
		}

	};

}

//endbasecross