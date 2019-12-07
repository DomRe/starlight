///
/// Application.hpp
/// galaxy
///
/// Created by reworks on 08/07/2016.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_APPLICATION_HPP_
#define GALAXY_APPLICATION_HPP_

#include <fstream>

#include "galaxy/core/World.hpp"
#include "galaxy/fs/VirtualFS.hpp"
#include "galaxy/fs/ConfigReader.hpp"
#include "galaxy/graphics/Window.hpp"
#include "galaxy/core/StateMachine.hpp"
#include "galaxy/resources/FontBook.hpp"
#include "galaxy/core/DebugInterface.hpp"
#include "galaxy/physics/Box2DHelper.hpp"
#include "galaxy/resources/SoundPlayer.hpp"
#include "galaxy/resources/MusicPlayer.hpp"
#include "galaxy/graphics/TextureAtlas.hpp"
#include "galaxy/physics/Box2DCallbacks.hpp"
#include "galaxy/resources/ShaderLibrary.hpp"
#include "galaxy/libs/entt/signal/dispatcher.hpp"

namespace galaxy
{
	///
	/// Application superclass. Entry point to run application / game.
	///
	class Application
	{
	public:
		///
		/// Cleans up engine related memory usage.
		/// 
		virtual ~Application() noexcept;

		///
		/// Runs the application.
		///
		/// \return Returns true if the program should restart.
		/// 
		virtual bool run() final;

	protected:
		///
		/// \brief Default constructor.
		///
		/// Sets up the engine. You need to inherit this and call it from a subclass.
		/// Also calls std::srand(std::time(nullptr)) for you.
		/// 
		/// \param config Path to the config file.
		/// \param newConfig A function pointer to a function that contains ofstream code to write a default config file.
		///
		Application(const std::string& config, std::function<void(std::ofstream&)> newConfig);

	private:
		///
		/// Default constructor.
		/// Deleted.
		///
		Application() = default;

		///
		/// Copy Constructor.
		/// Deleted.
		///
		Application(const Application&) = delete;

		///
		/// Move Constructor.
		/// Deleted.
		///
		Application(Application&&) = delete;

	protected:
		///
		/// Master Lua state for application.
		///
		std::unique_ptr<sol::state> m_lua;

		///
		/// The world class, which manages entitys, components, tags, systems, and other important data.
		///
		std::unique_ptr<World> m_world;

		///
		/// Manages the window, rendering and input.
		///
		std::unique_ptr<Window> m_window;

		///
		/// Integrates box2d with the rest of the library.
		///
		std::unique_ptr<Box2DHelper> m_box2dHelper;

		///
		/// Instance of a config reader to parse library config.
		///
		std::unique_ptr<ConfigReader> m_configReader;

		///
		/// Process game events.
		/// 
		std::unique_ptr<entt::Dispatcher> m_dispatcher;

		///
		/// Manages font resources.
		///
		std::unique_ptr<FontBook> m_fontBook;

		///
		/// Controls and manages music resources.
		///
		std::unique_ptr<MusicPlayer> m_musicPlayer;
		
		///
		/// Managers shaders and usage of them.
		///
		std::unique_ptr<ShaderLibrary> m_shaderLibrary;

		///
		/// Controls and manages sound resources.
		///
		std::unique_ptr<SoundPlayer> m_soundPlayer;

		///
		/// Controls game states. 
		///
		std::unique_ptr<StateMachine> m_stateMachine;

		///
		/// Stores and manages all the games graphics. Text, textures, etc.
		///
		std::unique_ptr<TextureAtlas> m_textureAtlas;

		///
		/// Manages the virtual filesystem, opens the resource archives, etc.
		///
		std::unique_ptr<VirtualFS> m_virtualFS;
		
		///
		/// Controls the debug UI which allows you to have control over the game from ingame. Console, script editing, etc.
		///
		#ifdef _DEBUG
			std::unique_ptr<DebugInterface> m_debugInterface;
		#endif

		///
		/// Collision callback functions for Box2D.
		///
		CollisionContact m_engineCallbacks;

	private:
		///
		/// This is returned as true if the debug menu tells the game to restart.
		///
		bool m_restart;

		///
		/// Allegro event queue. Where allegro stores its events.
		///
		ALLEGRO_EVENT_QUEUE* m_queue;
	};
}

#endif