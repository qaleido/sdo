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
| Author: Pete Robbins                                                 | 
+----------------------------------------------------------------------+ 

*/

#ifndef _SDOSAX2PARSER_H_
#define _SDOSAX2PARSER_H_
#include "SAX2Parser.h"

#include "DASDataFactory.h"
#include "DASDataObject.h"
#include "SAX2Namespaces.h"
#include "PropertySetting.h"

#include <stack>

namespace commonj
{
	namespace sdo
	{
		
		namespace xmldas
		{
			
			class SDOSAX2Parser : public SAX2Parser
			{
				
			public:
				
				SDOSAX2Parser(
					DASDataFactoryPtr df,
					const SDOXMLString& targetNamespaceURI,
					DataObjectPtr& rootDO);
				
				virtual ~SDOSAX2Parser();

				virtual void startDocument();
				virtual void endDocument();
				
				virtual void startElementNs(
					const SDOXMLString& localname,
					const SDOXMLString& prefix,
					const SDOXMLString& URI,
					const SAX2Namespaces& namespaces,
					const SAX2Attributes& attributes);
				
				virtual void endElementNs(
					const SDOXMLString& localname,
					const SDOXMLString& prefix,
					const SDOXMLString& URI);
				
				virtual void characters(const SDOXMLString& chars);

				friend std::istream& operator>>(std::istream& input, SDOSAX2Parser& parser);
				friend std::istringstream& operator>>(std::istringstream& input, SDOSAX2Parser& parser);
				
			private:
				SDOXMLString targetNamespaceURI;
				DASDataFactoryPtr dataFactory;
				DataObjectPtr&  rootDataObject;
				
				std::stack<DataObjectPtr>	dataObjectStack;
				DataObjectPtr	currentDataObject;
				bool			isDataGraph;
				
				void			setCurrentDataObject(DataObjectPtr currentDO);
				const Type*		currentDataObjectType;

				PropertySetting currentPropertySetting;

				void reset();

				bool setNamespaces;
				SAX2Namespaces documentNamespaces;

				bool changeSummary;
				DataObjectPtr changeSummaryDO;
				bool changeSummaryLogging;

				bool ignoreEvents;
				struct ignoretag
				{
					SDOXMLString localname;
					SDOXMLString uri;
					SDOXMLString prefix;
					int			 tagCount;
				} ignoreTag;


				typedef std::map<SDOXMLString, DataObjectPtr> ID_MAP;
				ID_MAP IDMap;

				class IDRef
				{
				public:
					IDRef(DataObjectPtr dataobj,
					const SDOXMLString& prop,
					const SDOXMLString& val)
					: dataObject(dataobj), property(prop), value(val)
					{}

					DataObjectPtr dataObject;
					SDOXMLString property;
					SDOXMLString value;
				};

				typedef std::list<IDRef> ID_REFS;
				ID_REFS IDRefs;					
			};
		} // End - namespace xmldas
	} // End - namespace sdo
} // End - namespace commonj

#endif //_SDOSAX2PARSER_H_