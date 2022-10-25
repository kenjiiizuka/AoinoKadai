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

#pragma comment (lib,"winmm.lib") //timeGetTime関数のため

//マクロ定義
#define CLASS_NAME "DX21Smpl" //ウィンドウクラスの名前
#define WINDOW_NAME "スケルトンプログラム" //ウィンドウの名前
#define BUFFREE 256
#define SCREEN_WIDTH (840)    //ウインドウの幅
#define SCREEN_HEIGHT (680)   //ウィンドウの高さ

//---------------------------------------------------------------------------------------
//関数プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//デルタタイム用の変数
DWORD gDeltaTime;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPravlnstance, LPSTR lpComdLine, int nCmdShow)
{
	//構造体宣言
	WNDCLASSEX wc; 
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_HELP); //カーソルの形
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//ウィンドウの背景の設定
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);//Windowsにウィンドウ情報を登録する

	HWND hWnd;

	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	//Direct3Dの初期化関数を呼び出す
	Direct3D_Init(hWnd);

	HRESULT hr;
	DIRECT3D *d3d = Direct3D_Get();
	MSG msg;
		
	FrameRateCalculator* cFrame = new FrameRateCalculator(); // FPS計算用オブジェクト

	// フレーム処理用変数
	char gBuf[BUFFREE] = { 0 };
	int PrevFrame = 0;
	int FrameLate = 60;
	int PrevSecond = 0;
	long long end = GetNowMicro();                    // 現在時刻を取得（1秒 = 1000000）
	long long next = end + (1000 * 1000 / FrameLate); // 次の更新時間を計算(1秒/フレームレート)

	// 乱数ジェネレータの初期化
	srand((unsigned)time(nullptr));
	
	//メインループ
	while (true)	{
		//前回のループからユーザー操作があったか調べる
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist)	{
			//間接的にウインドウプロシージャ関数を呼び出す
			DispatchMessage(&msg);
			
			if (msg.message == WM_QUIT) {
				break;
			}
		}
	
		else	{
			//デルタタイムの計測
			static DWORD lastTime = timeGetTime(); //前回経過時の時間
			timeBeginPeriod(1); //精度を1ミリ秒に上げる
			DWORD nowTime = timeGetTime(); //現在の時間
			timeEndPeriod(1); //精度をもとに戻す
			gDeltaTime = nowTime - lastTime; //差分がデルタタイム
			lastTime = nowTime; //前回計測時間として保存
		
			// 画面の塗りつぶし
			float color[4] = { 0.7f,0.7f,0.7f,1.0f };
			d3d->context->ClearRenderTargetView(d3d->renderTarget, color);


			// ここにゲームの処理を書いてください
			/* ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ */




			/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */
			// フレームを数える
			PrevFrame += 1;
			if (PrevFrame >= FrameLate) {
				PrevFrame = 0;
				PrevSecond += 1;
			}
			// fps描画
			float fps = cFrame->Update(); // fpsの計算
			sprintf_s(gBuf, BUFFREE, "fps %f 経過fps %d %d秒経過", fps, PrevFrame, PrevSecond);
			SetWindowText(hWnd, gBuf);

			end = GetNowMicro();        // できるだけ60fpsになるようにスレッド待機
			if (end < next) {           // 更新時間まで待機
				std::this_thread::sleep_for(std::chrono::microseconds(next - end));
			}
			// 次の更新時間を計算(1秒/フレームレート加算)
			next += (1000 * 1000 / FrameLate);

			//ダブルバッファの切り替え
			d3d->swapChain->Present(0, 0);
			
		}
	}
	
	delete cFrame;
		
	//Direct3Dの解放関数を呼び出す
	Direct3D_Release();
	UnregisterClass(CLASS_NAME, hInstance);
	return (int)msg.wParam;
}

//ウィンドウプロシージャ関数を作る
//※関数を作れるのはグローバル領域だけ！
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg/*イベントの内容が格納されている*/, WPARAM wParam, LPARAM lParam)
{
	//uMsg　ユーザー操作のID情報
	switch (uMsg)
	{
	case WM_KEYDOWN: //キー入力があった時
		Input::Input_SetKeyDown(LOWORD(wParam));
		break;

	case WM_KEYUP: //キーが話されたとき
		Input::Input_SetKeyUp(LOWORD(wParam));	
		break;

	case WM_DESTROY: //ウィンドウ破棄のメッセージ
		PostQuitMessage(0); //"WM_QUIT"メッセージを送る
		break;

	case WM_CLOSE: //×ボタン押したとき
		DestroyWindow(hWnd); //"WM_DESTROY"メッセージを送る
		break;

	default:
		//上のケース以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}
