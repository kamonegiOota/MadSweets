/*!
@file HitEffectManager.cpp
@brief HitEffectManagerÇ»Ç«é¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

#include "HitEffectManager.h"

#include "FluidUVController.h"
#include "AlphaFadeCtrl.h"

namespace basecross {

	//ÉpÉâÉÅÅ[É^----------------------------------------------------------------------------------------

	HitEffectManager::Parametor::Parametor(const wstring& texture)
		:Parametor(texture, Col4(1.0f))
	{}
	HitEffectManager::Parametor::Parametor(const wstring& texture, const Col4& color)
		:Parametor(texture, color, 0.1f)
	{}
	HitEffectManager::Parametor::Parametor(const wstring& texture, const Col4& color, const float& fadeSpeed)
		:Parametor(texture, Vec2(1280.0f, 800.0f), color, fadeSpeed)
	{}
	HitEffectManager::Parametor::Parametor(const wstring& texture, const Vec2& uvSize, const Col4& color, const float& fadeSpeed)
		: texture(texture), uvSize(uvSize), color(color), fadeSpeed(fadeSpeed)
	{}

	//--------------------------------------------------------------------------------------------------


	HitEffectManager::HitEffectManager(const std::shared_ptr<GameObject>& objPtr, const wstring& textrue)
		:HitEffectManager(objPtr, Parametor(textrue))
	{}

	HitEffectManager::HitEffectManager(const std::shared_ptr<GameObject>& objPtr,
		const Parametor& param
	) :
		Component(objPtr), m_param(param)
	{}

	void HitEffectManager::CreateEffect() {
		auto ui = GetStage()->Instantiate<UIObject>();
		auto image = ui->AddComponent<Image>();
		image->SetTextureResource(m_param.texture);
		image->SetDiffuse(m_param.color);
		image->SetAlpha(0.0f);

		auto rectTrans = ui->GetComponent<RectTransform>();
		//rectTrans->SetAnchor(AnchorType::Up);
		//rectTrans->SetPivot(Vec2(0.0f, 1.0f));
		const auto& uvSize = m_param.uvSize;
		rectTrans->SetRectSize(uvSize.x, uvSize.y);

		auto fade = ui->AddComponent<AlphaFadeCtrl>();
		fade->SetFadeObj(ui);
		//ui->AddComponent<FluidUVController>();  //ó¨ÇÍÇÈìÆçÏÇÃtest
		m_effects.push_back(ui);
	}

	void HitEffectManager::OnCreate() {
		CreateEffect();
	}

	void HitEffectManager::OnUpdate() {

	}

	void HitEffectManager::Hit() {
		for (auto effect : m_effects) {
			auto fade = effect->GetComponent<AlphaFadeCtrl>();
			fade->SetSpeed(m_param.fadeSpeed);
			fade->FadeInStart();
		}
	}

}

//endbasecross