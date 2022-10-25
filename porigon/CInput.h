#pragma once

//Inputクラス

//公開イベント関数
// Input_KeyDown関数 　キーが押されたイベントが発生したら、その状態を保存する関数 
//指定したキーが押されているか、その状態を返す関数
//キーが話されたイベントが発生したら、その状態をほぞんする関数
class Input
{

public:
	static void Input_SetKeyDown(int key);
	static bool Input_GetKeyDownTrigger(int Key); // 押した瞬間
	static bool Input_GetKeyDownPress(int key);   // 長押し
	static void Input_SetKeyUp(int key);
private:
	//全キー状態を保存する配列
	static bool gKeyState[256];
	static bool OldKeyState[256];
};


//プロトタイプ宣言
//CInput* GetCInput(); //入力クラスををかえす関数　externを減らすために