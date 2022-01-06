#pragma once

/*!
@file CookieHideObject.h
@brief CookieHideObject�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {

	class CookieHideObject : public StageObject
	{
		wstring m_mesh;
		
	public:

		//CookieHideObject(const std::shared_ptr<Stage>& stage, const wstring& name)
		//	:GameObject(stage), m_mesh(name)
		//{}

		CookieHideObject(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& texture
		) :
			StageObject(stage, name, scale, rotation, position),
			m_mesh(name)
		{
		}

		void OnCreate() override;
	};

}

//endbasecross