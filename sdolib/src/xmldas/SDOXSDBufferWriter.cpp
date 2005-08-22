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
static char rcs_id[] = "$Id$";

#include "SDOXSDBufferWriter.h"
#include "SDORuntimeException.h"

namespace commonj
{
	namespace sdo
	{
		
		namespace xmldas
		{
			
			
			
			SDOXSDBufferWriter::SDOXSDBufferWriter()
			{
				buf = xmlBufferCreate();
				if (buf == NULL) 
				{
					SDO_THROW_EXCEPTION("SDOXSDBufferWriter", SDOXMLParserException, "xmlBufferCreate failed");
				}
				setWriter(xmlNewTextWriterMemory(buf, 0));				
			}
			
			SDOXSDBufferWriter::~SDOXSDBufferWriter()
			{
				freeWriter();
				xmlBufferFree(buf);
			}
			
			SDOXMLString SDOXSDBufferWriter::getBuffer()
			{
				freeWriter();
				return xmlBufferContent(buf);
			}			
		} // End - namespace xmldas
	} // End - namespace sdo
} // End - namespace commonj
