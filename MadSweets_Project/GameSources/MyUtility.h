
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

			static std::shared_ptr<Stage> GetStage();

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

			/// <summary>
			/// Ray���΂����Ƃ��A��Q������������true��Ԃ��B
			/// </summary>
			/// <param name="startObj">Ray�̃X�^�[�g�|�W�V����</param>
			/// <param name="endObj">Ray�̃G���h�|�W�V����</param>
			/// <returns>��Q������������true</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj);
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos);

			/// <summary>
			/// �Ώۂ̃I�u�W�F�N�g�܂łɏ�Q�������邩�ǂ���
			/// </summary>
			/// <param name="startObj">Ray�̃X�^�[�g</param>
			/// <param name="endObj">Ray���΂��Ώ�</param>
			/// <param name="excluteObj">��Q���Ƃ��ďȂ��Ώ�</param>
			/// <returns>��Q������������true</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj,
				const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// �Ώۂ̃I�u�W�F�N�g�܂łɏ�Q�������邩�ǂ���
			/// </summary>
			/// <param name="startPos">Ray�̃X�^�[�g</param>
			/// <param name="endPos">Ray���΂��Ώ�</param>
			/// <param name="excluteObjs">��Q���Ƃ��ďȂ��Ώ�</param>
			/// <returns>��Q������������true</returns>
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos,
				const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// �ΏۃI�u�W�F�N�g�܂łɏ�Q�������邩�ǂ���
			/// </summary>
			/// <param name="startObj">Ray�̃X�^�[�g</param>
			/// <param name="endObj">�ΏۃI�u�W�F�N�g</param>
			/// <param name="obstacleObjs">��Q���̑ΏۂɂȂ�I�u�W�F�N�g</param>
			/// <param name="excluteObjs">��Q���̑ΏۂɂȂ�I�u�W�F�N�g�̒��ł�����̃I�u�W�F�N�g��ΏۊO�ɂ������ꍇ�ɋL�q</param>
			/// <returns>��Q������������true</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj,
				const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// �ΏۃI�u�W�F�N�g�܂łɏ�Q�������邩�ǂ���
			/// </summary>
			/// <param name="startPos">Ray�̃X�^�[�g</param>
			/// <param name="endPos">�ΏۃI�u�W�F�N�g</param>
			/// <param name="obstacleObjs">��Q���̑ΏۂɂȂ�I�u�W�F�N�g</param>
			/// <param name="excluteObjs">��Q���̑ΏۂɂȂ�I�u�W�F�N�g�̒��ł�����̃I�u�W�F�N�g��ΏۊO�ɂ������ꍇ�ɋL�q</param>
			/// <returns>��Q������������true</returns>
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos,
				const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// template�Ŏw�肳�ꂽ�N���X��`���āA��Q����������֐��B
			/// </summary>
			template<class ExcluteClass>
			static bool IsRayObstacleExclute(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj)
			{
				auto exclutes = maru::MyUtility::GetComponents<ExcluteClass>();
				return IsRayObstacle(startObj, endObj, exclutes);
			}

			/// <summary>
			/// Template�Ŏw�肵���R���|�[�l���g�̂��Ă���I�u�W�F�N�g���w���Q�����肵�ĒT���B
			/// </summary>
			template<class ObstacleClass>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj)
			{
				auto obstacleObjs = maru::MyUtility::GetComponents<ObstacleClass>();

				return IsRayObstacle(startObj, endObjs, obstacleObjs, vector<shared_ptr<GameObject>>());
			}

			/// <summary>
			/// ����̃I�u�W�F�N�g��Ray��ɍ�������true��Ԃ��B
			/// </summary>
			/// <param name="startObj">Ray�̊J�n</param>
			/// <param name="endObj">Ray�̏I���</param>
			/// <param name="obstacleObj">�Ԃɂ��邩�ǂ������f�������I�u�W�F�N�g</param>
			/// <returns>Ray��ɍ�������true</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj,
				const std::shared_ptr<GameObject>& obstacleObj);
			
			//�Ώۂ̏�Q�������Ray�̊Ԃɍ�������true
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos,
				const std::shared_ptr<GameObject>& obstacleObj);

			/// <summary>
			/// �Ώۂ̃I�u�W�F�N�g���ΏۊO���ǂ������f����
			/// </summary>
			/// <param name="targetObj">�Ώۂ̃I�u�W�F�N�g</param>
			/// <param name="excluteObjs">�ΏۊO�ƂȂ�z��I�u�W�F�N�g</param>
			/// <returns>�ΏۊO�Ȃ�true</returns>
			static bool IsExclute(const shared_ptr<GameObject>& targetObj ,const vector<shared_ptr<GameObject>>& excluteObjs);


			//�Q�[���I�u�W�F�N�gVec����w��̃I�u�W�F�N�g�̂ݎ擾
			//�ŏ��Ɏ擾�ł������̂����Ԃ��B
			template<class T,
				enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
			static shared_ptr<T> GetGameObject() {
				auto stage = GetStage();

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
			template<class T,
				enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
			static vector<shared_ptr<T>> GetGameObjects() {
				auto stage = GetStage();

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

			template<class T,
				enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr >
			static shared_ptr<T> GetComponent() {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = obj->GetComponent<T>(false);
					if (t) {
						return t;
					}
				}

				return nullptr;
			}

			template<class T,
				enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr >
			static vector<shared_ptr<T>> GetComponents() {
				auto stage = GetStage();

				vector<shared_ptr<T>> returnObjs;

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = obj->GetComponent<T>(false);
					if (t) {
						returnObjs.push_back(t);
					}
				}

				return returnObjs;
			}

			/// <summary>
			/// �n���ꂽ�z���template�Ŏw�肵���I�u�W�F�N�g�^�̃I�u�W�F�N�g��ǉ�����B
			/// </summary>
			template<class T,
				enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
			static void AddObjects(vector<shared_ptr<GameObject>>& addVec) {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = dynamic_pointer_cast<T>(obj);
					if (t) {
						addVec.push_back(t);  //�I�u�W�F�N�g�̒ǉ�
					}
				}
			}

			/// <summary>
			/// �n���ꂽ�z���template�Ŏw�肵���R���|�[�l���g�����I�u�W�F�N�g��ǉ�����B
			/// </summary>
			template<class T ,
				enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr >
			static void AddComponents(vector<shared_ptr<GameObject>>& addVec) {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = obj->GetComponent<T>(false);
					if (t) {
						addVec.push_back(obj);  //�I�u�W�F�N�g�̒ǉ�
					}
				}
			}

			//�x�N�^�[�z�񂩂����̃I�u�W�F�N�g���폜����֐��B
			template<class T>
			//static void RemoveVec(vector<shared_ptr<T>>& vec, const shared_ptr<T>& removePtr) {
			static bool RemoveVec(vector<T>& vec, const T& removePtr) {
				auto iter = vec.begin();
				while (iter != vec.end()) {
					if (*iter == removePtr) {
						iter = vec.erase(iter);
						return true;
						//break;
					}
					iter++;
				}

				return false;
			}

		};
	}

	

}

//endbasecross