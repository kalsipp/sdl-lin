#include "editor.hpp"
bool gameobject_sort(Gameobject * a, Gameobject * b);
Editor::Editor(){
	m_font = TTF_OpenFont("fonts/open-sans/OpenSans-Regular.ttf",28);

	m_mouse_collider = new Collider(&m_mouse_position, 16, 16);
	std::cout << "Editor constructed" << std::endl;
}

Editor::~Editor(){
	std::cout << "Editor deconstructed" << std::endl;
}

void Editor::editor_run(){
	
	Gameobject * go = new StaticObject(this);
	go->visualcomponent()->load_text("Helo", m_font, main_renderer());
	go->move_to(30,30);
	//m_gameobjects.push_back(go);

	m_mouse_object = go;


	while(m_running){
		std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = now-m_last_frame;
		std::chrono::milliseconds diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
		//Player Update
		update_keys();
		if(keymanager().key_down(SDLK_p)){
			debug_show_colliders = !debug_show_colliders;
		}
		int posx;
		int posy;
		SDL_GetMouseState(&posx, &posy);
		m_mouse_position.set(posx, posy, 0);
		std::sort(m_gameobjects.begin(), m_gameobjects.end(), gameobject_sort);

		if(m_mouse_object != nullptr){
			m_mouse_object->position().set(m_mouse_position);
			if(keymanager().mouse_down()){
				m_gameobjects.push_back(m_mouse_object);
				m_mouse_object = nullptr;
			}
		}else{
			if(keymanager().mouse_down()){
				auto it = m_gameobjects.rbegin();
				for (; it != m_gameobjects.rend(); ++it)
				{
					if((*it)->collider()->collision_check(m_mouse_collider)){
						m_mouse_object = *it;
						m_gameobjects.erase(std::next(it).base());
						break;
					}
				}
			}
		}
		

		//Rendering
		if(diff.count() > m_frame_delay){
			SDL_SetRenderDrawColor(main_renderer(), 0, 0, 0, 1);
			SDL_RenderClear(main_renderer());
			for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it)
			{
				//std::cout << "Hoi" << std::endl;
				if(debug_show_colliders){
					SDL_SetRenderDrawColor(main_renderer(), 255, 255, 255, 255);
					if((*it)->collider() != nullptr)(*it)->collider()->render(main_renderer(), world_position());
					
					if(m_mouse_object != nullptr){
						m_mouse_object->collider()->render(main_renderer(), world_position());
						if(m_mouse_object->interactioncomponent() != nullptr)m_mouse_object->interactioncomponent()->triggercollider()->render(main_renderer(), world_position());
					}else{
						m_mouse_collider->render(main_renderer(), world_position());
					}
					SDL_SetRenderDrawColor(main_renderer(), 255, 0,0,255);
					if((*it)->interactioncomponent() != nullptr) (*it)->interactioncomponent()->triggercollider()->render(main_renderer(), world_position());
					
				}else{
					(*it)->draw();
					if(m_mouse_object != nullptr){
						m_mouse_object->draw();
					}
				}	
			}
			
			// Update mousepos
			


			SDL_RenderPresent(main_renderer());
			m_last_frame = now;
			post_update();
		}

		
	}
	
} 