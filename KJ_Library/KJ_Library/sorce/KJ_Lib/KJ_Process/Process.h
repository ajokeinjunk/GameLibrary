#ifndef H_KLIB_PROCESS_H
#define H_KLIB_PROCESS_H

#include "../KJ_Defines/KJ_Defines.h"
#include <cassert>

//lolいらんコメントは消すこと

#include <memory>

using namespace std;

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Processクラス
	//
	//========--------========--------========--------========--------========
	class Process;
	typedef shared_ptr<Process> ProcessSharedPtr;
	typedef weak_ptr<Process> ProcessWeakPtr;
	
	class Process
	{
		friend class ProcessManager;

	public:
	enum ProcessState
	{
		UNINITIALIZED = 0,  //未初期化
		REMOVED,    //リストから取り除かれたが消されてはいない

		RUNNING,  //動作中
		PAUSED,   //一時停止中

		DEAD_SUCCEEDED,  //動作完了
		DEAD_FAILED,     //動作失敗
		DEAD_ABORTED,    //実行しきれず強制終了させられた

	};


	private:
		ProcessState m_state;
		ProcessSharedPtr m_pChild;

	protected:
		virtual void VInitialize(){ m_state = RUNNING; }
		virtual void VUpdate(jUInt32 deltaMs) = 0;
		virtual void VSuccess(){}      //成功した時に呼び出す処理
		virtual void VFail(){}         
		virtual void VAbort(){}

	public:
		Process(){ m_state = UNINITIALIZED; }
		~Process(){ if (m_pChild)m_pChild->VAbort(); } //lol何故アクセスできる？

		//終了時処理
		inline void Succeed();
		inline void Fail();

		//ポーズ処理
		inline void Pause();
		inline void UnPause();
		
		//子関数
		inline void AttchChiled(ProcessSharedPtr pChiled);
		ProcessSharedPtr RemoveChild();  //自分から取り除くだけ。破壊しない。

		//アクセサ
		ProcessSharedPtr GetChild(){ return m_pChild; }
		ProcessState     GetState()const{ return m_state; }
		bool IsAlive()const{ return (m_state == RUNNING || m_state || PAUSED); }
		bool IsDead()const{ return (m_state == DEAD_SUCCEEDED || m_state == DEAD_FAILED || m_state == DEAD_ABORTED); }
		bool IsRemoved()const{ return (m_state == REMOVED); }
		bool IsPaused()const{ return (m_state == PAUSED); }

	private:
		void SetState(ProcessState newState){ m_state = newState; }

	};

	//========--------========--------========--------========--------========
	//			ProcessクラスInline処理
	//========--------========--------========--------========--------========
	//lolアサートは別処理に置き換えること
	
	inline void Process::Succeed(){
		assert(m_state == RUNNING || m_state == PAUSED);
		m_state = DEAD_SUCCEEDED;
	}

	inline void Process::Fail(){
		assert(m_state == RUNNING || m_state == PAUSED);
		m_state = DEAD_FAILED;
	}

	inline void Process::Pause(){
		if (m_state == RUNNING){
			m_state = PAUSED;
		}
		else{
			assert(0);  
		}
	}

	inline void Process::UnPause(){
		if (m_state == PAUSED){
			m_state = RUNNING;
		}
		else{
			assert(0);
		}
	}

	inline void Process::AttchChiled(ProcessSharedPtr pChild){
		if (m_pChild){
			m_pChild->AttchChiled(pChild);
		}
		else{
			m_pChild = pChild;
		}
	}

}

#endif