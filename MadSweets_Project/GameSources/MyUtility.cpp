
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "MyUtility.h"
#include "Mathf.h"

#include "ThrowObject.h"
#include "StageObject.h"

namespace basecross {

	namespace maru {

		//�X�e�[�W�̎擾
		std::shared_ptr<Stage> MyUtility::GetStage() {
			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();
			return scene->GetActiveStage();
		}

		//���ʂɂ��邩�ǂ���
		bool MyUtility::IsTargetInFront(const std::shared_ptr<GameObject>& target, const std::shared_ptr<GameObject>& self)
		{
			auto targetTrans = target->GetComponent<Transform>();
			auto targetPos = targetTrans->GetPosition();

			auto selfTrans = self->GetComponent<Transform>();
			auto selfPos = selfTrans->GetPosition();
			auto selfForward = selfTrans->GetForword();

			auto toTarget = targetPos - selfPos;
			auto newDot = dot(selfForward, toTarget);  //�}�C�i�X�Ȃ�....�v���X�Ȃ�...

			if (newDot >= 0.0f)  //�p�x��plus�Ȃ�
			{
				return true;  //���ʂ���B
			}
			else
			{
				return false; //�o�b�N�ɂ���B
			}
		}

		//��ڂ̈����̕����Ɍ���
		void MyUtility::SetLookDirect(const Vec3& direct, const std::shared_ptr<GameObject>& objPtr) {
			auto delta = App::GetApp()->GetElapsedTime();

			auto trans = objPtr->GetComponent<Transform>();
			auto forward = trans->GetForword();
			forward.y = 0.0f;
			forward.normalize();

			auto newDot = dot(forward, direct);   //dot�Ŋp�x���擾 
			auto rad = acosf(newDot);             //acosf�Ŋp�x�̍��ق����߂���B
			auto newCross = cross(forward, direct);//�p�x�̍��ق�-�Ȃ̂�+�Ȃ̂����f���邽�߂�cross�����߂�B

			float rotDirect = 1.0f;
			if (newCross.y > 0.0f) {  //�N���X��Y���}�C�i�X�Ȃ�
				rotDirect *= -1.0f;  //��]����������t�ɂ���B
			}
			auto mat = trans->GetWorldMatrix();
			mat = Mathf::Mat4RotationAxisY(mat, rad * rotDirect);

			trans->SetQuaternion(mat.quatInMatrix());

			//return cr.y;
		}

		Vec3 MyUtility::CalucToTargetVec(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
			auto selfTrans = self->GetComponent<Transform>();
			auto selfPos = selfTrans->GetPosition();

			auto targetTrans = target->GetComponent<Transform>();
			auto targetPos = targetTrans->GetPosition();

			auto toVec = targetPos - selfPos;

			return toVec;
		}

		bool MyUtility::IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj) {
			return IsRayObstacle(startObj, endObj, vector<std::shared_ptr<GameObject>>());
		}

		bool MyUtility::IsRayObstacle(const Vec3& startPosition, const Vec3& endPosition) {
			return IsRayObstacle(startPosition, endPosition, vector<std::shared_ptr<GameObject>>());
		}

		bool MyUtility::IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
			const std::shared_ptr<GameObject>& endObj,
			const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			return IsRayObstacle(startObj, endObj, GetStage()->GetGameObjectVec(), excluteObjs);
		}

		bool MyUtility::IsRayObstacle(const Vec3& startPosition, const Vec3& endPosition,
			const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			return IsRayObstacle(startPosition, endPosition, GetStage()->GetGameObjectVec(), excluteObjs);
		}

		bool MyUtility::IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto startPosition = startObj->GetComponent<Transform>()->GetWorldPosition();
			auto endPosition = endObj->GetComponent<Transform>()->GetWorldPosition();

			//excluteObjs�ɃX�^�[�g�I�u�W�F�N�g�ƁA�G���h�I�u�W�F�N�g���Ȃ��B
			auto newExcluteObjs = excluteObjs;
			newExcluteObjs.push_back(startObj);
			newExcluteObjs.push_back(endObj);

			return IsRayObstacle(startPosition, endPosition, obstacleObjs,newExcluteObjs);
		}

		bool MyUtility::IsRayObstacle(const Vec3& startPosition, const Vec3& endPosition,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto direction = endPosition - startPosition;

			for (const auto& object : obstacleObjs)
			{
				auto collision = object->GetComponent<Collision>(false);
				if (!collision) {
					continue;
				}

				//�ΏۊO�̃I�u�W�F�N�g��������
				if (IsExclute(object, excluteObjs)) {
					continue;
				}

				//�q�b�g������A��Q�������邱�ƂɂȂ�B
				RayHitData data;
				if (collision->IsRayHit(startPosition, direction, data)) {
					auto length = direction.length();
					if (direction.length() > data.length) {  //length����O��������
						return true;
					}
				}
			}

			return false;
		}


		bool MyUtility::IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
			const std::shared_ptr<GameObject>& endObj,
			const std::shared_ptr<GameObject>& obstacleObj)
		{
			auto startPosition = startObj->GetComponent<Transform>()->GetWorldPosition();
			auto endPosition = endObj->GetComponent<Transform>()->GetPosition();
			//auto direction = endPosition - startPosition;

			return IsRayObstacle(startPosition, endPosition, obstacleObj);
		}

		bool MyUtility::IsRayObstacle(const Vec3& startPosition, const Vec3& endPosition,
			const std::shared_ptr<GameObject>& obstacleObj)
		{
			auto collision = obstacleObj->GetComponent<Collision>();
			auto direction = endPosition - startPosition;

			//�q�b�g������A��Q�������邱�ƂɂȂ�B
			RayHitData data;
			if (collision->IsRayHit(startPosition, direction, data)) {
				if (direction.length() > data.length) {
					return true;
				}
			}

			return false;
		}

		

		bool MyUtility::IsExclute(const shared_ptr<GameObject>& targetObj,const vector<shared_ptr<GameObject>>& excluteObjs) {
			for (auto& exclute : excluteObjs) {
				if (targetObj == exclute) {
					return true;
				}
			}

			return false;
		}
	}
}

//enbbasecross