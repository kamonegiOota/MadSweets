/*!
@file CaraSounder.h
@brief CaraSounder
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class SoundEmitter;

	class CaraSounder : public Component
	{
		//ex_weak_ptr<SoundEmitter> m_soundEmitter;

	public:

		CaraSounder(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnStart() override;

		void AttackSound();

	};

}

//endbasecross