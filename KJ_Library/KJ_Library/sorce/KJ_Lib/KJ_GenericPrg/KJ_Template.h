#pragma once 

#include <unordered_map>

namespace Klibrary{
	
	/**
	* @brief �h���𐶐����Ċ��ɃA�b�v�L���X�g���ēn���֐�
	*/
	template<class Base, class Sub>
	Base* CreateGenericObject(){ return new Sub; }

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class GenericObjectFactory
	@brief map�Ɋ�ꂪ���ʂ���I�u�W�F�N�g�����j�[�NID���Q�Ƃ��Đ�������N���X�B\n
	 ���K�ɓo�^�菇�𓥂񂾃I�u�W�F�N�g�����������Ȃ��悤�ɂł���B\n
	 ���g���폜����邱�Ƃ͑z�肳��Ă��Ȃ����A\n
	 �i�[������̂��֐��|�C���^�ł���A����ID��32Byte�̃T�C�Y�Ȃ̂�\n
	 ID���g���؂�O�Ƀ��Z�b�g����邱�Ƃ�O���ɒu�����̂Ƃ���B
	 */
	/*========--------========--------========--------========--------========--------========--------*/
	template <class Base,  class ID>
	class GenericObjectFactory{
	private:
		//�֐��|�C���^
		typedef Base* (*CreateObjectFunction)();
		std::unordered_map<ID, CreateObjectFunction> m_CreateFunctions;

	public:

		template <class Sub>
		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief ID���Q�Ƃ��Đ��������֐��|�C���^��o�^����֐�
		 @param[in] id map�̃L�[�ɂƂȂ�ID
	    @return �V���ɓo�^�����ꍇ��true��Ԃ��B\n
	    ���łɓo�^����Ă����ꍇ��false��Ԃ��I������B
		*/
		/*========--------========--------========--------========--------========--------========--------*/
		bool Register(ID id){
			auto it = m_CreateFunctions.find(id);
			if (it == m_CreateFunctions.end()){
				//�֐��|�C���^���i�[
				m_CreateFunctions[id] = &CreateGenericObject<Base, Sub>;
				return true;
			}

			return false;
		}

		/*========--------========--------========--------========--------========--------========--------*/
		/*! @brief ID���Q�Ƃ��ĐV���Ȕh���I�u�W�F�N�g���֐��|�C
		 @param[in] id map�̃L�[�ɂƂȂ�ID
		 @return �V���ɓo�^�����ꍇ��true��Ԃ��B\n
		 ���łɓo�^����Ă����ꍇ��false��Ԃ��I������B
		*/
		/*========--------========--------========--------========--------========--------========--------*/

		Base* Create(ID id){
			auto it = m_CreateFunctions.find(id);
			if (it != m_CreateFunctions.end()){
				CreateObjectFunction pFunction = it->second;
				return pFunction();
			}
			return nullptr;
		}
	};
}