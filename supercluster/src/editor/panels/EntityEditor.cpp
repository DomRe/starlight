///
/// EntityEditor.cpp
/// supercluster
///
/// Refer to LICENSE.txt for more details.
///

#include <galaxy/core/ServiceLocator.hpp>
#include <galaxy/fs/FileSystem.hpp>

#include <galaxy/components/Animated.hpp>
#include <galaxy/components/BatchedSprite.hpp>
#include <galaxy/components/Circle.hpp>
#include <galaxy/components/Line.hpp>
#include <galaxy/components/OnEvent.hpp>
#include <galaxy/components/Physics.hpp>
#include <galaxy/components/Point.hpp>
#include <galaxy/components/Renderable.hpp>
#include <galaxy/components/ShaderID.hpp>
#include <galaxy/components/Tag.hpp>
#include <galaxy/components/Text.hpp>
#include <galaxy/components/Transform.hpp>

#include <imgui/imgui_stdlib.h>
#include <magic_enum.hpp>

#include "EntityEditor.hpp"

using namespace galaxy;

namespace sc
{
	namespace panel
	{
		EntityEditor::EntityEditor()
		{
		}

		EntityEditor::~EntityEditor()
		{
			m_cur_scene = nullptr;
			m_selected  = std::nullopt;
		}

		void EntityEditor::pre_render()
		{
		}

		void EntityEditor::render()
		{
			if (ImGui::Begin("Entity Manager", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize))
			{
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::MenuItem("Create"))
					{
						m_cur_scene->world().create();
					}

					if (ImGui::MenuItem("Create from JSON"))
					{
						const auto file = SL_HANDLE.vfs()->show_open_dialog("*.json");
						m_cur_scene->world().create_from_json(file);
					}

					ImGui::EndMenuBar();
				}

				static std::string s_entity_label;
				auto& world = m_cur_scene->world();
				world.each([&](const ecs::Entity entity) {
					auto* tag = world.get<components::Tag>(entity);
					if (tag)
					{
						s_entity_label = tag->m_tag;
					}
					else
					{
						s_entity_label = "Unknown";
					}

					ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
					if (m_selected != std::nullopt)
					{
						if (m_selected.value() == entity)
						{
							flags |= ImGuiTreeNodeFlags_Selected;
						}
					}

					const bool is_open = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), flags, s_entity_label.c_str());
					if (ImGui::IsItemClicked())
					{
						m_selected = std::make_optional(entity);
					}

