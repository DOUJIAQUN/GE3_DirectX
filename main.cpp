#include<Windows.h>
#include <sstream>
#include<fstream>
#include<string>
#include<format>
#include <wrl.h>
#include<random>
#include <algorithm>

#include"Struct.h"
#include"MyMath.h"
#include"DebugReporter.h"
#include"Input.h"
#include"WinApp.h"
#include <numbers>
#include "Logger.h"
#include "DirectXCommon.h"
#include "D3DResourceLeakChecker.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

    //Windowの生成
    winApp = new WinApp();
    winApp->Initialize();

    // DX初期化
	dxCommon = new DirectXCommon;
	dxCommon->Initialize(winApp);

	// 入力初期化
	input = new Input();
	input->Initialize(winApp);

    
    while (true) {
        if (winApp->ProcessMessage()) {
            //ゲームループを抜ける
            break;
        }
        input->Update();

        
        dxCommon->Begin();
        dxCommon->BeginImGui();

		ImGui::Begin("Settings");
        	

		
		ImGui::End();
		ImGui::Render();

        

       
        dxCommon->RenderImGui();

        dxCommon->End();
    }
    dxCommon->RenderImGui();
    delete input;
    winApp->Finalize();
   
    delete winApp;
    delete dxCommon;

	return 0;
}