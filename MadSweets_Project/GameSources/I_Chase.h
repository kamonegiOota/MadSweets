/*!
@file I_Chase.h
@brief I_Chase
�S���ҁF�ێR �T��
*/

#pragma once

namespace basecross {

	class I_Chase
	{
	public:
		virtual void StartChase() = 0;  //�ǂ������鏈���ɕύX���鎞
		virtual void EndChase() = 0;  //�^�[�Q�b�g�����������Ƃ��̏���
	};
}

//endbasecross