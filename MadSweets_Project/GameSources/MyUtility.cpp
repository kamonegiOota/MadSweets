
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "MyUtility.h"
#include "Mathf.h"

#include "ThrowObject.h"
#include "StageObject.h"

namespace basecross {

	namespace maru {

		//ステージの取得
		std::shared_ptr<Stage> MyUtility::GetStage() {
			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();
			return scene->GetActiveStage();
		}

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

		bool MyUtility::IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj) {
			return IsRayObstacle(startObj, endObj, vector<std::shared_ptr<GameObject>>());


			//auto startPosition = startObj->GetComponent<Transform>()->GetWorldPosition();
			//auto endPosition = endObj->GetComponent<Transform>()->GetWorldPosition();
			//auto direction = endPosition - startPosition;

			//for (const auto& object : startObj->GetStage()->GetGameObjectVec())
			//{
			//	auto collision = object->GetComponent<Collision>(false);
			//	if (!collision) {
			//		continue;
			//	}

			//	if (startObj == object || endObj == object) {  //スタートもしくはエンドオブジェクトなら処理を飛ばす。
			//		continue;
			//	}

			//	//ヒットしたら、障害物があることになる。
			//	RayHitData data;
			//	if (collision->IsRayHit(startPosition, direction, data)) {
			//		auto length = direction.length();
			//		if (direction.length() > data.length) {  //lengthが手前だったら
			//			//object->GetComponent<BcPNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.0f));
			//			return true;
			//		}
			//	}
			//}

			//return false;
		}

		bool MyUtility::IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
			const std::shared_ptr<GameObject>& endObj,
			const vector<shared_ptr<GameObject>>& excluteObjs)
		{
			auto startPosition = startObj->GetComponent<Transform>()->GetWorldPosition();
			auto endPosition = endObj->GetComponent<Transform>()->GetWorldPosition();
			auto direction = endPosition - startPosition;

			for (const auto& object : startObj->GetStage()->GetGameObjectVec())
			{
				auto collision = object->GetComponent<Collision>(false);
				if (!collision) {
					continue;
				}

				if (startObj == object || endObj == object) {  //スタートもしくはエンドオブジェクトなら処理を飛ばす。
					continue;
				}

				//対象外のオブジェクトだったら
				if (IsExclute(object, excluteObjs)) {
					continue;
				}

				//ヒットしたら、障害物があることになる。
				RayHitData data;
				if (collision->IsRayHit(startPosition, direction, data)) {
					auto length = direction.length();
					if (direction.length() > data.length) {  //lengthが手前だったら
						//object->GetComponent<BcPNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.0f));
						return true;
					}
				}
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

				//ヒットしたら、障害物があることになる。
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

			//ヒットしたら、障害物があることになる。
			if (collision->IsRayHit(startPosition, direction)) {
				return true;
			}
			else {
				return false;
			}
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