#pragma once

#include "../ActorComponent.h"
#include "../../KJ_Math/KJ_Math.h"

namespace Klibrary{
	class TransformComponent: public ActorComponent {
	private:
		Matrix4 m_Tranfrom;

	public:
		//!< @brief ID����ɂȂ�R���|�[�l���g�^�C�v\n
		//�{����type��string�^�Aid�͂���string�����hash�l���g���B\n
		//���̕ϐ���static�Ȃ̂͐�������ĂȂ��Ă����̃N���X�̃^�C�v���m�F���邽�߂��B
		//���J����Ă���̂�static�ł͉��z�֐������Ȃ����߂ł���B
		static const ActorCompoType g_Type;

		TransformComponent(){ m_Tranfrom.Identify(); }

		bool VInitialize() override;
		bool VInitialize(const Vector3& pos);
		bool VInitialize(const Vector3& pos, const Vector3& scale, const Vector3 rotation);

		//�Q�b�^�[
		const Matrix4& GetTransform()const{ return m_Tranfrom; }
		ActorCompoType VGetType()  const override { return g_Type; }

		//�Z�b�^�[
		void SetTransform(const Matrix4& transform){m_Tranfrom = transform;}
	};
}