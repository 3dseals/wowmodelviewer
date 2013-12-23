/*
 * WowheadImporter.cpp
 *
 *  Created on: 1 déc. 2013
 *
 */

#include "WowheadImporter.h"

#include "database.h" // ItemRecord
#include "NPCInfos.h"
#include "util.h" // CSConv

#include <wx/sstream.h>
#include <wx/url.h>
#include <wx/html/htmlpars.h>

WowheadImporter::WowheadImporter()
{

}

WowheadImporter::~WowheadImporter()
{

}


NPCInfos * WowheadImporter::importNPC(std::string urlToGrab)
{
	NPCInfos * result = NULL;

	wxURL url(urlToGrab);
	if(url.GetError()==wxURL_NOERR)
	{
		wxString htmldata;
		wxInputStream *in = url.GetInputStream();

		if(in && in->IsOk())
		{
			wxStringOutputStream html_stream(&htmldata);
			in->Read(html_stream);

			std::string content(html_stream.GetString().ToAscii());

			// let's go : finding name
			// extract global infos
			std::string pattern("(g_npcs[");
			std::string patternEnd(";");
			std::size_t beginIndex = content.find(pattern);
			std::string infos = content.substr(beginIndex);
			std::size_t endIndex = infos.find(patternEnd);
			infos = infos.substr(0,endIndex);

			// finding name
			std::string NPCName = extractSubString(infos,"name\":\"","\",");

			// finding type
			std::string NPCType = extractSubString(infos,"type\":","}");

			// finding id
			std::string NPCId = extractSubString(infos,"id\":",",");

			// display id
			pattern = "ModelViewer.show({";
			std::string NPCDispId = content.substr(content.find(pattern)+pattern.length());
			NPCDispId = extractSubString(NPCDispId,"displayId: "," ");

			if(NPCDispId.find(",") != std::string::npos) // comma at end of id
				NPCDispId = NPCDispId.substr(0,NPCDispId.find(","));

			result = new NPCInfos();

			result->name = CSConv(NPCName).mb_str();
			result->type = atoi(NPCType.c_str());
			result->id = atoi(NPCId.c_str());
			result->displayId = atoi(NPCDispId.c_str());

		}
		delete in;
	}
	return result;
}

ItemRecord * WowheadImporter::importItem(std::string urlToGrab)
{
	ItemRecord * result = NULL;

	wxURL url(urlToGrab);
	if(url.GetError()==wxURL_NOERR)
	{
		wxString htmldata;
		wxInputStream *in = url.GetInputStream();

		if(in && in->IsOk())
		{
			wxStringOutputStream html_stream(&htmldata);
			in->Read(html_stream);

			std::string content(html_stream.GetString().ToAscii());

			// let's go : finding name
			// extract global infos
			std::string pattern("(g_items[");
			std::string patternEnd(";");
			std::size_t beginIndex = content.find(pattern);
			std::string infos = content.substr(beginIndex);
			std::size_t endIndex = infos.find(patternEnd);
			infos = infos.substr(0,endIndex);

			// finding name
			// due to specific stuff on index, name is treated here, not with method like others
			pattern = "name\":\"";
			patternEnd = "\",";
			std::string itemName = infos.substr(infos.find(pattern)+pattern.length());
			itemName = itemName.substr(1,itemName.find(patternEnd)-1); // first char is a number in name

			// finding type
			std::string itemType = extractSubString(infos,"slot\":", "}");

			// finding id
			std::string itemId = extractSubString(infos,"[", "]");

			// display id
			std::string itemDisplayId = extractSubString(infos,"displayid\":", "\",");

			// class
			// 3 sss it's not a typo (probably to avoid conflict with "class" keyword in javascript)
			std::string itemClass = extractSubString(infos,"classs\":", "\",");

			// subclass
			std::string idemSubClass = extractSubString(infos,"subclass\":", "\",");

			result = new ItemRecord();

			result->name = CSConv(itemName).mb_str();
			result->type = atoi(itemType.c_str());
			result->id = atoi(itemId.c_str());
			result->model = atoi(itemDisplayId.c_str());
			result->itemclass = atoi(itemClass.c_str());
			result->subclass = atoi(idemSubClass.c_str());
		}
		delete in;
	}
	return result;
}

std::string WowheadImporter::extractSubString(std::string & datas, std::string beginPattern, std::string endPattern)
{
	std::string result;
	try
	{
		result = datas.substr(datas.find(beginPattern)+beginPattern.length());
		result = result.substr(0,result.find(endPattern));
	}
	catch(...)
	{
	}
	return result;
}