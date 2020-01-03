#ifndef _TEXTUREMANAGER_H       
#define _TEXTUREMANAGER_H      
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager
{
    // TextureManager 설정
  private:
    UINT       width;       // 가로
    UINT       height;      // 세로
    LP_TEXTURE texture;     // 텍스처 포인터 주소
    const char *file;       // 파일이름
    Graphics *graphics;     // graphics 포인터
    bool    initialized;    // 초기화 성공 확인
    HRESULT hr;             // 리턴 타입


	static std::vector<std::pair<LP_TEXTURE, const char*>> TextureList;

  public:
	  

	// 생성자, 소멸자
    TextureManager();
    virtual ~TextureManager();

    // 텍스처를 가리키는 포인터를 반환
    LP_TEXTURE getTexture() const {return texture;}
    UINT getWidth() const {return width;}	// 텍스처의 폭을 반환
    UINT getHeight() const {return height;}	// 텍스처의 높이를 반환

	void AddTextureList(LP_TEXTURE inTexture, const char *file);

    virtual bool initialize(Graphics *g, const char *file);

	virtual Graphics* getGrpahics() { return graphics; };
};


#endif

