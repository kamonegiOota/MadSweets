/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

namespace basecross {

	/// <summary>
	/// �����鏈�����L�q����Interface
	/// </summary>
	class I_Escape {

	public:
		
		virtual void StartEscape() = 0;
		virtual void SuccessEscape() = 0;  //�����؂萬��
	};

}

//endbasecross