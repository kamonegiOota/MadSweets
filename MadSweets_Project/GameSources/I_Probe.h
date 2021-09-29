/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "BaseEnemy.h"

namespace basecross {

	class I_Probe {

	public:

		virtual void StartProbe() = 0;
		virtual void EndProbe() = 0;

		/// <summary>
		/// �B���I�u�W�F�N�g�̒���`������
		/// </summary>
		virtual void HideSearchAnimationStart() = 0;
	};

	

}

//endbasecross