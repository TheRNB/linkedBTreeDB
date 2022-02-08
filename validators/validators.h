#ifndef _VALIDATORS_
#define _VALIDATORS_

#include <string>
#include <sstream>
#include <stdexcept>
#include "../utils/hashUtils.h"
#include <iostream>

bool validator_int(std::string);

bool validator_date(std::string);

bool validator_string(std::string);

void validator_inputField (std::string, Type);


//CREATE TABLE {table name} ( column1 type , column2 type , ... )
bool validator_command_create (std::string);

//INSERT INTO {table name} VALUES ( field1 , field2 , ... )
bool validator_command_insert (std::string);

//DELETE FROM {table name} WHERE {cond i tion}
bool validator_command_delete (std::string);

//UPDATE {table name} SET ( "Hamid" , 2022/8/7 , 50000 ) WHERE {cond i tion}
bool validator_command_update (std::string);

//SELECT {( column1 , column2 , ... ) or *} FROM {table name} WHERE cond i tion
bool validator_command_select (std::string);

void validator_command (std::string);

#endif
