/*!
@file CaraSounder.cpp
@brief CaraSounder‚ÌƒNƒ‰ƒXŽÀ‘Ì
’S“–FŠÛŽR—TŠì
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