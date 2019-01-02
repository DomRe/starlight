///
/// GameState.cpp
/// sandbox
///
/// Created by reworks on 20/02/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include <sl/libs/entt/entity/helper.hpp>

#include <sl/core/World.hpp>
#include <sl/graphics/TextureAtlas.hpp>
#include <allegro5/keyboard.h>
#include <sl/tags/CameraTag.hpp>
#include <sl/core/ServiceLocator.hpp>
#include <sl/systems/RenderSystem.hpp>
#include <sl/components/RenderComponent.hpp>
#include <sl/components/EnabledComponent.hpp>
#include <sl/components/TransformComponent.hpp>
#include <sl/components/ScrollingBackgroundComponent.hpp>
#include <sl/ui/widgets/Button.hpp>
#include <sl/libs/entt/signal/dispatcher.hpp>
#include <sl/graphics/Window.hpp>
#include <sl/resources/MusicPlayer.hpp>
#include <sl/ui/widgets/ProgressBar.hpp>
#include <sl/events/MouseMovedEvent.hpp>
#include <sl/events/MousePressedEvent.hpp>
#include <sl/events/MouseReleasedEvent.hpp>
#include <sl/events/Keys.hpp>
#include <sl/events/KeyDownEvent.hpp>
#include <sl/ui/widgets/Textbox.hpp>
#include <sl/ui/widgets/TextInput.hpp>

#include "GameState.hpp"

using namespace sl;

GameState::GameState()
	:serialize("savefiles/"), m_theme("GameOver32", al_map_rgba(0, 255, 0, 255), "ui/master.png")
{
	//map = std::make_unique<sl::TMXMap>("platformer.tmx", 2.5f);
	//m_bounds.m_height = map->m_internalMap->height * map->m_internalMap->tile_height;
	//m_bounds.m_width = map->m_internalMap->width * map->m_internalMap->tile_width;
	m_bounds.m_height = 0;
	m_bounds.m_width = 0;
	m_bounds.m_x = 0;
	m_bounds.m_y = 0;

	//Locator::musicPlayer->get("background").play();

	sl::Keys::UI_CONFIRM = ALLEGRO_KEY_ENTER;

	entt::DefaultRegistry::entity_type scrolledEntity = Locator::world->m_registry.create();
	Locator::world->m_registry.assign<TransformComponent>(scrolledEntity, 1, 0.0f, Rect<float, int>{ 0.0f, 0.0f, 1280, 720 });
	Locator::world->m_registry.assign<ScrollingBackgroundComponent>(scrolledEntity, 1.0f);
	Locator::world->m_registry.assign<RenderComponent>(scrolledEntity, 1.0f, "bg_forest");
	Locator::world->m_registry.assign<EnabledComponent>(scrolledEntity);

	m_theme.defineWidgetTexture("frame", {9, 0, 256, 128});
	m_theme.defineWidgetTexture("arrow", {0, 0, 8, 6});

	m_panel = m_ui.addPanel(sl::Rect<int>{ 0, 0, 360, 720 }, al_map_rgba(169, 169, 169, 255));
	
	std::array<ALLEGRO_COLOR, 3> cols = 
	{
		al_map_rgba(0, 0, 255, 255), al_map_rgba(255, 0, 0, 255), al_map_rgba(0, 255, 0, 255)
	};

	sl::Button* testbtn = m_panel->add<sl::Button>(20, 20, "Click me!", cols, &m_theme);
	testbtn->registerCallback([&]() -> void
	{
		LOG_S(INFO) << "BUTTON CLICKED!";
	});
	testbtn->setTooltip("This is a tooltip.", &m_theme);

	sl::ProgressBar* bar = m_panel->add<sl::ProgressBar>(sl::Rect<int>{20, 80, 100, 20}, al_map_rgba(192, 192, 192, 255), al_map_rgba(255, 0, 0, 255));
	bar->setProgress(0.67f);

	std::ostringstream ss;
	ss << bar->getPercentage();
	std::string s = "Health Bar: " + ss.str() + "%";
	sl::Label* label = m_panel->add<sl::Label>(25, 80, s, &m_theme);

	slider = m_panel->add<sl::Slider>(sl::Rect<int>{5, 120, 200, 25}, 8, 50, al_map_rgba(255, 0, 0, 255), al_map_rgba(0, 0, 255, 255));

	std::ostringstream ss2;
	ss2 << slider->getPercentage();
	sliderLabelStr = "Value: " + ss2.str() + "%";
	m_sliderLabel = m_panel->add<sl::Label>(5, 120, sliderLabelStr, &m_theme);

	sl::Textbox* textbox = m_panel->add<sl::Textbox>(5, 200, "frame", "arrow", std::vector<std::string>{"This is a long message...", "This is an even longer message..."}, 120, 80, &m_theme, "Speaker");

	sl::TextInput* ti = m_panel->add<sl::TextInput>(sl::Rect<int>{5, 500, 200, 64}, al_map_rgba(0, 0, 0, 255), al_map_rgba(255, 255, 255, 255), &m_theme);
}

GameState::~GameState()
{
	Locator::world->m_registry.reset();
}

void GameState::load()
{
	//sl::Locator::world->createEntity("load.lua");
	//Locator::textureAtlas->dumpAtlas("atlas.png");
}

void GameState::unload()
{
}

void GameState::event(ALLEGRO_EVENT* event)
{
	switch (event->type)
	{
	case ALLEGRO_EVENT_MOUSE_AXES:
		Locator::dispatcher->trigger<sl::MouseMovedEvent>(event->mouse.x, event->mouse.y, event->mouse.dx, event->mouse.dy, event->mouse.pressure);
		break;

	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		Locator::dispatcher->trigger<sl::MousePressedEvent>(event->mouse.x, event->mouse.y, event->mouse.button);
		break;

	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		Locator::dispatcher->trigger<sl::MouseReleasedEvent>(event->mouse.x, event->mouse.y, event->mouse.button);
		break;

	case ALLEGRO_EVENT_KEY_CHAR:
		Locator::dispatcher->trigger<sl::KeyCharEvent>(event->keyboard.keycode, event->keyboard.unichar);
		break;

	case ALLEGRO_EVENT_KEY_DOWN:
		Locator::dispatcher->trigger<sl::KeyDownEvent>(event->keyboard.keycode);
		switch (event->keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			Locator::window->close();
			break;

		case ALLEGRO_KEY_V:
			m_panel->setVisibility(true);
			break;

		case ALLEGRO_KEY_H:
			m_panel->setVisibility(false);
			break;

		case ALLEGRO_KEY_S:
			//serialize.createGameSnapshot("test.sav", Locator::world->m_registry);
			break;

		case ALLEGRO_KEY_L:
			//serialize.loadGameSnapshot("test.sav", Locator::world->m_registry);
			break;
		}
		break;
	}
}

void GameState::update(const double dt)
{
	std::ostringstream ss2;
	ss2 << slider->getPercentage();
	sliderLabelStr = "Value: " + ss2.str() + "%";
	m_sliderLabel->setText(sliderLabelStr);

	m_ui.update(dt);
}

void GameState::render()
{
	Locator::world->getSystem<RenderSystem>()->render(Locator::world->m_registry);

	m_ui.render();
}