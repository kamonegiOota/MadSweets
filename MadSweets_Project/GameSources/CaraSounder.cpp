/*!
@file CaraSounder.cpp
@brief CaraSounder�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "SoundHelper.h"
#include "CaraSounder.h"

namespace basecross {

	void CaraSounder::OnStart() {
		//m_soundEmitter = GetGameObject()->GetComponent<SoundEmitter>();
	}

	void CaraSounder::AttackSound() {
		SimpleSoundManager::OnePlaySE(L"CookieCrushSE", 30.0f);
	}

}

//endbasecross