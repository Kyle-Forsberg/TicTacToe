#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "LoaderParams.h"




class GameObject {
	public:
		
		//no load, handled by Loader Params
		virtual void draw();
		virtual void update();
		virtual void clean();
	protected:

	GameObject(const LoaderParams* pParams) {}	//does nothing
	virtual ~GameObject() {}
	
	//these might not belong here too,
	//just trying to fix some errors for now
	int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    std::string m_textureID;
	///////////////////////////////////////
};


#endif
