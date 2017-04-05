#include "mainclass.hpp"

bool gameobject_sort(Gameobject * a, Gameobject * b){
	return a->position().z() < b->position().z();
}


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
			Position refpos = player()->position()-world_position();
			if(refpos.x() > m_screen_width*0.75f){
				m_world_position.add(refpos.x()-m_screen_width*0.75f,0,0);
			}
			if(refpos.x() < m_screen_width*0.25f){
				m_world_position.subtract(-refpos.x()+m_screen_width*0.25f,0,0);
			}
			if(refpos.y() > m_screen_height*0.75f){
				m_world_position.add(0,refpos.y()-m_screen_height*0.75f,0);
			}
			if(refpos.y() < m_screen_height*0.25f){
				m_world_position.subtract(0,-refpos.y()+m_screen_height*0.25f,0);
			}
			
			render();
			m_last_frame = now;
			post_update();
		}

		
	}
	std::cout << "Finished running mainloop." << std::endl;
}

void Mainclass::render(){

	std::sort(m_gameobjects.begin(), m_gameobjects.end(), gameobject_sort);
	SDL_SetRenderDrawColor(m_main_renderer, 0, 0, 0, 1);
	SDL_RenderClear(m_main_renderer);
	for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it)
	{
		if(!m_event_ongoing){
			//std::cout << "Hoi" << std::endl;
			(*it)->update(); //Update gameobjects
		}

		if(debug_show_colliders){
			SDL_SetRenderDrawColor(m_main_renderer, 255, 255, 255, 255);

			if((*it)->collider() != nullptr)(*it)->collider()->render(m_main_renderer, world_position());
			SDL_SetRenderDrawColor(m_main_renderer, 255, 0,0,255);
			if((*it)->interactioncomponent() != nullptr) (*it)->interactioncomponent()->triggercollider()->render(m_main_renderer, world_position());
		}else{
			(*it)->draw();
		}	
	}
	SDL_RenderPresent(m_main_renderer);

}

void Mainclass::post_update(){
	m_keymanager.update();
}


void Mainclass::setup_gameobjects(){
	std::cout << "Setting up gameobjects..." << std::endl;
	std::string filename = "levels/level.txt";
	std::ifstream infile(filename.c_str());
	std::stringstream buffer;
	buffer << infile.rdbuf();
	Gameobject * wip_gameobject = nullptr; 
	std::string line;
	std::string::size_type sz;
	while(std::getline(buffer, line)){
		//std::cout << std::endl << line << std::endl;
		//line = trim(line);
		std::vector<std::string> args = split_by_delimiter(line, ' ');
		if(line[0] == '#'){
			//Do nothing lmao
		}else if(line[0] == '$'){ //New event, save old, make new
			//std::cout << "Saving gameobject" << std::endl;
			m_gameobjects.push_back(wip_gameobject);
		}else if(line == "Staticobject"){
			//std::cout << "Making staticobject" << std::endl;
			wip_gameobject = new StaticObject(this);
		}else if(line == "Player"){
			//std::cout << "Making Player" << std::endl;
			m_player = new Player(this);
			wip_gameobject = m_player;
		}else if(line == "NPC"){
			//std::cout << "Making NPC" << std::endl;
			wip_gameobject = new NPC(this);
		}else if(args[0] == "spritesheet"){
			//std::cout << "Adding spritesheet" << std::endl;
			int sizex = std::stoi(args[2], &sz);
			int sizey = std::stoi(args[3], &sz);
			wip_gameobject->visualcomponent()->load_spritesheet(args[1], sizex, sizey, m_main_renderer);
		}else if(args[0] == "pos"){
			//std::cout << "setting pos" << std::endl;
			int posx = std::stoi(args[1], &sz);
			int posy = std::stoi(args[2], &sz);
			wip_gameobject->move_to(posx, posy);
		}else if(args[0] == "scale"){
			//std::cout << "Scaling" << std::endl;
			int scale = std::stoi(args[1], &sz);
			wip_gameobject->scale(scale);
		}else if(args[0] == "event"){
			wip_gameobject->interactioncomponent()->load_event(args[1]);
		
		}
	}
	/*
	Player * player = new Player(this);
	m_player = player;
	player->visualcomponent()->load_spritesheet("media/player_new.png", 32, 32, m_main_renderer);
	player->visualcomponent()->scale(4);
	player->move(70,70);
	m_gameobjects.push_back(player);

	Gameobject * go = new StaticObject(this);
	go->move_to(200,200);
	go->visualcomponent()->load_spritesheet("media/stat.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(4);
	go->collider()->scale(4);
	m_gameobjects.push_back(go);

	go = new NPC(this);
	go->move_to(300,300);
	go->visualcomponent()->load_spritesheet("media/npc.png", 32, 32, m_main_renderer);
	go->interactioncomponent()->load_event("scripts/script.scr");
	go->visualcomponent()->scale(4);
	m_gameobjects.push_back(go);

	go = new StaticObject(this);
	go->move_to(100,500);
	go->visualcomponent()->load_spritesheet("media/stat.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(2);
	go->collider()->scale(2);
	go->collider()->enable(false);
	go->position().z() = 10;
	m_gameobjects.push_back(go);

	go = new StaticObject(this);
	go->move_to(90,510);
	go->visualcomponent()->load_spritesheet("media/stat.png", 32, 32, m_main_renderer);
	go->visualcomponent()->scale(2);
	go->collider()->scale(2);
	go->collider()->enable(false);
	go->position().z() = -10;
	m_gameobjects.push_back(go);
	*/	
	/*
	*/
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
			case SDL_MOUSEBUTTONDOWN:
				m_keymanager.set_mouse(true);
			break;
			case SDL_MOUSEBUTTONUP:
				m_keymanager.set_mouse(false);
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

std::vector<std::string> Mainclass::split_by_delimiter(const std::string & in, char delimiter){
	std::vector<std::string> out; 
	std::string in_work;

	for(unsigned int i = 0; i < in.size(); ++i){
		if(in[i] != delimiter){
		in_work.push_back(in[i]);
		}else{
			out.push_back(in_work);
			in_work = "";
		}
	}
	out.push_back(in_work);
	return out;
}

std::string Mainclass::trim(const std::string& str,
                 const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
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

const Position & Mainclass::world_position(){
	return m_world_position;
}