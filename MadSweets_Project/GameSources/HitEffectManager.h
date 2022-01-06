/*!
@file HitEffectManager.h
@brief HitEffectManagerなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class HitEffectManager : public Component
	{
	public:

		struct Parametor {
			std::wstring texture = L"";
			Vec2 uvSize = Vec2(1280.0f, 800.0f);
			Col4 color = Col4(1.0f);
			float fadeSpeed = 0.1f;
			float fadeStartAlpha = 1.0f;

			Parametor(const wstring& texture);
			Parametor(const wstring& texture, const Col4& color);
			Parametor(const wstring& texture, const Col4& color, const float& fadeSpeed);
			Parametor(const wstring& texture, const Col4& color, const float& fadeSpeed, const float& fadeStartAlpha);
			Parametor(const wstring& texture, const Vec2& uvSize, const Col4& color, const float& fadeSpeed, const float& fadeStartAlpha);
		};

	private:

		Parametor m_param;
		std::vector<ex_weak_ptr<UIObject>> m_effects;

		void CreateEffect();

	public:

		HitEffectManager(const std::shared_ptr<GameObject>& objPtr, const wstring& textrue);
		HitEffectManager(const std::shared_ptr<GameObject>& objPtr, const Parametor& param);

		void OnCreate() override;
		void OnUpdate() override;
 
		//Hit時の処理
		void Hit();

		//アクセッサ---------------------------------------------------------

		void AddEffect(const std::shared_ptr<UIObject>& effect) {
			m_effects.push_back(effect);
		}

		void SetParametor(const Parametor& param) {
			m_param = param;
		}
		Parametor GetParametor() const {
			return m_param;
		}

		void SetFadeSpeed(const float& speed) {
			m_param.fadeSpeed = speed;
		}
		float GetFadeSpeed() const {
			return m_param.fadeSpeed;
		}
	};

}

//endbasecross