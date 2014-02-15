#ifndef	_TEXT_LOADER
#define	_TEXT_LOADER

#include <Windows.h>

//*****************************************************************************
//
//		�e�L�X�g�t�@�C������N���X
//
//*****************************************************************************
class	textLoader {
private:
		bool	bInit;

		char	*FileBuf;		//	�t�@�C���o�b�t�@
		DWORD	TextSize;		//	�t�@�C���T�C�Y
		DWORD	ReadIndex;		//	���݈ʒu�|�C���^
		
		DWORD	PushIndex;
		int		SearchTop();	//	���o��

protected:
		bool	Open( LPCSTR filename );

public:
		bool	EndCheck();
		void	LoadString( LPSTR str );	//	������擾
		void	LoadName( LPSTR str );		//	"���O"������擾
		float	LoadFloat();				//	�����_��
		int		LoadInt();					//	����
		DWORD	LoadDWORD();				//	�����Ȃ�����

		void	LoadStringTest( LPSTR str );//	������擾�i�|�C���^�ړ��Ȃ��j

		void	SetIndex( int index );
		void	Skip( void );	//	{}�X�L�b�v
		void	In( void );		//	{�N��
		void	Out( void );	//	}�O��

		void	newLine();		//	���̍s��

		DWORD	GetPointer(){ return ReadIndex; }
		void	SetPointer( DWORD p ){ ReadIndex = p; }

		void	push();		//	���݈ʒu�ۑ�
		void	pop();		//	�ʒu����

		//	����
		bool	Search( LPCSTR str );
		bool	Search2( LPCSTR str );
		bool	SearchIndent( LPCSTR str );
		bool	SearchLine( LPCSTR str );

		//	�������E���
		textLoader( LPCSTR filename );
		textLoader(){}

		~textLoader()
		{
			if( FileBuf ) delete[] FileBuf;		
		}

};

#endif

