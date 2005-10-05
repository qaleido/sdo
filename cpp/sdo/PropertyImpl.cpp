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
/* $Id$ */
 
#include <iostream>
using namespace std;

#ifndef SDO_EXPORTS 
#define SDO_EXPORTS
#endif
#include "export.h"


#include "Sequence.h"
#include "DataObject.h"
#include "TypeList.h"

#include "Type.h"
#include "TypeImpl.h"
#include "Property.h"
#include "PropertyImpl.h"

namespace commonj{
namespace sdo{
	



    ///////////////////////////////////////////////////////////////////////////
    // construction by DAS 
	///////////////////////////////////////////////////////////////////////////
    
	PropertyImpl::PropertyImpl(	const Type& cont, 
						const char* inname, 
						const TypeImpl& intype, 
						bool many ,	
						bool ro ,
						bool contain) : containertype(cont), type (intype)
	{
		name = new char[strlen(inname)+1];
		strcpy(name,inname);
		defvalue = 0;
		defvaluelength = 0;
		stringdef = 0;
		bisMany = many;
		bisReadOnly = ro;
		bisContainer = contain;
		if (contain == false && intype.isDataObjectType())
		{
			bisReference = true;
		}
		else 
		{
			bisReference = false;
		}
	}


	PropertyImpl::PropertyImpl(const PropertyImpl& p) : 
		                               type(p.getTypeImpl()),
		                               containertype (p.getContainingType())
		
		               
	{
        name = new char[strlen(p.getName()+1)];
		strcpy(name,p.getName());
		defvalue = 0;
		defvaluelength = 0;
        stringdef = 0;
        bisMany = p.bisMany;
		bisReadOnly = p.bisReadOnly;
		bisContainer = p.bisContainer;
		if (bisContainer == false && type.isDataObjectType())
		{
			bisReference = true;
		}
		else 
		{
			bisReference = false;
		}
	}

	
	PropertyImpl::~PropertyImpl()
	{
		if (name != 0) delete name;
		if (defvalue != 0) delete defvalue;
		if (stringdef != 0) delete stringdef;
	    for (int i = 0; i < aliases.size();i++)
		 {
			 delete ((char*)aliases[i]);
		 }

	}

    ///////////////////////////////////////////////////////////////////////////
    // Setting of attributes  by DAS 
	///////////////////////////////////////////////////////////////////////////

	void PropertyImpl::setMany(bool many)
	{
		bisMany = many;
	}

	void PropertyImpl::setReadOnly(bool readonly)
	{
		bisReadOnly = readonly;
	}

	void PropertyImpl::setContainment(bool contains)
	{
		if (contains == true && type.isDataType())
		{
			return;
		}
		bisContainer = contains;
		if (bisContainer == false && type.isDataObjectType())
		{
			bisReference = true;
		}
		else 
		{
			bisReference = false;
		}
	}


    ///////////////////////////////////////////////////////////////////////////
    // Setting of defaults by DAS 
	///////////////////////////////////////////////////////////////////////////

	void PropertyImpl::setDefault(bool b )
	{
		setDefaultBoolean(b);
	}

	void PropertyImpl::setDefault(char c )
	{
		setDefaultByte(c);
	}

	void PropertyImpl::setDefault(wchar_t c )
	{
		setDefaultCharacter(c);
	}
	void PropertyImpl::setDefault(char* c )
	{
		setDefaultCString(c);
	}
	void PropertyImpl::setDefault(short s )
	{
		setDefaultShort(s);
	}
	void PropertyImpl::setDefault(long i )
	{
		setDefaultInteger(i);
	}
	void PropertyImpl::setDefault(int64_t i )
	{
		setDefaultLong(i);
	}
	void PropertyImpl::setDefault(float f )
	{
		setDefaultFloat(f);
	}
	void PropertyImpl::setDefault(long double d )
	{
		setDefaultDouble(d);
	}
	void PropertyImpl::setDefault(const SDODate d )
	{
		setDefaultDate(d);
	}
	void PropertyImpl::setDefault(const char* c , unsigned int len)
	{
		setDefaultBytes(c, len);
	}

	void PropertyImpl::setDefault(const wchar_t* c, unsigned int len )
	{
		setDefaultString(c, len);
	}

	

 	///////////////////////////////////////////////////////////////////////////
    // Returns the name of the property.
   	///////////////////////////////////////////////////////////////////////////
	const char* PropertyImpl::getName() const
	{
  		return name;
	}

	void PropertyImpl::setAlias(const char* alias)
	{
		char* tmp = new char[strlen(alias)+1];
		strcpy(tmp,alias);
		aliases.push_back(tmp); 
	}

	const char* PropertyImpl::getAlias(unsigned int index) const
	{
		if (index < aliases.size())
		{
			return aliases[index];
		}
		return name;
	}

	unsigned int PropertyImpl::getAliasCount() const
	{
		return aliases.size();
	}

  
	///////////////////////////////////////////////////////////////////////////
    // Returns the type of the property.
 	///////////////////////////////////////////////////////////////////////////
	const Type& PropertyImpl::getType() const
	{
		return (Type&)type;
	}

	const Type::Types PropertyImpl::getTypeEnum() const
	{
		return type.getTypeEnum();
	}

 	///////////////////////////////////////////////////////////////////////////
	// Returns the type of the property.
	///////////////////////////////////////////////////////////////////////////
 	const TypeImpl& PropertyImpl::getTypeImpl() const
	{
		return type;
	}
  
