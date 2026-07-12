
#include "ImGuiManager.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

#include "Framework/Framework.h"

float f = 0;
int counter = 0;
// 初期化処理
void ImGuiManager::Init()
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

	bool result = ImGui_ImplWin32_Init(
		*pGraphics->GetHWND()
	);

	// ImGuiの初期化設定
	ImGui_ImplDX12_InitInfo initInfo{};
	{
		initInfo.Device = pGraphics->GetDevice();
		initInfo.CommandQueue = pGraphics->GetCommandQueue();
		initInfo.RTVFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		initInfo.DSVFormat = DXGI_FORMAT_UNKNOWN;
		initInfo.NumFramesInFlight = 2;

		// ディスクリプタヒープの設定
		initInfo.SrvDescriptorHeap = m_descriptorHeap.Get();
		initInfo.LegacySingleSrvCpuDescriptor =
			m_descriptorHeap.GetCPUHeapHandle();

		initInfo.LegacySingleSrvGpuDescriptor =
			m_descriptorHeap.GetGPUHeapHandle();
	}

	// ImGUIの初期化
	result = ImGui_ImplDX12_Init(
		&initInfo
	);
}
// フレーム開始時の処理
void ImGuiManager::BeginFrame()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

// 更新処理
void ImGuiManager::Render()
{
	ImGui::ShowDemoWindow();
	
	// UIパネル要素の追加
	ImGui::SetNextWindowSize(ImVec2(400, 800),ImGuiCond_Always);
	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;

	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::End();
}

// フレーム終了時の処理
void ImGuiManager::EndFrame()
{
	auto* pCommandList = Render_I->GetGraphics()->GetCommandList();

	// ディスクリプタヒープの設定
	ID3D12DescriptorHeap* pHeaps[] = { m_descriptorHeap.Get() };
	pCommandList->SetDescriptorHeaps(
		1,
		pHeaps
	);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(
		ImGui::GetDrawData(), 
		pCommandList
	);
}

// 後片付け処理
void ImGuiManager::Term()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}