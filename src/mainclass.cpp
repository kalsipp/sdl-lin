#include "mainclass.hpp"
/*
#include "gameobject.hpp"
#include "npc.hpp"
#include "player.hpp"
#include "actor.hpp"
*/
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
			if(m_main_renderer == NULL){
				std::cout << "Renderer could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
				m_init_ok = false;
			}else
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
	setup_keys();
	setup_gameobjects();
	m_last_frame = std::chrono::high_resolution_clock::now();
	std::cout << "Finished initializing mainclass." << std::endl;
	//int *load_spritesheet x = new int(10);
	//Destroy window


}
Mainclass::~Mainclass(){ 
	std::cout << "Destroying mainclass..." << std::endl;

	//Remove all gameobjects
	
	for(auto i = m_gameobjects.begin(); i != m_gameobjects.end(); ++i){
		delete *i;
	}
	
	m_gameobjects.clear();

	//Close down SDL
	SDL_DestroyRenderer(m_main_renderer);
	SDL_FreeSurface(m_main_surface);
	SDL_DestroyWindow( m_main_window );
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
		if(keymanager.key(SDLK_p)){
			debug_show_colliders = !debug_show_colliders;
			keymanager.set(SDLK_p, false);
		}

		std::sort(m_gameobjects.begin(), m_gameobjects.end());

		//Rendering
		if(diff.count() > m_frame_delay){
			SDL_SetRenderDrawColor(m_main_renderer, 0, 0, 0, 1);
			SDL_RenderClear(m_main_renderer);
			for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it)
			{
				(*it)->update(keymanager, m_gameobjects); //Update gameobjects


				if(debug_show_colliders){
					SDL_SetRenderDrawColor(m_main_renderer, 255, 255, 255, 255);
					if((*it)->collider() != nullptr)(*it)->collider()->render(m_main_renderer);
					SDL_SetRenderDrawColor(m_main_renderer, 255, 0,0,255);
					if((*it)->interactioncomponent() != nullptr) (*it)->interactioncomponent()->triggercollider()->render(m_main_renderer);
					//if((*it)->trigger_collider() != NULL)(*it)->trigger_collider()->render(m_main_renderer);
				}else{
					//std::cout << "render" << std::endl;
					(*it)->draw(m_main_renderer);
				}	
			}
			SDL_RenderPresent(m_main_renderer);
			m_last_frame = now;
		}
	}
	std::cout << "Finished running mainloop." << std::endl;
}





void Mainclass::setup_gameobjects(){
	
	
	std::cout << "Setting up gameobjects..." << std::endl;
	Gameobject * go = new Player();
	go->visualcomponent()->load_spritesheet("media/player_new.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(4);
	go->move(100,100);
	m_gameobjects.push_back(go);
	/*
	for (int i = 0; i < 1000; ++i){
		go = new StaticObject();
		m_gameobjects.push_back(go);
	}
	*/
	go = new StaticObject();
	go->move_to(200,200);
	go->visualcomponent()->load_spritesheet("media/stat.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(4);
	m_gameobjects.push_back(go);
	/*
	*/
	/*
	go = new NPC();
	go->visualcomponent()->load_spritesheet("media/npc.png", 32, 32, m_main_renderer);
	go->setup_animations();
	go->visualcomponent()->scale(4);
	m_gameobjects.push_back(go);
	*/
	//m_gameobjects.push_back(std::unique_ptr<Gameobject> (new Player()));
	//m_gameobjects[0]->visualcomponent()->
	//m_gameobjects[0]->visualcomponent()->scale(5);
	/*
	Gameobject * g = new Player(this);
	g->load_spritesheet("media/player_new.png");
	g->move_to(100, 100);
	g->scale(3.0f);
	g->collider()->set_size(96,96);
	m_gameobjects.push_back(g);
	std::cout << "Player made" << std::endl;
	
	g = new Gameobject(this);
	g->scale(0.5f);
	g->move_to(40,40);
	g->collider()->set_size(32, 32);
	g->load_spritesheet("media/stat.png");
	m_gameobjects.push_back(g);
	std::cout << "Setup gameobjects end" << std::endl;

	
	*/
	std::cout << "Finished setting up gameobjects." << std::endl;
}


void Mainclass::setup_keys(){
/*
	SDL_Scancode k;
	m_keys[SDLK_a] = false;
	m_keys[SDLK_w] = false;
	m_keys[SDLK_s] = false;
	m_keys[SDLK_d] = false;
	m_keys[SDLK_RIGHT] = false;
	m_keys[SDLK_LEFT] = false;
	m_keys[SDLK_UP] = false;
	m_keys[SDLK_DOWN] = false;
	m_keys[SDLK_p] = false;
	m_keys[SDLK_m] = false;
*/
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
			case SDL_KEYUP:
				keymanager.set(m_main_event.key.keysym.sym, false);

			break;
			case SDL_KEYDOWN:
				keymanager.set(m_main_event.key.keysym.sym, true);
			//}
			break;
		}
	}
}

/*

const std::vector<Gameobject> & Mainclass::gameobjects()const{
	return m_gameobjects;
}
bool Mainclass::key(int n){
	if(m_keys.count(n) <= 0) m_keys[n] = false;
	return m_keys.at(n);
}
const SDL_Renderer * Mainclass::main_renderer()const{
	return m_main_renderer;
}
*/