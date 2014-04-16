#pragma once

#include "../ActorComponent.h"
#include "../../KJ_Math/KJ_Math.h"

namespace Klibrary{
	class TransformComponent: public ActorComponent {
	private:
		Matrix4 m_Tranfrom;

	public:
		//!< @brief ID代わりになるコンポーネントタイプ\n
		//本来はtypeはstring型、idはそのstringからのhash値を使う。\n
		//この変数がstaticなのは生成されてなくてもこのクラスのタイプを確認するためだ。
		//公開されているのはstaticでは仮想関数が作れないためである。
		static const ActorCompoType g_Type;

		TransformComponent(){ m_Tranfrom.Identify(); }

		bool VInitialize() override;
		bool VInitialize(const Vector3& pos);
		bool VInitialize(const Vector3& pos, const Vector3& scale, const Vector3 rotation);

		//ゲッター
		const Matrix4& GetTransform()const{ return m_Tranfrom; }
		ActorCompoType VGetType()  const override { return g_Type; }

		//セッター
		void SetTransform(const Matrix4& transform){m_Tranfrom = transform;}
	};
}