	///////////////////////////////////////////////////////////////////////////
    // Returns whether the property is many-valued.
	///////////////////////////////////////////////////////////////////////////
	bool PropertyImpl::isMany() const
	{
  		return bisMany;
	}
  
 	///////////////////////////////////////////////////////////////////////////
    // Returns whether the property is containment.
	///////////////////////////////////////////////////////////////////////////
	bool PropertyImpl::isContainment() const
	{
  		return bisContainer;
	}

 	///////////////////////////////////////////////////////////////////////////
    // Returns whether the property is containment.
	///////////////////////////////////////////////////////////////////////////
	bool PropertyImpl::isReference() const
	{
  		return bisReference;
	}

	///////////////////////////////////////////////////////////////////////////
	// Returns the containing type of this property.
	///////////////////////////////////////////////////////////////////////////
	const Type& PropertyImpl::getContainingType() const
	{
  		return containertype;
	}

	///////////////////////////////////////////////////////////////////////////
	// Returns the opposite.
	///////////////////////////////////////////////////////////////////////////
	const Property* PropertyImpl::getOpposite() const
	{
		//TODO
  		return 0;
	}

	///////////////////////////////////////////////////////////////////////////
    // Returns the default value this property will have in a 
    // data object where the property hasn't been set.
 	///////////////////////////////////////////////////////////////////////////
	const char*      PropertyImpl::getCStringDefault() 
	{
		
		return getTypeImpl().convertToCString(defvalue, &stringdef, defvaluelength);
	}
	bool        PropertyImpl::getBooleanDefault() const
	{
		return getTypeImpl().convertToBoolean(defvalue,defvaluelength);
	}
	char        PropertyImpl::getByteDefault() const
	{
		return getTypeImpl().convertToByte(defvalue,defvaluelength);
	}
	wchar_t     PropertyImpl::getCharacterDefault() const
	{
		return getTypeImpl().convertToCharacter(defvalue,defvaluelength);
	}
	short       PropertyImpl::getShortDefault() const
	{
		return getTypeImpl().convertToShort(defvalue,defvaluelength);
	}
	long        PropertyImpl::getIntegerDefault() const
	{
		return getTypeImpl().convertToInteger(defvalue,defvaluelength);
	}
	int64_t     PropertyImpl::getLongDefault() const
	{
		return getTypeImpl().convertToLong(defvalue,defvaluelength);
	}
	float       PropertyImpl::getFloatDefault() const
	{
		return getTypeImpl().convertToFloat(defvalue,defvaluelength);
	}
	long double PropertyImpl::getDoubleDefault() const
	{
		return getTypeImpl().convertToDouble(defvalue,defvaluelength);
	}
	const SDODate      PropertyImpl::getDateDefault() const 
	{
		return getTypeImpl().convertToDate(defvalue,defvaluelength);
	}
	unsigned int PropertyImpl::getStringDefault(wchar_t* val, unsigned int max) 
	{
		if (val == 0 || max == 0) return defvaluelength; 
		return getTypeImpl().convertToString(defvalue, val, defvaluelength, max);
	
	}
	unsigned int PropertyImpl::getBytesDefault(char* val, unsigned int max) 
	{
		if (val == 0 || max == 0) return defvaluelength; 
		return getTypeImpl().convertToBytes(defvalue, val, defvaluelength, max);
	}


	///////////////////////////////////////////////////////////////////////////
    // sets the default value by type
	///////////////////////////////////////////////////////////////////////////

	void PropertyImpl::setDefaultCString(const char* s) 
	{
		defvaluelength = getTypeImpl().convert(&defvalue,s); 
	}
	void PropertyImpl::setDefaultString(    const wchar_t* c , unsigned int len )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,c, len); 
	}
	void PropertyImpl::setDefaultBytes(    const char* c , unsigned int len )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,c, len); 
	}
	void PropertyImpl::setDefaultBoolean(    const bool b  )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,b); 
	}
	void PropertyImpl::setDefaultByte(    const char c   )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,c); 
	}
	void PropertyImpl::setDefaultCharacter(   const wchar_t c)
	{
		defvaluelength = getTypeImpl().convert(&defvalue,c); 
	}
	void PropertyImpl::setDefaultShort(   const short s  )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,s); 
	}
	void PropertyImpl::setDefaultInteger( const long i    )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,i); 
	}
	void PropertyImpl::setDefaultLong(const int64_t l)
	{
		defvaluelength = getTypeImpl().convert(&defvalue,l); 
	}
	void PropertyImpl::setDefaultFloat(   const float f  )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,f); 
	}
	void PropertyImpl::setDefaultDouble(  const long double d )
	{
		defvaluelength = getTypeImpl().convert(&defvalue,d); 
	}
	void PropertyImpl::setDefaultDate(    const SDODate d )
	{
		defvaluelength = getTypeImpl().convertDate(&defvalue,d); 
	}

	///////////////////////////////////////////////////////////////////////////
    // Returns true if values for this Property cannot be modified using the SDO APIs.
    // When true, DataObject.set(Property property, Object value) throws an exception.
    // Values may change due to other factors, such as services operating on DataObjects.
 	///////////////////////////////////////////////////////////////////////////
	bool PropertyImpl::isReadOnly() const
	{
  		return bisReadOnly;
	}
  
};
};

