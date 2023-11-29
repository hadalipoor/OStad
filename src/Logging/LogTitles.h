#ifndef LOGTITLES_H
#define LOGTITLES_H

class LogTitles
{    
public:
    //Database
    static const String ADD_RECORD_TO_DB;
    static const String UPDATE_RECORD_IN_DB;
    static const String DELETE_RECORD_FROM_DB;
    static const String REMOVE_COLUMN_FROM_DB;
    static const String REMOVE_TABLE_FROM_DB;
    
    static const String ADD;
    static const String UPDATE;
    static const String DELETE;
    static const String GET;
    static const String REMOVE_COLUMN;
    static const String REMOVE_TABLE;
    
    //System
    static const String DB_CHANGE;
    static const String SYSTEM_BOOT;
    static const String SYSTEM_REBOOT;
    static const String _INFO_CHANGE;
    static const String SYSTEM_CLOCK;

    //Modules
    static const String BUTTON_LONG_PRESS;
    static const String BUTTON_CLICK;
    static const String RELAY_STATE_CHANGE;
    static const String MODULE_NOT_FOUND_IN_DB;
    static const String MODULE_ADDED_TO_DB;
    static const String MODULE_NOT_ADDED_TO_DB;
    
    //SIM800
    static const String SIM800_MESSAGE_RECIEVED;
//MODULE_NOT_FOUND_IN_DB 

    static const String USER_LOGS;

};

const String LogTitles::ADD_RECORD_TO_DB = "add_record_to_db";
const String LogTitles::UPDATE_RECORD_IN_DB = "update_record_in_db";
const String LogTitles::DELETE_RECORD_FROM_DB = "delete_record_from_db";
const String LogTitles::REMOVE_COLUMN_FROM_DB = "remove_column_from_db";
const String LogTitles::REMOVE_TABLE_FROM_DB = "remove_table_from_db";

const String LogTitles::ADD = "add";
const String LogTitles::UPDATE = "update";
const String LogTitles::DELETE = "delete";
const String LogTitles::GET = "get";
const String LogTitles::REMOVE_COLUMN = "remove_column";
const String LogTitles::REMOVE_TABLE = "remove_table";

const String LogTitles::DB_CHANGE = "db_change";
const String LogTitles::SYSTEM_BOOT = "system_boot";
const String LogTitles::SYSTEM_REBOOT = "system_reboot";
const String LogTitles::_INFO_CHANGE = "_info_save";
const String LogTitles::SYSTEM_CLOCK = "system_clock";
const String LogTitles::USER_LOGS = "user_logs";

const String LogTitles::BUTTON_LONG_PRESS = "button_long_press";
const String LogTitles::BUTTON_CLICK = "button_click";
const String LogTitles::RELAY_STATE_CHANGE = "relay_state_changed";
const String LogTitles::MODULE_NOT_FOUND_IN_DB = "module_not_found_in_db";
const String LogTitles::MODULE_ADDED_TO_DB = "module_added_to_db";
const String LogTitles::MODULE_NOT_ADDED_TO_DB = "module_not_added_to_db";

const String LogTitles::SIM800_MESSAGE_RECIEVED = "sim800_message_recieved";


#endif