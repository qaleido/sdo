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

#ifndef _DASDataFactoryIMPL_H_
#define _DASDataFactoryIMPL_H_

#include "DASDataFactory.h"
#include "TypeImpl.h"
#include "RefCountingPointer.h"

#include <map>
using namespace std;

namespace commonj{
namespace sdo{

class  DASDataFactoryImpl  : public DASDataFactory
{
public:
	DASDataFactoryImpl();
	virtual ~DASDataFactoryImpl();

	DASDataFactoryImpl(const DASDataFactoryImpl& inmdg);
	DASDataFactoryImpl& operator=(const DASDataFactoryImpl& inmdg);

    virtual void addType(const char* uri, const char* inTypeName,
		bool isSeq = false, bool isOp = false);


	virtual void addPropertyToType(const char* uri, 
		                           const char* inTypeName,
		                           const char* propname,
								   const char* propTypeUri, 
		                           const char* propTypeName,
								   bool many = false);


	virtual void addPropertyToType(const char* uri, 
		                           const char* inTypeName,
		                           const char* propname,
								   const Type& propType,
								   bool many = false);

	virtual void addPropertyToType(const Type& type, 
		                           const char* propname,
								   const Type& propType,
								   bool many = false);
	
	virtual void addPropertyToType(const Type& type, 
		                           const char* propname,
								   const char* propTypeUri, 
		                           const char* propTypeName,
								   bool many = false);

	virtual void addPropertyToType(const char* uri, 
		                           const char* inTypeName,
		                           const char* propname,
								   const char* propTypeUri, 
		                           const char* propTypeName,
								   bool	 many ,
								   bool  rdonly,
								   bool  cont);

	virtual void addPropertyToType(const char* uri, 
		                           const char* inTypeName,
		                           const char* propname,
								   const Type& propType,
								   bool  many,
								   bool  rdonly,
								   bool  cont);
	
	virtual void addPropertyToType(const Type& type, 
		                           const char* propname,
								   const Type& propType,
								   bool  many,
								   bool  rdonly,
								   bool  cont);

	virtual void addPropertyToType(const Type& type, 
		                           const char* propname,
								   const char* propTypeUri, 
		                           const char* propTypeName,
								   bool  many,
								   bool  rdonly,
								   bool  cont);


	virtual void setBaseType( const Type& type,
		                      const Type& base);

	virtual void setBaseType( const char* typeuri,
		                      const char* typenam,
							  const char* baseuri,
							  const char* basename);

	virtual const Type& getType(const char* uri, const char* inTypeName) const;

	virtual TypeList getTypes() const;

	virtual DataObjectPtr create(const char* uri, const char* typeName) ;

	virtual DataObjectPtr create(const Type& type) ;

	virtual void setAlias(const char* typeuri,
		                          const char* typenam,
								  const char* alias) ;

	virtual void setAlias(const char* typeuri, 
		                          const char* typname, 
								  const char* propname,
								  const char* alias) ;


	////////////////////////////////////////////////////////
	virtual SDO_API void setDefault(
		const Type& t, const char* propname, bool b ) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , char c) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , wchar_t c) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , char* c) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , short s) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , long l) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , int64_t i) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , float f) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , long double d) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , const wchar_t* c, unsigned int len) ;
	virtual SDO_API void setDefault(
		const Type& t, const char* propname , const char* c, unsigned int len) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname, bool b ) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , char c) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , wchar_t c) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , char* c) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , short s) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , long l) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , int64_t i) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , float f) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , long double d) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , const wchar_t* c, unsigned int len) ;
	virtual SDO_API void setDefault(
		const char* typuri, const char* typnam, const char* propname , const char* c, unsigned int len) ;

	virtual void setDASValue( 
			const Type& type,
				const char* name,
				DASValue* value);

	virtual void setDASValue(
				const char* typeuri,
				const char* typenam,
				const char* name,
				DASValue* value);

	virtual DASValue* getDASValue(
				const Type& type,
				const char* name) const;

	virtual DASValue* getDASValue(
				const char* typeuri,
				const char* typenam, 
				const char* name) const;

	virtual void setDASValue( 
				const Type& type,
				const char* propertyName,
				const char* name,
				DASValue* value);

	virtual void setDASValue( 
				const char* typeuri,
				const char* typenam,
				const char* propertyName,
				const char* name,
				DASValue* value);

	virtual DASValue* getDASValue( 
				const Type& type,
				const char* propertyName,
				const char* name) const;

	virtual DASValue* getDASValue(
				const char* typeuri,
				const char* typenam,
				const char* propertyName, 
				const char* name) const;

private:
	typedef map<string, TypeImpl*> TYPES_MAP;
	TYPES_MAP	types;

	// Need to validate and 'lock' the data model for base types to
	// work properly.

	bool isResolved;
	void resolve();
	
	bool recursiveCheck(TypeImpl* cs, TypeImpl* t);
	bool DASDataFactoryImpl::checkForValidChangeSummary(TypeImpl* t);

	typedef vector<TypeImpl*> TYPES_VECTOR;
	TYPES_VECTOR cstypes;
	
	char*		getFullTypeName(const char* uri, const char* inTypeName) const;
	char*		getAliasTypeName(const char* uri, const char* inTypeName) const;
	const Type*	findType  (const char* uri, const char* inTypeName) const;
	const TypeImpl*	findTypeImpl  (const char* uri, const char* inTypeName) const;
	virtual const TypeImpl& getTypeImpl(const char* uri, const char* inTypeName) const;

	void		copyTypes(const DASDataFactoryImpl& inmdg);
};
};
};
#endif // _DASDataFactoryIMPL_H_
