#ifndef TEXTURE_MANAGER_CPP
#define TEXTURE_MANAGER_CPP

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;
//defining the ONLY instance here, and then the header file checks this to ensure only one


bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

  if(pTempSurface == 0)
  {
    return false;
    //error out, could not find image name
  }

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  // everything went ok, add the texture to our list
  if(pTexture != 0)
  {
    m_textureMap[id] = pTexture;
    return true;
  }

  // reaching here means something went wrong
  return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  //could use some error checking for if the id is not in the texture map?
  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::drawFrame(std::string id,int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip){
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x  = width * (currentFrame - 1);    //width of frame * cur makes it select which part of animation
  srcRect.y = height * (currentRow - 1);  //same deal here
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  SDL_RenderCopyEx(pRenderer, m_textureMap[id],&srcRect, &destRect, 0,0,flip);
  //note: the row is not zero indexed in this implementation
}

#endif
