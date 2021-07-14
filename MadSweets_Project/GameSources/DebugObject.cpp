/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugObject.h"

namespace basecross {

	wstringstream DebugObject::m_wss;
	
	void DebugObject::OnCreate() {
		auto sprite = AddComponent<StringSprite>();
		sprite->SetTextRect(Rect2D<float>(10.0f,10.0f,300.0f,300.0f));
		sprite->SetBackColor(Col4(0.5f, 0.5f, 0.5f, 0.5f));
	}

	void DebugObject::OnUpdate() {
		auto sprite = GetComponent<StringSprite>();

		sprite->AddText(m_wss.str());	
		m_wss.str(L"");
	}

	void DebugObject::OnUpdate2() {
		
	}
}