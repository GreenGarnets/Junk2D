#ifndef _OBJECTMANAGER_H           
#define _OBJECTMANAGER_H            
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "Junk2DSprite.h"

class ObjectManager {
	
private :

public :

	std::vector<std::pair<Junk2DSprite*, std::string>> ObjectList;

	ObjectManager() {};
	virtual ~ObjectManager() {
		RemoveAllObject();
	};
	void AddObject(Junk2DSprite* p_pObject, std::string objecName);

	void RenderAllObject(int tag);
	void RemoveAllObject();
	void RemoveObject(std::string objecName);

	void RemoveObject(Junk2DSprite * object);

	Junk2DSprite* getCGameObject(std::string ObjectName);
};

#endif