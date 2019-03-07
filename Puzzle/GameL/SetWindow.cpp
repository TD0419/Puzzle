#include "SetWindow.h"
using namespace GameL;

//�폜����Ă��Ȃ����������o�͂Ƀ_���v����
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
HWND LSetWindow:: m_hWnd;
int  LSetWindow:: m_width;
int  LSetWindow:: m_height;

//�E�B���h�E�쐬
// ����5 bool : bFullScreen �t���X�N���[���t���O true : �t���X�N���[�� false : �ʏ�E�B���h�E
void LSetWindow::NewWindow(int w,int h,wchar_t* name,HINSTANCE hInstance, bool bFullScreen)
{
	// �t���X�N���[����
	if (bFullScreen == true)
	{
		DEVMODE dmScreenSettings;

		// �f�B�X�v���C�T�C�Y�擾
		m_width = GetSystemMetrics(SM_CXSCREEN);
		m_height = GetSystemMetrics(SM_CYSCREEN);

		// �S��ʂ̏ꍇ�A��ʂ����[�U�[�̃f�X�N�g�b�v��32�r�b�g�̍ő�T�C�Y�ɐݒ�
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_width;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// �\���ݒ���t���X�N���[���ɕύX
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// �t���X�N���[���E�B���h�E�쐬
		if (!(m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, name, name,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			CW_USEDEFAULT, 0, m_width, m_height, 0, 0, hInstance, 0)))
		{
			return;
		}
	}
	// �ʏ�E�B���h�E�T�C�Y
	else
	{
		m_width = w;
		m_height = h;

		int width  = m_width + GetSystemMetrics(SM_CXDLGFRAME) * 2;
		int height = m_height + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

		//�E�B���h�E�쐬
		if( !( m_hWnd = CreateWindow( name, name, 
			WS_OVERLAPPEDWINDOW & ~( WS_MAXIMIZEBOX | WS_SIZEBOX ),
			CW_USEDEFAULT, 0,  width, height, 0, 0, hInstance, 0) ) )
		{
			 return ;
		}
	}

	ShowWindow( m_hWnd, SW_SHOW );

}

//�E�B���h�E�j��
void LSetWindow::DeleteWindow()
{

	DestroyWindow(m_hWnd);	// �E�B���h�E��j�����o�^������
}