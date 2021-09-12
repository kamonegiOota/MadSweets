/*!
@file CalucEscapeRoute.h
@brief CalucEscapeRoute
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "GraphAstar.h"

namespace basecross {

	/// <summary>
	/// �����郋�[�g���\�z����Ƃ��̃f�[�^�N���X
	/// </summary>
	class CalucEscapeRoute
	{

	public:

		/// <summary>
		/// ���[�g�̍\�z
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="selfObj">�������g</param>
		/// <param name="targetObj">�^�[�Q�b�g</param>
		/// <returns>����������̃m�[�h</returns>
		static NavGraphNode CalucRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);
		/// <summary>
		/// ���[�g�̍\�z
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="selfPos">�������g�̃|�W�V����</param>
		/// <param name="targetPos">�^�[�Q�b�g�̃|�W�V����</param>
		/// <returns>����������̃m�[�h</returns>
		static NavGraphNode CalucRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);


		/// <summary>
		/// ������Ƃ��̓��ڈȍ~�̃��[�g���z
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="selfObj">�������g</param>
		/// <param name="targetObj">�^�[�Q�b�g</param>
		/// <returns>����������̃m�[�h</returns>
		static NavGraphNode CalucNextRoute(const GraphAstar& astar,
			const std::shared_ptr<GameObject>& selfObj,
			const std::shared_ptr<GameObject>& targetObj);
		/// <summary>
		/// ������Ƃ��̓��ڈȍ~�̃��[�g���z
		/// </summary>
		/// <param name="astar">Astar�̎Q��</param>
		/// <param name="selfPos">�������g�̃|�W�V����</param>
		/// <param name="targetPos">�^�[�Q�b�g�̃|�W�V����</param>
		/// <returns>����������̃m�[�h</returns>
		static NavGraphNode CalucNextRoute(const GraphAstar& astar,
			const Vec3& selfPos, const Vec3& targetPos);
	};

}

//endbasecross