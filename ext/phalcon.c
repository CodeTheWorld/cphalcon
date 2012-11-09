
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

zend_class_entry *phalcon_session_exception_ce;
zend_class_entry *phalcon_session_adapter_files_ce;
zend_class_entry *phalcon_session_bag_ce;
zend_class_entry *phalcon_loader_ce;
zend_class_entry *phalcon_di_ce;
zend_class_entry *phalcon_text_ce;
zend_class_entry *phalcon_mvc_router_exception_ce;
zend_class_entry *phalcon_mvc_router_route_ce;
zend_class_entry *phalcon_mvc_router_ce;
zend_class_entry *phalcon_mvc_micro_ce;
zend_class_entry *phalcon_mvc_dispatcher_exception_ce;
zend_class_entry *phalcon_mvc_collection_exception_ce;
zend_class_entry *phalcon_mvc_collection_manager_ce;
zend_class_entry *phalcon_mvc_view_ce;
zend_class_entry *phalcon_mvc_collection_ce;
zend_class_entry *phalcon_mvc_view_engine_ce;
zend_class_entry *phalcon_mvc_view_exception_ce;
zend_class_entry *phalcon_mvc_view_engine_php_ce;
zend_class_entry *phalcon_mvc_view_engine_volt_ce;
zend_class_entry *phalcon_mvc_view_engine_volt_compiler_ce;
zend_class_entry *phalcon_mvc_url_ce;
zend_class_entry *phalcon_mvc_controller_ce;
zend_class_entry *phalcon_mvc_application_exception_ce;
zend_class_entry *phalcon_mvc_url_exception_ce;
zend_class_entry *phalcon_mvc_dispatcher_ce;
zend_class_entry *phalcon_mvc_model_ce;
zend_class_entry *phalcon_mvc_micro_exception_ce;
zend_class_entry *phalcon_mvc_model_validator_uniqueness_ce;
zend_class_entry *phalcon_mvc_model_validator_presenceof_ce;
zend_class_entry *phalcon_mvc_model_validator_exclusionin_ce;
zend_class_entry *phalcon_mvc_model_validator_regex_ce;
zend_class_entry *phalcon_mvc_model_validator_inclusionin_ce;
zend_class_entry *phalcon_mvc_model_validator_stringlength_ce;
zend_class_entry *phalcon_mvc_model_validator_numericality_ce;
zend_class_entry *phalcon_mvc_model_validator_email_ce;
zend_class_entry *phalcon_mvc_model_query_ce;
zend_class_entry *phalcon_mvc_model_resultset_complex_ce;
zend_class_entry *phalcon_mvc_model_resultset_simple_ce;
zend_class_entry *phalcon_mvc_model_query_status_ce;
zend_class_entry *phalcon_mvc_model_query_lang_ce;
zend_class_entry *phalcon_mvc_model_exception_ce;
zend_class_entry *phalcon_mvc_model_criteria_ce;
zend_class_entry *phalcon_mvc_model_validator_ce;
zend_class_entry *phalcon_mvc_model_row_ce;
zend_class_entry *phalcon_mvc_model_transaction_exception_ce;
zend_class_entry *phalcon_mvc_model_transaction_failed_ce;
zend_class_entry *phalcon_mvc_model_transaction_manager_ce;
zend_class_entry *phalcon_mvc_model_metadata_ce;
zend_class_entry *phalcon_mvc_model_message_ce;
zend_class_entry *phalcon_mvc_model_manager_ce;
zend_class_entry *phalcon_mvc_model_metadata_memory_ce;
zend_class_entry *phalcon_mvc_model_metadata_files_ce;
zend_class_entry *phalcon_mvc_model_metadata_apc_ce;
zend_class_entry *phalcon_mvc_model_metadata_session_ce;
zend_class_entry *phalcon_mvc_model_resultset_ce;
zend_class_entry *phalcon_mvc_model_transaction_ce;
zend_class_entry *phalcon_mvc_user_plugin_ce;
zend_class_entry *phalcon_mvc_user_module_ce;
zend_class_entry *phalcon_mvc_user_component_ce;
zend_class_entry *phalcon_mvc_application_ce;
zend_class_entry *phalcon_config_exception_ce;
zend_class_entry *phalcon_config_adapter_ini_ce;
zend_class_entry *phalcon_exception_ce;
zend_class_entry *phalcon_db_ce;
zend_class_entry *phalcon_logger_ce;
zend_class_entry *phalcon_cache_exception_ce;
zend_class_entry *phalcon_cache_frontend_base64_ce;
zend_class_entry *phalcon_cache_frontend_output_ce;
zend_class_entry *phalcon_cache_frontend_none_ce;
zend_class_entry *phalcon_cache_frontend_data_ce;
zend_class_entry *phalcon_cache_backend_ce;
zend_class_entry *phalcon_cache_backend_mongo_ce;
zend_class_entry *phalcon_cache_backend_memcache_ce;
zend_class_entry *phalcon_cache_backend_apc_ce;
zend_class_entry *phalcon_cache_backend_file_ce;
zend_class_entry *phalcon_acl_exception_ce;
zend_class_entry *phalcon_acl_adapter_memory_ce;
zend_class_entry *phalcon_acl_role_ce;
zend_class_entry *phalcon_acl_resource_ce;
zend_class_entry *phalcon_paginator_exception_ce;
zend_class_entry *phalcon_paginator_adapter_model_ce;
zend_class_entry *phalcon_paginator_adapter_nativearray_ce;
zend_class_entry *phalcon_tag_exception_ce;
zend_class_entry *phalcon_tag_select_ce;
zend_class_entry *phalcon_filter_exception_ce;
zend_class_entry *phalcon_flash_direct_ce;
zend_class_entry *phalcon_flash_exception_ce;
zend_class_entry *phalcon_flash_session_ce;
zend_class_entry *phalcon_escaper_exception_ce;
zend_class_entry *phalcon_dispatcher_ce;
zend_class_entry *phalcon_translate_ce;
zend_class_entry *phalcon_db_profiler_ce;
zend_class_entry *phalcon_db_exception_ce;
zend_class_entry *phalcon_db_reference_ce;
zend_class_entry *phalcon_db_dialect_ce;
zend_class_entry *phalcon_db_adapter_pdo_mysql_ce;
zend_class_entry *phalcon_db_adapter_pdo_postgresql_ce;
zend_class_entry *phalcon_db_adapter_pdo_sqlite_ce;
zend_class_entry *phalcon_db_adapter_pdo_ce;
zend_class_entry *phalcon_db_profiler_item_ce;
zend_class_entry *phalcon_db_rawvalue_ce;
zend_class_entry *phalcon_db_column_ce;
zend_class_entry *phalcon_db_index_ce;
zend_class_entry *phalcon_db_result_pdo_ce;
zend_class_entry *phalcon_db_dialect_mysql_ce;
zend_class_entry *phalcon_db_dialect_postgresql_ce;
zend_class_entry *phalcon_db_dialect_sqlite_ce;
zend_class_entry *phalcon_tag_ce;
zend_class_entry *phalcon_http_cookie_ce;
zend_class_entry *phalcon_http_request_exception_ce;
zend_class_entry *phalcon_http_request_file_ce;
zend_class_entry *phalcon_http_response_exception_ce;
zend_class_entry *phalcon_http_response_headers_ce;
zend_class_entry *phalcon_http_response_ce;
zend_class_entry *phalcon_http_request_ce;
zend_class_entry *phalcon_session_ce;
zend_class_entry *phalcon_version_ce;
zend_class_entry *phalcon_flash_ce;
zend_class_entry *phalcon_config_ce;
zend_class_entry *phalcon_filter_ce;
zend_class_entry *phalcon_di_factorydefault_cli_ce;
zend_class_entry *phalcon_di_exception_ce;
zend_class_entry *phalcon_di_injectable_ce;
zend_class_entry *phalcon_di_injectionawareinterface_ce;
zend_class_entry *phalcon_di_factorydefault_ce;
zend_class_entry *phalcon_events_event_ce;
zend_class_entry *phalcon_events_exception_ce;
zend_class_entry *phalcon_events_manager_ce;
zend_class_entry *phalcon_acl_ce;
zend_class_entry *phalcon_translate_exception_ce;
zend_class_entry *phalcon_translate_adapter_nativearray_ce;
zend_class_entry *phalcon_escaper_ce;
zend_class_entry *phalcon_cli_task_ce;
zend_class_entry *phalcon_cli_router_exception_ce;
zend_class_entry *phalcon_cli_router_ce;
zend_class_entry *phalcon_cli_dispatcher_exception_ce;
zend_class_entry *phalcon_cli_console_ce;
zend_class_entry *phalcon_cli_dispatcher_ce;
zend_class_entry *phalcon_cli_console_exception_ce;
zend_class_entry *phalcon_logger_exception_ce;
zend_class_entry *phalcon_logger_adapter_file_ce;
zend_class_entry *phalcon_logger_item_ce;
zend_class_entry *phalcon_loader_exception_ce;

