#include "mainclass.hpp"

Mainclass::Mainclass(){
	std::cout << "Initalizing mainclass..." << std::endl;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout <<  "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
		m_init_ok = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}
		//Create window
		m_main_window = SDL_CreateWindow( "Let's go bois", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
		if( m_main_window == NULL )
		{
			std::cout <<  "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
			m_init_ok = false;
		}else{
			m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			m_main_surface = SDL_GetWindowSurface( m_main_window );
			if(m_main_surface == NULL){
				std::cout << "Surface could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
				m_init_ok = false;
			}
			if(m_main_renderer == NULL){
				std::cout << "Renderer could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
				m_init_ok = false;
			}else if(m_init_ok)
			{
				SDL_SetRenderDrawColor(m_main_renderer, 0x0, 0x0, 0x0, 0x0);
				int img_flags = IMG_INIT_PNG;
				if(!(IMG_Init(img_flags) & img_flags)){
					std::cout << "SDL_image could not initialize! SDL_image Error: " << std::string(IMG_GetError()) << std::endl;
					m_init_ok = false;
				}
				
				if (TTF_Init() == -1)
				{
					std::cout <<"SDL_ttf could not initialize! SDL_ttf Error: " << std::string(TTF_GetError())<<std::endl;
					m_init_ok = false;
				}
				
			}
		}
	}
	setup_gameobjects();
	m_last_frame = std::chrono::high_resolution_clock::now();
	std::cout << "Finished initializing mainclass." << std::endl;
}
Mainclass::~Mainclass(){ 
	std::cout << "Destroying mainclass..." << std::endl;

	//Remove all gameobjects
	
	for(auto i = m_gameobjects.begin(); i != m_gameobjects.end(); ++i){
		delete *i;
		//*i = nullptr;
	}
	
	m_gameobjects.clear();

	//Close down SDL
	SDL_DestroyRenderer(m_main_renderer);
	SDL_FreeSurface(m_main_surface);
	SDL_DestroyWindow( m_main_window );
	/*
	*/
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "Destruct mainclass finished." << std::endl;
}
void Mainclass::run(){
	std::cout << "Running mainloop.." << std::endl;
	while(m_running){
		std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = now-m_last_frame;
		std::chrono::milliseconds diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

		//Player Update
		update_keys();
		if(m_keymanager.key_down(SDLK_p)){
			debug_show_colliders = !debug_show_colliders;
		}

		if(m_event_ongoing){
			m_event_ongoing = (m_current_event.update(this));
		}


		//Rendering
		if(diff.count() > m_frame_delay){
			std::sort(m_gameobjects.begin(), m_gameobjects.end());
			SDL_SetRenderDrawColor(m_main_renderer, 0, 0, 0, 1);
			SDL_RenderClear(m_main_renderer);
			for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it)
			{
				if(!m_event_ongoing){
					(*it)->update(); //Update gameobjects
				}

				if(debug_show_colliders){
					SDL_SetRenderDrawColor(m_main_renderer, 255, 255, 255, 255);
					if((*it)->collider() != nullptr)(*it)->collider()->render(m_main_renderer);
					SDL_SetRenderDrawColor(m_main_renderer, 255, 0,0,255);
					if((*it)->interactioncomponent() != nullptr) (*it)->interactioncomponent()->triggercollider()->render(m_main_renderer);
				}else{
					(*it)->draw();
				}	
			}
			SDL_RenderPresent(m_main_renderer);
			m_last_frame = now;
			post_update();
		}

		
	}
	std::cout << "Finished running mainloop." << std::endl;
}


void Mainclass::post_update(){
	m_keymanager.update();
}


void Mainclass::setup_gameobjects(){
	
	
	std::cout << "Setting up gameobjects..." << std::endl;
	Player * player = new Player(this);
	m_player = player;
	player->visualcomponent()->load_spritesheet("media/player_new.png", 32, 32, m_main_renderer);
	player->visualcomponent()->scale(4);
	player->move(100,100);
	m_gameobjects.push_back(player);

	Gameobject * go = new StaticObject(this);
	go->move_to(200,200);
	go->visualcomponent()->load_spritesheet("media/stat.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(4);
	m_gameobjects.push_back(go);
	std::cout << "Making npc" << std::endl; 
	go = new NPC(this);
	go->move_to(300,300);
	go->visualcomponent()->load_spritesheet("media/npc.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(4);
	m_gameobjects.push_back(go);


	std::cout << "Finished setting up gameobjects." << std::endl;
}



void Mainclass::update_keys(){
	while(SDL_PollEvent(&m_main_event) != 0){ 
		switch(m_main_event.type){
			case SDL_QUIT:
				m_running = false;
			break; 

			case SDL_TEXTINPUT:
				if(m_main_event.text.text[0] == 'q'){
					m_running = false;
				}
			break;
			case SDL_KEYUP:
				m_keymanager.set(m_main_event.key.keysym.sym, false);

			break;
			case SDL_KEYDOWN:
				m_keymanager.set(m_main_event.key.keysym.sym, true);
			break;
		}
	}
}


bool Mainclass::start_event(const Event & event){
	if(!m_event_ongoing){
		m_current_event = event;
		m_event_ongoing = true;
		return true;
	}else{
		return false;
	}
}



std::vector<Gameobject*> & Mainclass::gameobjects(){
	return m_gameobjects;
}
Keymanager & Mainclass::keymanager(){
	return m_keymanager;
}
SDL_Renderer * Mainclass::main_renderer(){
	return m_main_renderer;
}
Gameobject * Mainclass::player(){
	return m_player;
}
