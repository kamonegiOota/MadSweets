/*!
@file I_Probe.h
@brief I_Probe
�S���ҁF�ێR �T��
*/

#pragma once

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