ZEND_DECLARE_MODULE_GLOBALS(phalcon)

PHP_MINIT_FUNCTION(phalcon){


	if(!zend_ce_serializable){
		fprintf(stderr, "Phalcon Error: Interface Serializable was not found");
		return FAILURE;
	}
	if(!zend_ce_iterator){
		fprintf(stderr, "Phalcon Error: Interface Iterator was not found");
		return FAILURE;
	}
	if(!spl_ce_SeekableIterator){
		fprintf(stderr, "Phalcon Error: Interface SeekableIterator was not found");
		return FAILURE;
	}
	if(!spl_ce_Countable){
		fprintf(stderr, "Phalcon Error: Interface Countable was not found");
		return FAILURE;
	}
	if(!zend_ce_arrayaccess){
		fprintf(stderr, "Phalcon Error: Interface ArrayAccess was not found");
		return FAILURE;
	}

	/** Init globals */
	ZEND_INIT_MODULE_GLOBALS(phalcon, php_phalcon_init_globals, NULL);

	PHALCON_INIT(Phalcon_Session_Bag);
	PHALCON_INIT(Phalcon_Loader);
	PHALCON_INIT(Phalcon_DI);
	PHALCON_INIT(Phalcon_Text);
	PHALCON_INIT(Phalcon_Mvc_Router_Route);
	PHALCON_INIT(Phalcon_Mvc_Router);
	PHALCON_INIT(Phalcon_Mvc_Collection_Manager);
	PHALCON_INIT(Phalcon_Mvc_Collection);
	PHALCON_INIT(Phalcon_Mvc_View_Engine_Volt_Compiler);
	PHALCON_INIT(Phalcon_Mvc_Url);
	PHALCON_INIT(Phalcon_Mvc_Model);
	PHALCON_INIT(Phalcon_Mvc_Model_Query);
	PHALCON_INIT(Phalcon_Mvc_Model_Query_Status);
	PHALCON_INIT(Phalcon_Mvc_Model_Query_Lang);
	PHALCON_INIT(Phalcon_Mvc_Model_Criteria);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator);
	PHALCON_INIT(Phalcon_Mvc_Model_Row);
	PHALCON_INIT(Phalcon_Mvc_Model_Transaction_Manager);
	PHALCON_INIT(Phalcon_Mvc_Model_MetaData);
	PHALCON_INIT(Phalcon_Mvc_Model_Message);
	PHALCON_INIT(Phalcon_Mvc_Model_Manager);
	PHALCON_INIT(Phalcon_Mvc_Model_Resultset);
	PHALCON_INIT(Phalcon_Mvc_Model_Transaction);
	PHALCON_INIT(Phalcon_Db);
	PHALCON_INIT(Phalcon_Logger);
	PHALCON_INIT(Phalcon_Cache_Frontend_Base64);
	PHALCON_INIT(Phalcon_Cache_Frontend_Output);
	PHALCON_INIT(Phalcon_Cache_Frontend_None);
	PHALCON_INIT(Phalcon_Cache_Frontend_Data);
	PHALCON_INIT(Phalcon_Cache_Backend);
	PHALCON_INIT(Phalcon_Acl_Role);
	PHALCON_INIT(Phalcon_Acl_Resource);
	PHALCON_INIT(Phalcon_Paginator_Adapter_Model);
	PHALCON_INIT(Phalcon_Paginator_Adapter_NativeArray);
	PHALCON_INIT(Phalcon_Tag_Select);
	PHALCON_INIT(Phalcon_Dispatcher);
	PHALCON_INIT(Phalcon_Translate);
	PHALCON_INIT(Phalcon_Db_Profiler);
	PHALCON_INIT(Phalcon_Db_Reference);
	PHALCON_INIT(Phalcon_Db_Dialect);
	PHALCON_INIT(Phalcon_Db_Profiler_Item);
	PHALCON_INIT(Phalcon_Db_RawValue);
	PHALCON_INIT(Phalcon_Db_Column);
	PHALCON_INIT(Phalcon_Db_Index);
	PHALCON_INIT(Phalcon_Db_Result_Pdo);
	PHALCON_INIT(Phalcon_Tag);
	PHALCON_INIT(Phalcon_Http_Cookie);
	PHALCON_INIT(Phalcon_Http_Request_File);
	PHALCON_INIT(Phalcon_Http_Response_Headers);
	PHALCON_INIT(Phalcon_Http_Response);
	PHALCON_INIT(Phalcon_Http_Request);
	PHALCON_INIT(Phalcon_Session);
	PHALCON_INIT(Phalcon_Version);
	PHALCON_INIT(Phalcon_Flash);
	PHALCON_INIT(Phalcon_Config);
	PHALCON_INIT(Phalcon_Filter);
	PHALCON_INIT(Phalcon_DI_Injectable);
	PHALCON_INIT(Phalcon_DI_InjectionAwareInterface);
	PHALCON_INIT(Phalcon_Events_Event);
	PHALCON_INIT(Phalcon_Events_Manager);
	PHALCON_INIT(Phalcon_Acl);
	PHALCON_INIT(Phalcon_Escaper);
	PHALCON_INIT(Phalcon_CLI_Router);
	PHALCON_INIT(Phalcon_CLI_Console);
	PHALCON_INIT(Phalcon_Logger_Item);
	PHALCON_INIT(Phalcon_Exception);
	PHALCON_INIT(Phalcon_Mvc_View_Engine);
	PHALCON_INIT(Phalcon_Mvc_Model_Exception);
	PHALCON_INIT(Phalcon_Db_Adapter_Pdo);
	PHALCON_INIT(Phalcon_DI_FactoryDefault);
	PHALCON_INIT(Phalcon_Session_Exception);
	PHALCON_INIT(Phalcon_Session_Adapter_Files);
	PHALCON_INIT(Phalcon_Mvc_Router_Exception);
	PHALCON_INIT(Phalcon_Mvc_Micro);
	PHALCON_INIT(Phalcon_Mvc_Dispatcher_Exception);
	PHALCON_INIT(Phalcon_Mvc_Collection_Exception);
	PHALCON_INIT(Phalcon_Mvc_View);
	PHALCON_INIT(Phalcon_Mvc_View_Exception);
	PHALCON_INIT(Phalcon_Mvc_View_Engine_Php);
	PHALCON_INIT(Phalcon_Mvc_View_Engine_Volt);
	PHALCON_INIT(Phalcon_Mvc_Controller);
	PHALCON_INIT(Phalcon_Mvc_Application_Exception);
	PHALCON_INIT(Phalcon_Mvc_Url_Exception);
	PHALCON_INIT(Phalcon_Mvc_Dispatcher);
	PHALCON_INIT(Phalcon_Mvc_Micro_Exception);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_Uniqueness);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_PresenceOf);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_Exclusionin);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_Regex);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_Inclusionin);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_StringLength);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_Numericality);
	PHALCON_INIT(Phalcon_Mvc_Model_Validator_Email);
	PHALCON_INIT(Phalcon_Mvc_Model_Resultset_Complex);
	PHALCON_INIT(Phalcon_Mvc_Model_Resultset_Simple);
	PHALCON_INIT(Phalcon_Mvc_Model_Transaction_Exception);
	PHALCON_INIT(Phalcon_Mvc_Model_Transaction_Failed);
	PHALCON_INIT(Phalcon_Mvc_Model_MetaData_Memory);
	PHALCON_INIT(Phalcon_Mvc_Model_MetaData_Files);
	PHALCON_INIT(Phalcon_Mvc_Model_MetaData_Apc);
	PHALCON_INIT(Phalcon_Mvc_Model_MetaData_Session);
	PHALCON_INIT(Phalcon_Mvc_User_Plugin);
	PHALCON_INIT(Phalcon_Mvc_User_Module);
	PHALCON_INIT(Phalcon_Mvc_User_Component);
	PHALCON_INIT(Phalcon_Mvc_Application);
	PHALCON_INIT(Phalcon_Config_Exception);
	PHALCON_INIT(Phalcon_Config_Adapter_Ini);
	PHALCON_INIT(Phalcon_Cache_Exception);
	PHALCON_INIT(Phalcon_Cache_Backend_Mongo);
	PHALCON_INIT(Phalcon_Cache_Backend_Memcache);
	PHALCON_INIT(Phalcon_Cache_Backend_Apc);
	PHALCON_INIT(Phalcon_Cache_Backend_File);
	PHALCON_INIT(Phalcon_Acl_Exception);
	PHALCON_INIT(Phalcon_Acl_Adapter_Memory);
	PHALCON_INIT(Phalcon_Paginator_Exception);
	PHALCON_INIT(Phalcon_Tag_Exception);
	PHALCON_INIT(Phalcon_Filter_Exception);
	PHALCON_INIT(Phalcon_Flash_Direct);
	PHALCON_INIT(Phalcon_Flash_Exception);
	PHALCON_INIT(Phalcon_Flash_Session);
	PHALCON_INIT(Phalcon_Escaper_Exception);
	PHALCON_INIT(Phalcon_Db_Exception);
	PHALCON_INIT(Phalcon_Db_Adapter_Pdo_Mysql);
	PHALCON_INIT(Phalcon_Db_Adapter_Pdo_Postgresql);
	PHALCON_INIT(Phalcon_Db_Adapter_Pdo_Sqlite);
	PHALCON_INIT(Phalcon_Db_Dialect_Mysql);
	PHALCON_INIT(Phalcon_Db_Dialect_Postgresql);
	PHALCON_INIT(Phalcon_Db_Dialect_Sqlite);
	PHALCON_INIT(Phalcon_Http_Request_Exception);
	PHALCON_INIT(Phalcon_Http_Response_Exception);
	PHALCON_INIT(Phalcon_DI_FactoryDefault_CLI);
	PHALCON_INIT(Phalcon_DI_Exception);
	PHALCON_INIT(Phalcon_Events_Exception);
	PHALCON_INIT(Phalcon_Translate_Exception);
	PHALCON_INIT(Phalcon_Translate_Adapter_NativeArray);
	PHALCON_INIT(Phalcon_CLI_Task);
	PHALCON_INIT(Phalcon_CLI_Router_Exception);
	PHALCON_INIT(Phalcon_CLI_Dispatcher_Exception);
	PHALCON_INIT(Phalcon_CLI_Dispatcher);
	PHALCON_INIT(Phalcon_CLI_Console_Exception);
	PHALCON_INIT(Phalcon_Logger_Exception);
	PHALCON_INIT(Phalcon_Logger_Adapter_File);
	PHALCON_INIT(Phalcon_Loader_Exception);

	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(phalcon){
	if (PHALCON_GLOBAL(active_memory) != NULL) {
		phalcon_clean_shutdown_stack(TSRMLS_C);
	}
	return SUCCESS;
}

PHP_RINIT_FUNCTION(phalcon){
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(phalcon){
	if (PHALCON_GLOBAL(active_memory) != NULL) {
		phalcon_clean_shutdown_stack(TSRMLS_C);
	}
	return SUCCESS;
}

zend_module_entry phalcon_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_PHALCON_EXTNAME,
	NULL,
	PHP_MINIT(phalcon),
	PHP_MSHUTDOWN(phalcon),
	PHP_RINIT(phalcon),
	PHP_RSHUTDOWN(phalcon),
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_PHALCON_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHALCON
ZEND_GET_MODULE(phalcon)
#endif

