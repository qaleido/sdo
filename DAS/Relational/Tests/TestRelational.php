<?php
/* 
+----------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2005.                                  |
| All Rights Reserved.                                                 |
+----------------------------------------------------------------------+
|                                                                      |
| Licensed under the Apache License, Version 2.0 (the "License"); you  |
| may not use this file except in compliance with the License. You may |
| obtain a copy of the License at                                      |
| http://www.apache.org/licenses/LICENSE-2.0                           |
|                                                                      |
| Unless required by applicable law or agreed to in writing, software  |
| distributed under the License is distributed on an "AS IS" BASIS,    |
| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
| implied. See the License for the specific language governing         |
| permissions and limitations under the License.                       |
+----------------------------------------------------------------------+
| Author: Matthew Peters                                               |
+----------------------------------------------------------------------+

*/
/**
 * Test case for SDORDAS class
 *
 */
require_once 'PHPUnit2/Framework/TestCase.php';
require_once 'PHPUnit2/Framework/IncompleteTestError.php';

require_once 'SDO/DAS/Relational.php';

class TestRelational extends PHPUnit2_Framework_TestCase
{
	public function __construct($name) {
		parent::__construct($name);
	}

	public function testMustHaveSomeDatabaseMetadata() {
		$database_metadata = null;
		$exception_thrown = false;
		try {
			$das = new SDO_DAS_Relational ($database_metadata);
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue($exception_thrown,'Exception was never thrown');
		$this->assertTrue(strpos($msg,'must not be null') != 0,'Wrong message issued: '.$msg);
	}

	public function testApplicationRootTypeCanBeNullIfExactlyOneTable() {
		$company_table_metadata = array(
		'name' => 'company',
		'columns'=> array('id'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table_metadata);

		$exception_thrown = false;
		try {
			$das = new SDO_DAS_Relational($database_metadata);
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue(! $exception_thrown,'Unexpected exception was thrown:' . $msg);
	}

	public function testApplicationRootTypeCannotBeNullIfMoreThanOneTable() {
		$company_table_metadata = array(
		'name' => 'company',
		'columns'=> array('id'),
		'PK' => 'id',
		);
		$department_table_metadata = array(
		'name' => 'department',
		'columns'=> array('id'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table_metadata, $department_table_metadata);

		$exception_thrown = false;
		try {
			$das = new SDO_DAS_Relational($database_metadata);
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue($exception_thrown,'Exception was never thrown');
		$this->assertTrue(strpos($msg,'exactly one table') != 0,'Wrong message issued: '.$msg);
	}


	public function testReferencesMetadataCanBeNull() {
		$company_table_metadata = array(
		'name' => 'company',
		'columns'=> array('id'),
		'PK' => 'id',
		);
		$department_table_metadata = array(
		'name' => 'department',
		'columns'=> array('id'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table_metadata, $department_table_metadata);

		$exception_thrown = false;
		try {
			$das = new SDO_DAS_Relational($database_metadata,'company',null);
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue(! $exception_thrown,'Unexpected exception was thrown:' . $msg);
	}


	public function testSQLStatementMustBeAString() {
		$company_table = array (
		'name' => 'company',
		'columns' => array('id', 'name',  'employee_of_the_month'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table);
		$exception_thrown = false;
		$das = new SDO_DAS_Relational ($database_metadata);
		try {
			$company = $das->executeQuery('dummy PDO handle',3,'rubbish');
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue($exception_thrown,'Exception was never thrown');
		$this->assertTrue(strpos($msg,'second argument') != 0,'Wrong message issued: '.$msg);
		$this->assertTrue(strpos($msg,'must be a string') != 0,'Wrong message issued: '.$msg);
	}

	public function testColumnSpeciferMustBeAnArray() {
		$company_table = array (
		'name' => 'company',
		'columns' => array('id', 'name',  'employee_of_the_month'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table);
		$exception_thrown = false;
		$das = new SDO_DAS_Relational ($database_metadata);
		try {
			$company = $das->executeQuery('dummy PDO handle','SELECT * from company','rubbish');
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue($exception_thrown,'Exception was never thrown');
		$this->assertTrue(strpos($msg,'third argument') != 0,'Wrong message issued: '.$msg);
		$this->assertTrue(strpos($msg,'must be an array') != 0,'Wrong message issued: '.$msg);
	}

	public function testColumnSpeciferMustContainStrings() {
		$company_table = array (
		'name' => 'company',
		'columns' => array('id', 'name',  'employee_of_the_month'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table);
		$exception_thrown = false;
		$das = new SDO_DAS_Relational ($database_metadata);
		try {
			$company = $das->executeQuery('dummy PDO handle','SELECT * from company',array(1,2,3,));
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue($exception_thrown,'Exception was never thrown');
		$this->assertTrue(strpos($msg,'in the column specifier') != 0,'Wrong message issued: '.$msg);
		$this->assertTrue(strpos($msg,'must be a string') != 0,'Wrong message issued: '.$msg);
	}

	public function testColumnSpecifersMustBeValidTableAndColumnNames() {
		$company_table = array (
		'name' => 'company',
		'columns' => array('id', 'name',  'employee_of_the_month'),
		'PK' => 'id',
		);
		$database_metadata = array($company_table);
		$exception_thrown = false;
		$das = new SDO_DAS_Relational ($database_metadata);
		try {
			$company = $das->executeQuery('dummy PDO handle','SELECT * from company',array('not-a-table.not-a-column'));
		} catch (SDO_DAS_Relational_Exception $e) {
			$exception_thrown = true;
			$msg = $e->getMessage();
		}
		$this->assertTrue($exception_thrown,'Exception was never thrown');
		$this->assertTrue(strpos($msg,'table.column') != 0,'Wrong message issued: '.$msg);
	}


}


?>