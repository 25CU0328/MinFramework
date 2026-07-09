
#include "FrameworkImGui.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

#include "Framework/Framework.h"

// 初期化処理
void FrameworkImGui::Init()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends

	Render::Graphics* const pGraphics = Render_I->GetGraphics();
	m_descriptorHeap.Init(
		pGraphics->GetDevice(),
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		1
	);

	ImGui_ImplWin32_Init(
		pGraphics->GetHWND()
	);

	// ImGUIの初期化
	ImGui_ImplDX12_Init(
		pGraphics->GetDevice(),
		2,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		m_descriptorHeap.Get(),
		m_descriptorHeap.GetCPUHeapHandle(),
		m_descriptorHeap.GetGPUHeapHandle()
	);
}

// 更新処理
void FrameworkImGui::CreateUIs()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// UIパネル要素の追加
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::End();
	}
}

// 描画処理
void FrameworkImGui::Render()
{
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(
		ImGui::GetDrawData(), 
		Render_I->GetGraphics()->GetCommandList()
	);
}

void FrameworkImGui::Term()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}