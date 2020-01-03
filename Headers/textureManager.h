#ifndef _TEXTUREMANAGER_H       
#define _TEXTUREMANAGER_H      
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager
{
    // TextureManager ����
  private:
    UINT       width;       // ����
    UINT       height;      // ����
    LP_TEXTURE texture;     // �ؽ�ó ������ �ּ�
    const char *file;       // �����̸�
    Graphics *graphics;     // graphics ������
    bool    initialized;    // �ʱ�ȭ ���� Ȯ��
    HRESULT hr;             // ���� Ÿ��


	static std::vector<std::pair<LP_TEXTURE, const char*>> TextureList;

  public:
	  

	// ������, �Ҹ���
    TextureManager();
    virtual ~TextureManager();

    // �ؽ�ó�� ����Ű�� �����͸� ��ȯ
    LP_TEXTURE getTexture() const {return texture;}
    UINT getWidth() const {return width;}	// �ؽ�ó�� ���� ��ȯ
    UINT getHeight() const {return height;}	// �ؽ�ó�� ���̸� ��ȯ

	void AddTextureList(LP_TEXTURE inTexture, const char *file);

    virtual bool initialize(Graphics *g, const char *file);

	virtual Graphics* getGrpahics() { return graphics; };
};


#endif

