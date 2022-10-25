#undef UNICODE 

#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "Texture.h"
#include "direct3d.h"
#include "CInput.h"
#include <stdio.h>
#include <thread>
#include "FrameRateCalculator.h"
#include "Time.h"

#pragma comment (lib,"winmm.lib") //timeGetTime�֐��̂���

//�}�N����`
#define CLASS_NAME "DX21Smpl" //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "�X�P���g���v���O����" //�E�B���h�E�̖��O
#define BUFFREE 256
#define SCREEN_WIDTH (840)    //�E�C���h�E�̕�
#define SCREEN_HEIGHT (680)   //�E�B���h�E�̍���

//---------------------------------------------------------------------------------------
//�֐��v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//�f���^�^�C���p�̕ϐ�
DWORD gDeltaTime;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPravlnstance, LPSTR lpComdLine, int nCmdShow)
{
	//�\���̐錾
	WNDCLASSEX wc; 
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_HELP); //�J�[�\���̌`
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�E�B���h�E�̔w�i�̐ݒ�
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);//Windows�ɃE�B���h�E����o�^����

	HWND hWnd;

	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	//Direct3D�̏������֐����Ăяo��
	Direct3D_Init(hWnd);

	HRESULT hr;
	DIRECT3D *d3d = Direct3D_Get();
	MSG msg;
		
	FrameRateCalculator* cFrame = new FrameRateCalculator(); // FPS�v�Z�p�I�u�W�F�N�g

	// �t���[�������p�ϐ�
	char gBuf[BUFFREE] = { 0 };
	int PrevFrame = 0;
	int FrameLate = 60;
	int PrevSecond = 0;
	long long end = GetNowMicro();                    // ���ݎ������擾�i1�b = 1000000�j
	long long next = end + (1000 * 1000 / FrameLate); // ���̍X�V���Ԃ��v�Z(1�b/�t���[�����[�g)

	// �����W�F�l���[�^�̏�����
	srand((unsigned)time(nullptr));
	
	//���C�����[�v
	while (true)	{
		//�O��̃��[�v���烆�[�U�[���삪�����������ׂ�
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist)	{
			//�ԐړI�ɃE�C���h�E�v���V�[�W���֐����Ăяo��
			DispatchMessage(&msg);
			
			if (msg.message == WM_QUIT) {
				break;
			}
		}
	
		else	{
			//�f���^�^�C���̌v��
			static DWORD lastTime = timeGetTime(); //�O��o�ߎ��̎���
			timeBeginPeriod(1); //���x��1�~���b�ɏグ��
			DWORD nowTime = timeGetTime(); //���݂̎���
			timeEndPeriod(1); //���x�����Ƃɖ߂�
			gDeltaTime = nowTime - lastTime; //�������f���^�^�C��
			lastTime = nowTime; //�O��v�����ԂƂ��ĕۑ�
		
			// ��ʂ̓h��Ԃ�
			float color[4] = { 0.7f,0.7f,0.7f,1.0f };
			d3d->context->ClearRenderTargetView(d3d->renderTarget, color);


			// �����ɃQ�[���̏����������Ă�������
			/* ������������������������������������������������������ */




			/* ���������������������������������������������������� */
			// �t���[���𐔂���
			PrevFrame += 1;
			if (PrevFrame >= FrameLate) {
				PrevFrame = 0;
				PrevSecond += 1;
			}
			// fps�`��
			float fps = cFrame->Update(); // fps�̌v�Z
			sprintf_s(gBuf, BUFFREE, "fps %f �o��fps %d %d�b�o��", fps, PrevFrame, PrevSecond);
			SetWindowText(hWnd, gBuf);

			end = GetNowMicro();        // �ł��邾��60fps�ɂȂ�悤�ɃX���b�h�ҋ@
			if (end < next) {           // �X�V���Ԃ܂őҋ@
				std::this_thread::sleep_for(std::chrono::microseconds(next - end));
			}
			// ���̍X�V���Ԃ��v�Z(1�b/�t���[�����[�g���Z)
			next += (1000 * 1000 / FrameLate);

			//�_�u���o�b�t�@�̐؂�ւ�
			d3d->swapChain->Present(0, 0);
			
		}
	}
	
	delete cFrame;
		
	//Direct3D�̉���֐����Ăяo��
	Direct3D_Release();
	UnregisterClass(CLASS_NAME, hInstance);
	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W���֐������
//���֐�������̂̓O���[�o���̈悾���I
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg/*�C�x���g�̓��e���i�[����Ă���*/, WPARAM wParam, LPARAM lParam)
{
	//uMsg�@���[�U�[�����ID���
	switch (uMsg)
	{
	case WM_KEYDOWN: //�L�[���͂���������
		Input::Input_SetKeyDown(LOWORD(wParam));
		break;

	case WM_KEYUP: //�L�[���b���ꂽ�Ƃ�
		Input::Input_SetKeyUp(LOWORD(wParam));	
		break;

	case WM_DESTROY: //�E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0); //"WM_QUIT"���b�Z�[�W�𑗂�
		break;

	case WM_CLOSE: //�~�{�^���������Ƃ�
		DestroyWindow(hWnd); //"WM_DESTROY"���b�Z�[�W�𑗂�
		break;

	default:
		//��̃P�[�X�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}
