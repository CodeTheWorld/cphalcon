
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/fcall.h"
#include "kernel/object.h"

/**
 * Phalcon\DI\FactoryDefault\CLI
 *
 * This is a variant of the standard Phalcon\DI. By default it automatically
 * registers all the services provided by the framework.
 * Thanks to this, the developer does not need to register each service individually.
 * This class is specially suitable for CLI applications
 */


/**
 * Phalcon\DI\FactoryDefault\CLI initializer
 */
PHALCON_INIT_CLASS(Phalcon_DI_FactoryDefault_CLI){

	PHALCON_REGISTER_CLASS_EX(Phalcon\\DI\\FactoryDefault, CLI, di_factorydefault_cli, "phalcon\\di\\factorydefault", phalcon_di_factorydefault_cli_method_entry, 0);

	return SUCCESS;
}

/**
 * Phalcon\DI\FactoryDefault\CLI constructor
 */
PHP_METHOD(Phalcon_DI_FactoryDefault_CLI, __construct){

	zval *services;

	PHALCON_MM_GROW();

	PHALCON_CALL_PARENT_NORETURN(this_ptr, "Phalcon\\DI\\FactoryDefault\\CLI", "__construct");
	
	PHALCON_INIT_VAR(services);
	array_init(services);
	add_assoc_stringl_ex(services, SS("router"), SL("Phalcon\\CLI\\Router"), 1);
	add_assoc_stringl_ex(services, SS("dispatcher"), SL("Phalcon\\CLI\\Dispatcher"), 1);
	add_assoc_stringl_ex(services, SS("modelsManager"), SL("Phalcon\\Mvc\\Model\\Manager"), 1);
	add_assoc_stringl_ex(services, SS("modelsMetadata"), SL("Phalcon\\Mvc\\Model\\Metadata\\Memory"), 1);
	add_assoc_stringl_ex(services, SS("filter"), SL("Phalcon\\Filter"), 1);
	add_assoc_stringl_ex(services, SS("flash"), SL("Phalcon\\Flash\\Direct"), 1);
	add_assoc_stringl_ex(services, SS("eventsManager"), SL("Phalcon\\Events\\Manager"), 1);
	phalcon_update_property_zval(this_ptr, SL("_services"), services TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

