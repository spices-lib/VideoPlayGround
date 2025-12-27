#include "SlateScope.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>
#include <imgui.cpp>
#include <imgui_internal.h>
#include <imgui_widgets.cpp>

namespace PlayGround::Slate {

	void SlateScope::BeginScope()
	{
		ImGui_ImplVulkan_NewFrame();

		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

        ImGuiID dockspaceID = ImGui::GetID("DockSpace");

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags host_window_flags = 0;
        host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        host_window_flags |= ImGuiWindowFlags_NoMove; //| ImGuiWindowFlags_NoDocking;
        host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        host_window_flags |= ImGuiWindowFlags_NoBackground;

        char label[32];
        ImFormatString(label, IM_ARRAYSIZE(label), "DockSpaceViewport_%08X", viewport->ID);
        ImGui::Begin(label, NULL, host_window_flags);


        ImGuiDockNodeFlags dockspaceFlags =
        ImGuiDockNodeFlags_PassthruCentralNode;
        //ImGuiDockNodeFlags_AutoHideTabBar;
        //ImGuiDockNodeFlags_NoDockingInCentralNode;

        if (!ImGui::DockBuilderGetNode(dockspaceID))
        {
            ImGui::DockBuilderRemoveNode(dockspaceID);
            ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);

            ImGuiID dock_main_id = dockspaceID;

            ImGuiID id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_left", id_left);

            ImGuiID id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_right", id_right);

            ImGuiID id_up = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_up", id_up);

            ImGuiID id_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_down", id_down);

            ImGui::DockBuilderDockWindow("Scene", dock_main_id);

            ImGui::DockBuilderFinish(dock_main_id);
        }

        ImVec4 col = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(col.x, col.y, col.z, 1.0f));

        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
        ImGui::PopStyleColor();
        ImGui::End();
	}

	void SlateScope::EndScope()
	{
		ImGui::Render();
	}
}