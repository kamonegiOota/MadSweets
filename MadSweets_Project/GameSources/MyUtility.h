
/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	namespace maru{

		class MyUtility
		{

		public:

			static constexpr float FOWARD_ADJUST = -XM_PIDIV2;

			//�Ώۂ����ʂɂ��邩�ǂ���
			static bool IsTargetInFront(const std::shared_ptr<GameObject>& target, const std::shared_ptr<GameObject>& self);

			//��ڂ̈����̕����Ɍ���
			//��y���ɑΉ����ĂȂ����߁Ay��0�œn���Ă��������B
			//�Ή�����R�����������܂��B
			static void SetLookDirect(const Vec3& direct, const std::shared_ptr<GameObject>& objPtr);

			/// <summary>
			/// �^�[�Q�b�g�Ɍ������x�N�g�����v�Z���Ă����B
			/// </summary>
			/// <param name="self">�������g�̃|�C���^</param>
			/// <param name="target">�^�[�Q�b�g�̃|�C���^</param>
			/// <returns>�^�[�Q�b�g�Ɍ������x�N�g��</returns>
			static Vec3 CalucToTargetVec(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);

			//�Q�[���I�u�W�F�N�gVec����w��̃I�u�W�F�N�g�̂ݎ擾
			//�ŏ��Ɏ擾�ł������̂����Ԃ��B
			template<class T>
			static shared_ptr<T> GetGameObject() {
				auto& app = App::GetApp();
				auto scene = app->GetScene<Scene>();
				auto stage = scene->GetActiveStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = dynamic_pointer_cast<T>(obj);
					if (t) {
						return t;
					}
				}

				return nullptr;
			}

			//�Q�[���I�u�W�F�N�gVec����w��̃I�u�W�F�N�g�̂ݎ擾
			//�x�N�^�[�z��Ƃ��Č��������̑S�ĕԂ��B
			template<class T>
			static vector<shared_ptr<T>> GetGameObjects() {
				auto& app = App::GetApp();
				auto scene = app->GetScene<Scene>();
				auto stage = scene->GetActiveStage();

				vector<shared_ptr<T>> returnObjs;

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = dynamic_pointer_cast<T>(obj);
					if (t) {
						returnObjs.push_back(t);
					}
				}

				return returnObjs;
			}

		};
	}

	

}

//endbasecross