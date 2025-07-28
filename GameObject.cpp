#ifndef GAME_OBJ_CPP
#define GAME_OBJ_CPP

#include "GameObject.h"
#include "TextureManager.h"
#include "game.h"
#include "LoaderParams.h"

//void GameObject::load(int x, int y, int width, int height, std::string textureID){
//	m_x = x;
//	m_y = y;
//	m_width = width;
//	m_height = height;
//	m_textureID = textureID;
//
//	m_currentRow = 1;
//	m_currentFrame = 1;	//this might actually be zero indexed I need to look at this again
//}
//GameObject::GameObject(const LoaderParams* pParams){
  //  m_x = pParams->getX();
 //   m_y = pParams->getY();
 //   m_width = pParams->getWidth();
 //   m_height = pParams->getWidth();
//    m_textureID = pParams->getTextureID();

  //  m_currentRow = 1;
//    m_currentFrame = 1;
//}
//ill remove this when the refactor is running.


void GameObject::draw(){
	TextureManager::Instance()->drawFrame(m_textureID,m_x,m_y,m_width,m_height,m_currentRow,m_currentFrame,TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);	//added flip for now
}

void GameObject::update(){
	m_x+= 1;		//just for testing obv dont leave this;
}

void GameObject::clean(){
	std::cout << "cleaning?\n";
}



#endif
