/*!
@file I_Escape.h
@brief I_Escape
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