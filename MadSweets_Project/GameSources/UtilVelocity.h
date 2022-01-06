
/*!
@file UtilVelocity.h
@brief UtilVelocity�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// ���x�v�Z�ɕK�v�ȕ֗��֐��܂Ƃ�
	/// </summary>
	class UtilVelocity 
	{

	public:

		/// <summary>
		/// �ő呬�x����
		/// </summary>
		/// <param name="velocity">�����������x�N�g��</param>
		/// <param name="maxSpeed">�������x</param>
		/// <returns>�������ꂽ�͈͂̃x�N�g����Ԃ��B</returns>
		static Vec3 MaxSpeedVecCheck(const Vec3 velocity ,const float& maxSpeed);

		//�x�N�g���v�Z�p�̊֐��B
		/// <summary>
		/// �����I�ɒǂ������邽�߂̃x�N�g�����v�Z���ĕԂ��֐�
		/// </summary>
		/// <param name="velocity">���݂̑��x</param>
		/// <param name="toVec">�^�[�Q�b�g�����̃x�N�g��</param>
		/// <param name="maxSpeed">�ő呬�x</param>
		/// <returns>�u�^�[�Q�b�g�̕����̃x�N�g���v- �u���݂̑��x�v</returns>
		static Vec3 CalucSeekVec(const Vec3& velocity, const Vec3& toVec,const float& maxSpeed);
		/// <summary>
		/// �����x�N�g����Ԃ�(�߂Â��Ə������Ȃ�x�N�g��)
		/// </summary>
		/// <param name="velocity">���݂̑��x</param>
		/// <param name="toVec">�^�[�Q�b�g�����̃x�N�g��</param>
		/// <param name="maxSpeed">�ő呬�x</param>
		/// <param name="decl"></param>
		/// <returns>�����x�N�g����Ԃ�(�߂Â��Ə������Ȃ�x�N�g��)��Ԃ�</returns>
		static Vec3 CalucArriveVec(const Vec3& velocity, const Vec3& toVec,const float& maxSpeed,const float& decl = 3.0f);

		/// <summary>
		/// �߂��ɂ���Ƃ���Arrive��,�����ɂ���Ƃ���Seek�Œǂ�������֐�
		/// </summary>
		/// <param name="velocity">���݂̑��x</param>
		/// <param name="toVec">�^�[�Q�b�g�����̃x�N�g��</param>
		/// <param name="maxSpeed">�ő呬�x</param>
		/// <param name="nearRange">�v�Z��؂�ւ��鋗��</param>
		/// <param name="decl"></param>
		/// <returns>�v�Z���ꂽForce</returns>
		static Vec3 CalucNearArriveFarSeek(const Vec3& velocity, const Vec3& toVec,
			const float& maxSpeed, const float& nearRange, const float& decl = 3.0f);
	};

}

//endbasecross