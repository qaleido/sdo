<?php
/**
+-----------------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2007.                                         |
| All Rights Reserved.                                                        |
+-----------------------------------------------------------------------------+
| Licensed under the Apache License, Version 2.0 (the "License"); you may not |
| use this file except in compliance with the License. You may obtain a copy  |
| of the License at -                                                         |
|                                                                             |
|                   http://www.apache.org/licenses/LICENSE-2.0                |
|                                                                             |
| Unless required by applicable law or agreed to in writing, software         |
| distributed under the License is distributed on an "AS IS" BASIS, WITHOUT   |
| WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.            |
| See the License for the specific language governing  permissions and        |
| limitations under the License.                                              |
+-----------------------------------------------------------------------------+
| Author: Graham Charters,                                                    |
|         Matthew Peters,                                                     |
|         Megan Beynon,                                                       |
|         Chris Miller,                                                       |
|         Caroline Maynard,                                                   |
|         Simon Laws                                                          |
+-----------------------------------------------------------------------------+
$Id: Mapper.php 238265 2007-06-22 14:32:40Z mfp $
 *
 * PHP Version 5
 *
 * @category SCA
 * @package  SCA_SDO
 * @author   Simon Laws <slaws@php.net>
 * @license  Apache http://www.apache.org/licenses/LICENSE-2.0
 * @link     http://www.osoa.org/display/PHP/
 */


/**
 * SCA_Bindings_ebaysoap_Mapper
 *
 * @category SCA
 * @package  SCA_SDO
 * @author   Simon Laws <slaws@php.net>
 * @license  Apache http://www.apache.org/licenses/LICENSE-2.0
 * @link     http://www.osoa.org/display/PHP/
 */
class SCA_Bindings_Ebaysoap_Mapper extends SCA_Bindings_Soap_Mapper
{
    /**
     * Load the WSDL and hence initialise the SDO model
     *
     * @param string $wsdl WSDL
     *
     * @throws SCA_RuntimeException
     * @return null
     */
    public function setWSDLTypes($wsdl)
    {
        SCA::$logger->log('Entering');
        SCA::$logger->log("wsdl is $wsdl");
        try {
            $this->xmldas = @SDO_DAS_XML::create($wsdl, "WEARETHEEBAYSOAPBINDING");
        } catch (Exception $e) {
            $problem = $e->getMessage();
            SCA::$logger->log("exception thrown from create(): $problem");


            if ($e instanceof SDO_Exception ) {
                $problem = "SDO_Exception in setWSDLTypes : " . $problem;
            }

            /**
             * Depending On Whether The Function Is Being Used On The
             * Client Side Or The Server Side Either Report The Problem
             * To The Client, Or Record The Problem In The Error.Log
             */
            trigger_error($problem);

            /* When the 'TypeHandler is being used by the Soap Server */
            if (strcmp($this->association, self::SERVER) === 0) {
                throw new SoapFault("Client", "Invalid WSDL Type");
            }
        }
    }
}