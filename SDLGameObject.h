
#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "LoaderParams.h"
#include <string>
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject {
    
    public:
        SDLGameObject(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();

		Vector2D m_position;	
		//made this public for ease for this as its literally just tic tac toe
    protected:
	
        //int m_x;
        //int m_y;
	//replace with vector
	//Vector2D m_position;
	Vector2D m_velocity;
        Vector2D m_accel;
	
	
	int m_width;
        int m_height;
	
        int m_currentRow;
        int m_currentFrame;

        std::string m_textureID;
};


#endif
