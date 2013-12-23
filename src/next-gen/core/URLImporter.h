/*
 * URLImporter.h
 *
 *  Created on: 25 nov. 2013
 *
 */

#ifndef _URLIMPORTER_H_
#define _URLIMPORTER_H_

#include <string>

struct ItemRecord;
class CharInfos;
class NPCInfos;

class URLImporter
{
  public:
	URLImporter(){};
	virtual  ~URLImporter(){};

	virtual NPCInfos * importNPC(std::string url) = 0;
	virtual ItemRecord * importItem(std::string url) = 0;
	virtual CharInfos * importChar(std::string url) = 0;
};


#endif /* _URLIMPORTER_H_ */