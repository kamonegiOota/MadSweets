
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "MyUtility.h"
#include "Mathf.h"


namespace basecross {

	namespace maru {

		//正面にいるかどうか
		bool MyUtility::IsTargetInFront(const std::shared_ptr<GameObject>& target, const std::shared_ptr<GameObject>& self)
		{
			auto targetTrans = target->GetComponent<Transform>();
			auto targetPos = targetTrans->GetPosition();

			auto selfTrans = self->GetComponent<Transform>();
			auto selfPos = selfTrans->GetPosition();
			auto selfForward = selfTrans->GetForword();

			auto toTarget = targetPos - selfPos;
			auto newDot = dot(selfForward, toTarget);  //マイナスなら....プラスなら...

			if (newDot >= 0.0f)  //角度がplusなら
			{
				return true;  //正面いる。
			}
			else
			{
				return false; //バックにいる。
			}
		}

		//一つ目の引数の方向に向く
		void MyUtility::SetLookDirect(const Vec3& direct, const std::shared_ptr<GameObject>& objPtr) {
			auto delta = App::GetApp()->GetElapsedTime();

			auto trans = objPtr->GetComponent<Transform>();
			auto forward = trans->GetForword();
			forward.y = 0.0f;
			forward.normalize();

			auto newDot = dot(forward, direct);   //dotで角度を取得 
			auto rad = acosf(newDot);             //acosfで角度の差異が求められる。
			auto newCross = cross(forward, direct);//角度の差異が-なのか+なのか判断するためにcrossを求める。

			float rotDirect = 1.0f;
			if (newCross.y > 0.0f) {  //クロスのYがマイナスなら
				rotDirect *= -1.0f;  //回転する方向を逆にする。
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