#pragma once

//Input�N���X

//���J�C�x���g�֐�
// Input_KeyDown�֐� �@�L�[�������ꂽ�C�x���g������������A���̏�Ԃ�ۑ�����֐� 
//�w�肵���L�[��������Ă��邩�A���̏�Ԃ�Ԃ��֐�
//�L�[���b���ꂽ�C�x���g������������A���̏�Ԃ��ق��񂷂�֐�
class Input
{

public:
	static void Input_SetKeyDown(int key);
	static bool Input_GetKeyDownTrigger(int Key); // �������u��
	static bool Input_GetKeyDownPress(int key);   // ������
	static void Input_SetKeyUp(int key);
private:
	//�S�L�[��Ԃ�ۑ�����z��
	static bool gKeyState[256];
	static bool OldKeyState[256];
};


//�v���g�^�C�v�錾
//CInput* GetCInput(); //���̓N���X�����������֐��@extern�����炷���߂