
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "MyUtility.h"
#include "Mathf.h"


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
	}
}

//enbbasecross