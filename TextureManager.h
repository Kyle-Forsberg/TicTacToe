#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <exception>



class TextureManager{
    public:
//loading a sprite into renderer
  bool load(std::string filename, std::string id, SDL_Renderer * pRenderer);

//draw a static image
  void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip);

//draw a frame of a sprite
  void drawFrame(std::string id, int x, int y,int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip);
 
  std::map<std::string, SDL_Texture*> m_textureMap;

	private:
  TextureManager() {}
  //you may ask why the constructor is private? well we want this class to be a singleton (only one instance) and this helps facilitate that.

public:
  static TextureManager * s_pInstance;

  static TextureManager * Instance()
  {  
	if(s_pInstance == 0){
		s_pInstance = new TextureManager();
		return s_pInstance;
	}
	return s_pInstance;	//if there was one return it
  }	

};
typedef TextureManager TheTextureManager;


#endif
