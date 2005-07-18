/* 
+----------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2005.                                  | 
| All Rights Reserved.                                                 |
+----------------------------------------------------------------------+ 
|                                                                      | 
| Licensed under the Apache License, Version 2.0 (the "License"); you  | 
| may not use this file except in compliance with the License. You may | 
| obtain a copy of the License at                                      | 
|  http://www.apache.org/licenses/LICENSE-2.0                          |
|                                                                      | 
| Unless required by applicable law or agreed to in writing, software  | 
| distributed under the License is distributed on an "AS IS" BASIS,    | 
| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      | 
| implied. See the License for the specific language governing         | 
| permissions and limitations under the License.                       | 
+----------------------------------------------------------------------+ 
| Author: Ed Slattery                                                  | 
+----------------------------------------------------------------------+ 

*/

#include "SDORuntimeException.h"

#include "SettingList.h"
#include "Logger.h"
#include "Setting.h"

namespace commonj{
namespace sdo {


SettingList::SettingList(SETTING_VECTOR p) : slist (p)
{
	Logger::log("SettingList constructed from vector\n");
}

/*SettingList::SettingList(const SettingList &pin)
{
	Logger::log("SettingList copy constructor\n");
	slist = std::vector<Setting>(pin.getVec());
}
*/

SettingList::SettingList()
{
	Logger::log("SettingList default constructor\n");
}

SettingList::~SettingList()
{
	Logger::log("SettingList destructor\n");
}


Setting& SettingList::operator[] (int pos) const
{	
	validateIndex(pos);
	return (Setting&)slist[pos];
}

int SettingList::size () const
{
	return slist.size();
}

SETTING_VECTOR SettingList::getVec() const
{
	return slist;
}

void SettingList::insert (unsigned int index, const Setting& d)
{
	slist.insert(slist.begin()+index, d);
}

void SettingList::append (const Setting& d)
{
	slist.insert(slist.end(),d);
}

void SettingList::remove(unsigned int index)
{
	validateIndex(index);
	slist.erase(slist.begin()+index);
	return;
}

void SettingList::validateIndex(int index) const
{
	if ((index < 0) || (index > size()))
	{
		string msg("Index out of range:");
		msg += index;
		SDO_THROW_EXCEPTION("ValidateIndex", SDOIndexOutOfRangeException,
			msg.c_str());

	}

}

};
};