					if (is_open)
					{
						ImGui::Text(fmt::format("Numeric ID: {0}.", entity).c_str());

						bool enabled = world.is_enabled(entity);
						if (ImGui::Checkbox("Is Enabled?", &enabled))
						{
							if (enabled)
							{
								world.enable(entity);
							}
							else
							{
								world.disable(entity);
							}
						}

						ImGui::Text("Animated:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##1"))
						{
							world.create_component<components::Animated>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##2"))
						{
							world.remove<components::Animated>(entity);
						}

						ImGui::Text("Batched Sprite:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##3"))
						{
							world.create_component<components::BatchedSprite>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##4"))
						{
							world.remove<components::BatchedSprite>(entity);
						}

						ImGui::Text("Circle:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##5"))
						{
							world.create_component<components::Circle>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##6"))
						{
							world.remove<components::Circle>(entity);
						}

						ImGui::Text("Line:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##7"))
						{
							world.create_component<components::Line>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##8"))
						{
							world.remove<components::Line>(entity);
						}

						ImGui::Text("Point:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##9"))
						{
							world.create_component<components::Point>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##10"))
						{
							world.remove<components::Point>(entity);
						}

						ImGui::Text("Renderable:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##11"))
						{
							world.create_component<components::Renderable>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##12"))
						{
							world.remove<components::Renderable>(entity);
						}

						ImGui::Text("Shader ID:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##13"))
						{
							world.create_component<components::ShaderID>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##14"))
						{
							world.remove<components::ShaderID>(entity);
						}

						ImGui::Text("Sprite:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##15"))
						{
							world.create_component<components::Sprite>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##16"))
						{
							world.remove<components::Sprite>(entity);
						}

						ImGui::Text("Tag:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##17"))
						{
							world.create_component<components::Tag>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##18"))
						{
							world.remove<components::Tag>(entity);
						}

						ImGui::Text("Text:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##19"))
						{
							world.create_component<components::Text>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##20"))
						{
							world.remove<components::Text>(entity);
						}

						ImGui::Text("Transform:");
						ImGui::SameLine();

						if (ImGui::Button(" + ##21"))
						{
							world.create_component<components::Transform>(entity);
						}

						ImGui::SameLine();

						if (ImGui::Button(" - ##22"))
						{
							world.remove<components::Transform>(entity);
						}

						ImGui::TreePop();
					}
				});

				if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				{
					m_selected = std::nullopt;
				}

				if (ImGui::Begin("Component Editor", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (m_selected != std::nullopt)
					{
						const auto entity = m_selected.value();
						render_components(entity);
					}
				}

				ImGui::End();
			}

			ImGui::End();
		}

		void EntityEditor::set_scene(core::Scene* scene)
		{
			m_cur_scene = scene;
		}

		void EntityEditor::render_components(const ecs::Entity entity)
		{
			// clang-format off
			auto [animated, batchedsprite, circle, line, physics, point, renderable, shaderid, sprite, tag, text, transform]
			= m_cur_scene->world().get_multi<components::Animated, components::BatchedSprite, components::Circle, 
			components::Line, components::Physics, components::Point, components::Renderable, components::ShaderID, 
			components::Sprite, components::Tag, components::Text, components::Transform>(entity);
			// clang-format on

			if (ImGui::BeginTabBar("EntityComponentsTabBar", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_Reorderable))
			{
				if (animated)
				{
					if (ImGui::BeginTabItem("Animated"))
					{
						static bool s_add = false;
						if (ImGui::Button("Add"))
						{
							s_add = !s_add;
						}

						if (s_add)
						{
							static std::string s_id                      = "";
							static bool s_loop                           = false;
							static float s_speed                         = 1.0f;
							static std::vector<graphics::Frame> s_frames = {};

							if (ImGui::BeginPopup("Add Animation", ImGuiWindowFlags_AlwaysAutoResize))
							{
								ImGui::InputText("ID", &s_id, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
								ImGui::Checkbox("Is Looping?", &s_loop);
								ImGui::SliderFloat("Speed", &s_speed, 0.1f, 10.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput);

								static bool s_add_frame = false;
								if (ImGui::Button("Add Frame"))
								{
									s_add_frame = !s_add_frame;
								}

								if (s_add_frame)
								{
									if (ImGui::BeginPopup("Add Frame", ImGuiWindowFlags_AlwaysAutoResize))
									{
										static graphics::Frame s_frame;
										static std::string s_tex_id = "";
										static double s_tpf         = 0.1;

										ImGui::InputText("Texture Atlas ID", &s_tex_id, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);

										const static double s_min = 0.1;
										const static double s_max = 10.0;
										ImGui::SliderScalar("Time Per Frame", ImGuiDataType_Double, &s_tpf, &s_min, &s_max, "%.1f");

										if (ImGui::Button("Add##frameaddbutton01"))
										{
											s_frame.set_region(s_tex_id);
											s_frame.m_time_per_frame = s_tpf;
											s_frames.push_back(s_frame);

											s_frame  = {};
											s_tex_id = "";
											s_tpf    = 0.1;

											ImGui::CloseCurrentPopup();
										}

										ImGui::EndPopup();
									}
								}

								if (ImGui::Button("Add"))
								{
									animated->add_animation(s_id, s_id, s_loop, static_cast<double>(s_speed), s_frames);

									s_id    = "";
									s_loop  = false;
									s_speed = 1.0f;
									s_frames.clear();

									ImGui::CloseCurrentPopup();
								}

								ImGui::EndPopup();
							}
						}

						static std::string s_selected = "None";
						if (animated->get_cur_animation())
						{
							s_selected = animated->get_cur_animation()->get_name();
						}

						if (ImGui::BeginCombo("Animation", s_selected.c_str()))
						{
							for (const auto& [name, anim] : animated->get_all())
							{
								const bool selected = (s_selected == name);
								if (ImGui::Selectable(name.c_str(), selected))
								{
									s_selected = name;
									animated->set_animation(s_selected);
								}

								if (selected)
								{
									ImGui::SetItemDefaultFocus();
								}
							}

							ImGui::EndCombo();
						}

						ImGui::LabelText("Current Animation", s_selected.c_str());

						if (ImGui::Button("Play"))
						{
							animated->play();
						}

						if (ImGui::Button("Pause"))
						{
							animated->pause();
						}

						if (ImGui::Button("Stop"))
						{
							animated->stop();
						}

						ImGui::EndTabItem();
					}
				}

				if (batchedsprite)
				{
					if (ImGui::BeginTabItem("Batched Sprite"))
					{
						static float s_cw = 1.0f;
						if (ImGui::InputFloat("Custom Width", &s_cw, 1.0f, 10.0f, "%.1f", ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							batchedsprite->set_custom_width(s_cw);
						}

						static float s_ch = 1.0f;
						if (ImGui::InputFloat("Custom Height", &s_ch, 1.0f, 10.0f, "%.1f", ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							batchedsprite->set_custom_height(s_ch);
						}

						float opacity = batchedsprite->opacity();
						if (ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput))
						{
							batchedsprite->set_opacity(opacity);
						}

						static std::string s_bs_tex = "";
						if (ImGui::InputText("Set Region", &s_bs_tex, ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							if (!s_bs_tex.empty())
							{
								batchedsprite->set_region(s_bs_tex);
								s_bs_tex.clear();
							}
						}

						ImGui::EndTabItem();
					}
				}

				if (circle)
				{
					if (ImGui::BeginTabItem("Circle"))
					{
						/*
						* todo
						*/
						ImGui::EndTabItem();
					}
				}

				if (line)
				{
					if (ImGui::BeginTabItem("Line"))
					{
						/*
						* todo
						*/
						ImGui::EndTabItem();
					}
				}

				if (physics)
				{
					if (ImGui::BeginTabItem("Physics"))
					{
						/*
						if (!physics->m_body->is_rigid())
						{
							ImGui::Text("Body: Kinetic.");

							static float s_hf = 0.0f;
							if (ImGui::InputFloat("Apply Horizontal Force", &s_hf, 0.1, 1, "%.1f", ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
							{
								auto* kin_body = static_cast<physics::KineticBody*>(physics->m_body.get());
								kin_body->apply_horizontal_force(s_hf);
								s_hf = 0.0f;
							}

							ImGui::SameLine();

							static float s_vf = 0.0f;
							if (ImGui::InputFloat("Apply Vertical Force", &s_vf, 0.1, 1, "%.1f", ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
							{
								auto* kin_body = static_cast<physics::KineticBody*>(physics->m_body.get());
								kin_body->apply_vertical_force(s_vf);
								s_vf = 0.0f;
							}
						}
						else
						{
							ImGui::Text("Body: Static.");
						}

						ImGui::Spacing();

						ImGui::SliderFloat("Restitution", &physics->m_body->m_restitution, 0.0f, 10.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);

						ImGui::Spacing();

						ImGui::SliderFloat("Dynamic Friction", &physics->m_body->m_dynamic_friction, 0.0f, 20.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
						ImGui::SameLine();
						ImGui::SliderFloat("Static Friction", &physics->m_body->m_static_friction, 0.0f, 20.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);

						ImGui::Spacing();

						ImGui::Text(fmt::format("X Pos: {0}", physics->m_body->get_pos().x).c_str());
						ImGui::SameLine();
						ImGui::Text(fmt::format("Y Pos: {0}", physics->m_body->get_pos().y).c_str());

						ImGui::Spacing();

						ImGui::Text(fmt::format("X Velocity: {0}", physics->m_body->get_vel().x).c_str());
						ImGui::SameLine();
						ImGui::Text(fmt::format("Y Velocity: {0}", physics->m_body->get_vel().y).c_str());

						ImGui::Spacing();

						ImGui::Text(fmt::format("Body Mass: {0}", physics->m_body->mass()).c_str());
						*/

						ImGui::EndTabItem();
					}
				}

				if (point)
				{
					if (ImGui::BeginTabItem("Point"))
					{
						int size = point->get_size();
						if (ImGui::SliderInt("Size", &size, 0, 100, "%d", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput))
						{
							point->set_size(size);
						}

						float opacity = point->opacity();
						if (ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput))
						{
							point->set_opacity(opacity);
						}

						ImGui::EndTabItem();
					}
				}

				if (renderable)
				{
					if (ImGui::BeginTabItem("Renderable"))
					{
						static const constexpr auto s_types = magic_enum::enum_names<graphics::Renderables>();

						static std::string s_selected = "";
						if (ImGui::BeginCombo("Type", s_selected.c_str()))
						{
							for (const auto& name : s_types)
							{
								const bool selected = (s_selected == name);
								if (ImGui::Selectable(static_cast<std::string>(name).c_str(), selected))
								{
									s_selected         = name;
									renderable->m_type = magic_enum::enum_cast<graphics::Renderables>(s_selected).value();
								}

								if (selected)
								{
									ImGui::SetItemDefaultFocus();
								}
							}

							ImGui::EndCombo();
						}

						ImGui::InputInt("Z Level", &renderable->m_z_level, 1, 2, ImGuiInputTextFlags_CharsNoBlank);

						ImGui::EndTabItem();
					}
				}

				if (shaderid)
				{
					if (ImGui::BeginTabItem("ShaderID"))
					{
						static std::string s_sid_buff = "";
						if (ImGui::InputText("Shader ID", &s_sid_buff, ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							shaderid->m_shader_id = s_sid_buff;
							s_sid_buff            = "";
						}

						ImGui::EndTabItem();
					}
				}

				if (sprite)
				{
					if (ImGui::BeginTabItem("Sprite"))
					{
						/*
						if (ImGui::Button("Load Texture"))
						{
							m_sprites_to_create.emplace(sprite, SL_HANDLE.vfs()->open_with_dialog("*.png"));
						}

						if (ImGui::Button("Clamp to Border"))
						{
							sprite->clamp_to_border();
						}

						if (ImGui::Button("Clamp to Edge"))
						{
							sprite->clamp_to_edge();
						}

						if (ImGui::Button("Set Repeated"))
						{
							sprite->set_repeated();
						}

						if (ImGui::Button("Set Mirrored"))
						{
							sprite->set_mirrored();
						}

						float opacity = sprite->opacity();
						if (ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f))
						{
							sprite->set_opacity(opacity);
						}

						int ansio = sprite->get_aniso_level();
						if (ImGui::SliderInt("Set Ansiotrophy", &ansio, 0, 16))
						{
							sprite->set_anisotropy(ansio);
						}
						*/

						ImGui::EndTabItem();
					}
				}

				if (tag)
				{
					if (ImGui::BeginTabItem("Tag"))
					{
						ImGui::InputText("##TagInput01", &tag->m_tag);
						ImGui::EndTabItem();
					}
				}

				if (text)
				{
					if (ImGui::BeginTabItem("Text"))
					{
						/*
						todo
						*/
						ImGui::EndTabItem();
					}
				}

				if (transform)
				{
					if (ImGui::BeginTabItem("Transform"))
					{
						float pos[2] = {transform->get_pos().x, transform->get_pos().y};
						if (ImGui::InputFloat2("Position", pos, "%.1f", ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							transform->set_pos(pos[0], pos[1]);
						}

						float rotation = transform->get_rotation();
						if (ImGui::SliderAngle("Rotate", &rotation, 0.0f, 360.0f))
						{
							transform->rotate(rotation);
						}

						static float origin[2] = {0.0f, 0.0f};
						if (ImGui::InputFloat2("Rotation Origin", pos, "%.1f", ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							transform->set_rotation_origin(origin[0], origin[1]);
						}

						ImGui::EndTabItem();
					}
				}

				ImGui::EndTabBar();
			}
		}
	} // namespace panel
} // namespace sc