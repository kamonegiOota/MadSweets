
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
			auto startPosition = startObj->GetComponent<Transform>()->GetWorldPosition();
			auto endPosition = endObj->GetComponent<Transform>()->GetWorldPosition();
			auto direction = endPosition - startPosition;

			//return false;
			for (const auto& object : startObj->GetStage()->GetGameObjectVec())
			{
				auto collision = object->GetComponent<Collision>(false);
				if (!collision) {
					continue;
				}

				if (startObj == object || endObj == object) {  //�X�^�[�g�������̓G���h�I�u�W�F�N�g�Ȃ珈�����΂��B
					continue;
				}

				//���ŃX�e�[�W�I�u�W�F�N�g�ɂ����������Ȃ��悤�ɂ���B
				//auto stageObj = dynamic_pointer_cast<StageObject>(object);
				//if (!stageObj) {
				//	continue;
				//}

				//���Ŕ������Ȃ��悤�ɂ���B(�����I�ɂ͉����Ŕ������Ȃ��悤�ɂ���B)
				auto throwObj = dynamic_pointer_cast<ThrowObject>(object);
				if (throwObj) {
					continue;
				}

				//�q�b�g������A��Q�������邱�ƂɂȂ�B
				RayHitData data;
				if (collision->IsRayHit(startPosition, direction, data)) {
					auto length = direction.length();
					if (direction.length() > data.length) {  //length����O��������
						//object->GetComponent<BcPNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.0f));
						return true;
					}
				}

				//����IsRayHit��
				//auto obb = dynamic_pointer_cast<CollisionObb>(collision);
				//if (obb) {
				//	if (HitTest::SEGMENT_OBB(startPosition, endPosition, obb->GetObb())) {
				//		return true;
				//	}
				//}
				
			}

			return false;
		}

		bool MyUtility::IsRayObstacle(const Vec3& startPosition, const Vec3& endPosition) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto direction = endPosition - startPosition;

			for (const auto& object : stage->GetGameObjectVec())
			{
				auto collision = object->GetComponent<Collision>(false);
				if (!collision) {
					continue;
				}

				//�q�b�g������A��Q�������邱�ƂɂȂ�B
				if (collision->IsRayHit(startPosition, direction)) {
					return true;
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
			auto direction = endPosition - startPosition;

			return IsRayObstacle(startPosition, direction, obstacleObj);
		}

		bool MyUtility::IsRayObstacle(const Vec3& startPosition, const Vec3& endPosition,
			const std::shared_ptr<GameObject>& obstacleObj)
		{
			auto collision = obstacleObj->GetComponent<Collision>();
			auto direction = endPosition - startPosition;

			//�q�b�g������A��Q�������邱�ƂɂȂ�B
			if (collision->IsRayHit(startPosition, direction)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

//enbbasecross