#ifndef H_KLIB_PROCESS_MANAGER_H
#define H_KLIB_PROCESS_MANAGER_H

#include <list>
#include "Process.h"

namespace Klibrary{

	typedef std::list<ProcessSharedPtr> ProcessList;

	class ProcessManager;
	typedef std::shared_ptr<ProcessManager> ProcessManagerSharedPtr;
	typedef std::weak_ptr<ProcessManager> ProcessManagerWeakPtr;
	

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class ProcessManager
	@brief 個別に処理させたい動作をProcessとして作成し
	それらを統括して管理するクラス
	*/
	/*========--------========--------========--------========--------========--------========--------*/
	class ProcessManager
	{
	private:
		ProcessList m_processList;
		void ClearAllProcesses();

	public:
		ProcessManager(){}
		~ProcessManager(){ ClearAllProcesses(); }

		jUInt32 UpdateProcesses(const jUInt32 deltaMs);
		
		ProcessWeakPtr AttachProcesses(ProcessSharedPtr pProcess);  
		void AbortAllProcesses(bool erase);  //全動作を強制終了。immediateがTrueならProcessリストからも除外される。

		jUInt32 GetProcessNum(void)const{ return m_processList.size(); }

	};

}

#endif