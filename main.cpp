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

        
	/*	ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Settings");
        	

		
		ImGui::End();
		ImGui::Render();*/
        

            dxCommon->Begin();


            dxCommon->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());
            dxCommon->GetCommandList()->SetPipelineState(graphicsPipelineState.Get());
            ID3D12DescriptorHeap* descriptorHeaps[] = { dxCommon->GetSrvDescriptorHeap().Get() };
            dxCommon->GetCommandList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
            // 3D球
            if (showSphere) {
                dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
                dxCommon->GetCommandList()->IASetIndexBuffer(&indexBufferView);
                dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

                materialData->color.x = ballColor.x;
                materialData->color.y = ballColor.y;
                materialData->color.z = ballColor.z;
                materialData->color.w = ballColor.w;
                materialData->enableLighting = enableLighting;
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());

                dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(2, useMonsterBall ? textureSrvHandleGPU2 : textureSrvHandleGPU);
                dxCommon->GetCommandList()->DrawIndexedInstanced(numIndices, 1, 0, 0, 0);
            }

            dxCommon->GetCommandList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
            // 2DSprite
            if (showSprite) {
                dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);
                dxCommon->GetCommandList()->IASetIndexBuffer(&indexBufferViewSprite);
                dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

                materialDataSprite->color.x = spriteColor.x;
                materialDataSprite->color.y = spriteColor.y;
                materialDataSprite->color.z = spriteColor.z;
                materialDataSprite->color.w = spriteColor.w;
                materialDataSprite->enableLighting = enableLightingSprite;
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSprite->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResourceSprite->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU);
                dxCommon->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
            }

            dxCommon->GetCommandList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
            //model
            if (showModel) {
                dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewModel);
                dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

                materialDataModel->color.x = modelColor.x;
                materialDataModel->color.y = modelColor.y;
                materialDataModel->color.z = modelColor.z;
                materialDataModel->color.w = modelColor.w;
                materialDataModel->enableLighting = enableLightingModel;

                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResourceModel->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceModel->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU3);
                dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());
                dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(4, instancingSrvHandleGPU);
                //描画！
                dxCommon->GetCommandList()->DrawInstanced(UINT(modelData.vertices.size()), numInstance, 0, 0);
            }



            // ImGuiの新しいフレームを開始する
            ImGui_ImplDX12_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // ImGuiウィンドウの設定
            ImGui::Begin("Window");

            ImGui::Text("Camera");
            ImGui::DragFloat3("Camera Position", &cameraTransform.translate.x, 0.1f);
            ImGui::DragFloat3("Camera Rotation", &cameraTransform.rotate.x, 0.1f);
            ImGui::DragFloat3("Camera Translate", &cameraTransform.translate.x, 0.1f);
            ImGui::Text("Draw Mode");
            if (ImGui::Button("Sphere")) {
                showSphere = !showSphere;
            }
            if (ImGui::Button("Sprite")) {
                showSprite = !showSprite;
            }
            if (ImGui::Button("Model")) {
                showModel = !showModel;
            }



        dxCommon->RenderImGui();

            ImGui::End();
            // ImGuiの描画データをレンダリングする
            ImGui::Render();
            ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dxCommon->GetCommandList());
            dxCommon->End();
        }
    }

   dxCommon->Finalize();

    delete input;
    winApp->Finalize();
   
    delete winApp;
    delete dxCommon;

	return 0;
}