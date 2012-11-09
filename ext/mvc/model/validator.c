
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
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"

/**
 * Phalcon\Mvc\Model\Validator
 *
 * This is a base class for Phalcon\Mvc\Model validators
 */


/**
 * Phalcon\Mvc\Model\Validator initializer
 */
PHALCON_INIT_CLASS(Phalcon_Mvc_Model_Validator){

	PHALCON_REGISTER_CLASS(Phalcon\\Mvc\\Model, Validator, mvc_model_validator, phalcon_mvc_model_validator_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalcon_mvc_model_validator_ce, SL("_options"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_validator_ce, SL("_messages"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Validator constructor
 *
 * @param array $options
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator, __construct){

	zval *options;

	PHALCON_MM_GROW();

	phalcon_update_property_empty_array(phalcon_mvc_model_validator_ce, this_ptr, SL("_options") TSRMLS_CC);
	
	phalcon_update_property_empty_array(phalcon_mvc_model_validator_ce, this_ptr, SL("_messages") TSRMLS_CC);
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &options) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(options) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "$options argument must be an Array");
		return;
	}
	phalcon_update_property_zval(this_ptr, SL("_options"), options TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Appends a message to the validator
 *
 * @param string $message
 * @param string $field
 * @param string $type
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator, appendMessage){

	zval *message, *field = NULL, *type = NULL, *class_name, *suffix;
	zval *empty_string, *model_message;
	zval *t0 = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|zz", &message, &field, &type) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!field) {
		PHALCON_INIT_NVAR(field);
	}
	
	if (!type) {
		PHALCON_INIT_NVAR(type);
	} else {
		PHALCON_SEPARATE_PARAM(type);
	}
	
	if (!zend_is_true(type)) {
		PHALCON_INIT_VAR(class_name);
		phalcon_get_class(class_name, this_ptr TSRMLS_CC);
	
		PHALCON_INIT_VAR(suffix);
		ZVAL_STRING(suffix, "Validator", 1);
	
		PHALCON_INIT_VAR(empty_string);
		ZVAL_STRING(empty_string, "", 1);
	
		PHALCON_INIT_NVAR(type);
		phalcon_fast_str_replace(type, suffix, empty_string, class_name TSRMLS_CC);
	}
	
	PHALCON_INIT_VAR(model_message);
	object_init_ex(model_message, phalcon_mvc_model_message_ce);
	PHALCON_CALL_METHOD_PARAMS_3_NORETURN(model_message, "__construct", message, field, type, PH_CHECK);
	
	PHALCON_INIT_VAR(t0);
	phalcon_read_property(&t0, this_ptr, SL("_messages"), PH_NOISY_CC);
	phalcon_array_append(&t0, model_message, 0 TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, SL("_messages"), t0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns messages generated by the validator
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator, getMessages){

	zval *messages;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(messages);
	phalcon_read_property(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	
	RETURN_CCTOR(messages);
}

/**
 * Returns all the options from the validator
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator, getOptions){

	zval *options;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(options);
	phalcon_read_property(&options, this_ptr, SL("_options"), PH_NOISY_CC);
	
	RETURN_CCTOR(options);
}

/**
 * Returns an option
 *
 * @param string $option
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator, getOption){

	zval *option, *options, *value;
	int eval_int;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &option) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(options);
	phalcon_read_property(&options, this_ptr, SL("_options"), PH_NOISY_CC);
	eval_int = phalcon_array_isset(options, option);
	if (eval_int) {
		PHALCON_INIT_VAR(value);
		phalcon_array_fetch(&value, options, option, PH_NOISY_CC);
	
		RETURN_CCTOR(value);
	}
	
	PHALCON_MM_RESTORE();
	RETURN_STRING("", 1);
}

/**
 * Check whether a option has been defined in the validator options
 *
 * @param string $option
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator, isSetOption){

	zval *option, *options, *is_set = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &option) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(options);
	phalcon_read_property(&options, this_ptr, SL("_options"), PH_NOISY_CC);
	eval_int = phalcon_array_isset(options, option);
	
	PHALCON_INIT_VAR(r0);
	ZVAL_BOOL(r0, eval_int);
	PHALCON_CPY_WRT(is_set, r0);
	
	RETURN_NCTOR(is_set);
}

