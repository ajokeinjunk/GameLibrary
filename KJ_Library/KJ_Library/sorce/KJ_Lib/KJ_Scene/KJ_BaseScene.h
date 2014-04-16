#ifndef H_KLIB_BASE_SCENE_H
#define H_KLIB_BASE_SCENE_H

#include <memory>

namespace Klibrary{

	class BaseScene{
	private:
	protected:
		bool m_IsInitialized;

	public:
		BaseScene():m_IsInitialized(false){}
		virtual ~BaseScene(){};

		virtual bool Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual void Release() = 0;

		inline bool GetIsInitialized(){return m_IsInitialized;}
	};

	typedef std::shared_ptr<BaseScene> SceneSharedPtr;
	typedef std::weak_ptr<BaseScene> SceneWeakPtr;

}

#endif