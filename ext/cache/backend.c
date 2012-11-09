
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

#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"

/**
 * Phalcon\Cache\Backend
 *
 * This class implements common functionality for backend adapters. All the backend cache adapter must
 * extend this class
 */


/**
 * Phalcon\Cache\Backend initializer
 */
PHALCON_INIT_CLASS(Phalcon_Cache_Backend){

	PHALCON_REGISTER_CLASS(Phalcon\\Cache, Backend, cache_backend, phalcon_cache_backend_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalcon_cache_backend_ce, SL("_frontendObject"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_cache_backend_ce, SL("_backendOptions"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_cache_backend_ce, SL("_prefix"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_cache_backend_ce, SL("_lastKey"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(phalcon_cache_backend_ce, SL("_fresh"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(phalcon_cache_backend_ce, SL("_started"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}

/**
 * Phalcon\Cache\Backend constructor
 *
 * @param mixed $frontendObject
 * @param array $backendOptions
 */
PHP_METHOD(Phalcon_Cache_Backend, __construct){

	zval *frontend_object, *backend_options = NULL, *prefix;
	int eval_int;

	PHALCON_MM_GROW();

	phalcon_update_property_empty_array(phalcon_cache_backend_ce, this_ptr, SL("_backendOptions") TSRMLS_CC);
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &frontend_object, &backend_options) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!backend_options) {
		PHALCON_INIT_NVAR(backend_options);
		array_init(backend_options);
	}
	
	if (Z_TYPE_P(frontend_object) != IS_OBJECT) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_cache_exception_ce, "Frontend must be an Object");
		return;
	}
	eval_int = phalcon_array_isset_string(backend_options, SS("prefix"));
	if (eval_int) {
		PHALCON_INIT_VAR(prefix);
		phalcon_array_fetch_string(&prefix, backend_options, SL("prefix"), PH_NOISY_CC);
		phalcon_update_property_zval(this_ptr, SL("_prefix"), prefix TSRMLS_CC);
	}
	
	phalcon_update_property_zval(this_ptr, SL("_frontendObject"), frontend_object TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, SL("_backendOptions"), backend_options TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Starts a cache. The $keyname allows to identify the created fragment
 *
 * @param int|string $keyName
 * @return  mixed
 */
PHP_METHOD(Phalcon_Cache_Backend, start){

	zval *key_name, *backend, *front_end, *existing_cache;
	zval *fresh = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(backend);
	phalcon_read_property(&backend, this_ptr, SL("_backendOptions"), PH_NOISY_CC);
	
	PHALCON_INIT_VAR(front_end);
	phalcon_read_property(&front_end, this_ptr, SL("_frontendObject"), PH_NOISY_CC);
	
	PHALCON_INIT_VAR(existing_cache);
	PHALCON_CALL_METHOD_PARAMS_1(existing_cache, this_ptr, "get", key_name, PH_NO_CHECK);
	if (Z_TYPE_P(existing_cache) == IS_NULL) {
		PHALCON_INIT_VAR(fresh);
		ZVAL_BOOL(fresh, 1);
		PHALCON_CALL_METHOD_NORETURN(front_end, "start", PH_NO_CHECK);
	} else {
		PHALCON_INIT_NVAR(fresh);
		ZVAL_BOOL(fresh, 0);
	}
	
	phalcon_update_property_zval(this_ptr, SL("_fresh"), fresh TSRMLS_CC);
	phalcon_update_property_bool(this_ptr, SL("_started"), 1 TSRMLS_CC);
	
	RETURN_CCTOR(existing_cache);
}

/**
 * Stops the frontend without store any cached content
 *
 * @param boolean $stopBuffer
 */
PHP_METHOD(Phalcon_Cache_Backend, stop){

	zval *stop_buffer = NULL, *front_end;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &stop_buffer) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!stop_buffer) {
		PHALCON_INIT_NVAR(stop_buffer);
		ZVAL_BOOL(stop_buffer, 1);
	}
	
	PHALCON_INIT_VAR(front_end);
	phalcon_read_property(&front_end, this_ptr, SL("_frontendObject"), PH_NOISY_CC);
	if (PHALCON_IS_TRUE(stop_buffer)) {
		PHALCON_CALL_METHOD_NORETURN(front_end, "stop", PH_NO_CHECK);
	}
	
	phalcon_update_property_bool(this_ptr, SL("_started"), 0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns front-end instance adapter related to the back-end
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Cache_Backend, getFrontend){


	RETURN_MEMBER(this_ptr, "_frontendObject");
}

/**
 * Checks whether the last cache is fresh or cached
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Cache_Backend, isFresh){


	RETURN_MEMBER(this_ptr, "_fresh");
}

/**
 * Checks whether the cache has starting buffering or not
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Cache_Backend, isStarted){


	RETURN_MEMBER(this_ptr, "_started");
}

/**
 * Gets the last key stored by the cache
 *
 * @return string
 */
PHP_METHOD(Phalcon_Cache_Backend, getLastKey){


	RETURN_MEMBER(this_ptr, "_lastKey");
}

PHP_METHOD(Phalcon_Cache_Backend, get){


	
}

