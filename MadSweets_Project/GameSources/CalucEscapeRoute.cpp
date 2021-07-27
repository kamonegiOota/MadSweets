/*!
@file CalucEscapeRoute.cpp
@brief CalucEscapeRoute�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "CalucEscapeRoute.h"
#include "UtilityAstar.h"

namespace basecross {

	NavGraphNode CalucEscapeRoute::CalucRoute(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& selfObj,
		const std::shared_ptr<GameObject>& targetObj) 
	{
		auto selfPos = selfObj->GetComponent<Transform>()->GetPosition();
		auto targetPos = targetObj->GetComponent<Transform>()->GetPosition();

		return CalucRoute(astar, selfPos, targetPos);
	}

	NavGraphNode CalucEscapeRoute::CalucRoute(const GraphAstar& astar,
		const Vec3& selfPos, const Vec3& targetPos)
	{
		auto selfNode = UtilityAstar::SearchNearNode(astar,selfPos);
		auto targetNode = UtilityAstar::SearchNearNode(astar,targetPos);

		//���肩���ԋ߂��m�[�h���玩���Ɍ������m�[�h������
		auto escapeNode = UtilityAstar::CalucTargetDirectNode(astar, targetNode, selfPos);  //��ԍŏ��ɓ���������̃m�[�h��ݒ�

		return escapeNode;
	}

	NavGraphNode CalucEscapeRoute::CalucNextRoute(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& selfObj,
		const std::shared_ptr<GameObject>& targetObj)
	{
		auto selfPos = selfObj->GetComponent<Transform>()->GetPosition();
		auto targetPos = selfObj->GetComponent<Transform>()->GetPosition();

		return CalucNextRoute(astar, selfPos,targetPos);
	}

	NavGraphNode CalucEscapeRoute::CalucNextRoute(const GraphAstar& astar,
		const Vec3& selfPos, const Vec3& targetPos)
	{
		auto selfNode = UtilityAstar::SearchNearNode(astar, selfPos);

		//�^�[�Q�b�g�̔��Α��ɏo�郋�[�g
		return UtilityAstar::CalucTargetEscapeDirectNode(astar, selfNode, targetPos);
	}

}

//endbasecross