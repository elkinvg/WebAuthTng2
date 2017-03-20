/*----- PROTECTED REGION ID(WebAuthTng2.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        WebAuthTng2.cpp
//
// description : C++ source for the WebAuthTng2 class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               WebAuthTng2 are implemented in this file.
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <WebAuthTng2.h>
#include <WebAuthTng2Class.h>

/*----- PROTECTED REGION END -----*/	//	WebAuthTng2.cpp

/**
 *  WebAuthTng2 class description:
 *    Device server to provide basic web authorization and check access permissions.
 *    (MySQL database needed).
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name         |  Method name
//================================================================
//  State                |  Inherited (no method)
//  Status               |  Inherited (no method)
//  On                   |  on
//  Off                  |  off
//  check_permissions    |  check_permissions
//  check_user           |  check_user
//  Send_log_command_ex  |  send_log_command_ex
//  check_user_ident     |  check_user_ident
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace WebAuthTng2_ns
{
/*----- PROTECTED REGION ID(WebAuthTng2::namespace_starting) ENABLED START -----*/

//    static initializations

/*----- PROTECTED REGION END -----*/	//	WebAuthTng2::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::WebAuthTng2()
 *	Description : Constructors for a Tango device
 *                implementing the classWebAuthTng2
 */
//--------------------------------------------------------
WebAuthTng2::WebAuthTng2(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(WebAuthTng2::constructor_1) ENABLED START -----*/
    init_device();

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::constructor_1
}
//--------------------------------------------------------
WebAuthTng2::WebAuthTng2(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(WebAuthTng2::constructor_2) ENABLED START -----*/
    init_device();

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::constructor_2
}
//--------------------------------------------------------
WebAuthTng2::WebAuthTng2(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(WebAuthTng2::constructor_3) ENABLED START -----*/
    init_device();

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void WebAuthTng2::delete_device()
{
	DEBUG_STREAM << "WebAuthTng2::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::delete_device) ENABLED START -----*/

    //    Delete device allocated objects

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void WebAuthTng2::init_device()
{
	DEBUG_STREAM << "WebAuthTng2::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::init_device_before) ENABLED START -----*/

    //    Initialization before get_device_property() call

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	/*----- PROTECTED REGION ID(WebAuthTng2::init_device) ENABLED START -----*/
#ifdef USEDDB
    initDbUserPass();
#endif

    try
    {
        MysqlConnect();
        MysqlPing();
        set_state(Tango::ON);
        set_status("TangoAuthServer is ON");
    }
    catch (MySQLError &err)
    {
        set_state(Tango::FAULT);
        set_status(err.errorMessage);
    }

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::init_device
}

//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void WebAuthTng2::get_device_property()
{
	/*----- PROTECTED REGION ID(WebAuthTng2::get_device_property_before) ENABLED START -----*/

    //    Initialize property data members

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("MailAgentDevice"));
	dev_prop.push_back(Tango::DbDatum("dbhost"));
	dev_prop.push_back(Tango::DbDatum("dbname"));
	dev_prop.push_back(Tango::DbDatum("dbuser"));
	dev_prop.push_back(Tango::DbDatum("dbpass"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on WebAuthTng2Class to get class property
		Tango::DbDatum	def_prop, cl_prop;
		WebAuthTng2Class	*ds_class =
			(static_cast<WebAuthTng2Class *>(get_device_class()));
		int	i = -1;

		//	Try to initialize MailAgentDevice from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  mailAgentDevice;
		else {
			//	Try to initialize MailAgentDevice from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  mailAgentDevice;
		}
		//	And try to extract MailAgentDevice value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  mailAgentDevice;

		//	Try to initialize dbhost from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  dbhost;
		else {
			//	Try to initialize dbhost from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  dbhost;
		}
		//	And try to extract dbhost value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  dbhost;

		//	Try to initialize dbname from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  dbname;
		else {
			//	Try to initialize dbname from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  dbname;
		}
		//	And try to extract dbname value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  dbname;

		//	Try to initialize dbuser from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  dbuser;
		else {
			//	Try to initialize dbuser from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  dbuser;
		}
		//	And try to extract dbuser value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  dbuser;

		//	Try to initialize dbpass from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  dbpass;
		else {
			//	Try to initialize dbpass from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  dbpass;
		}
		//	And try to extract dbpass value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  dbpass;

	}

	/*----- PROTECTED REGION ID(WebAuthTng2::get_device_property_after) ENABLED START -----*/

    //    Check device property data members init

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void WebAuthTng2::always_executed_hook()
{
	DEBUG_STREAM << "WebAuthTng2::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::always_executed_hook) ENABLED START -----*/

    //    code always executed before all requests

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void WebAuthTng2::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "WebAuthTng2::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::read_attr_hardware) ENABLED START -----*/

    //    Add your own code

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void WebAuthTng2::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(WebAuthTng2::add_dynamic_attributes) ENABLED START -----*/

    //    Add your own code to create and add dynamic attributes if any

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command On related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void WebAuthTng2::on()
{
	DEBUG_STREAM << "WebAuthTng2::On()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::on) ENABLED START -----*/

    set_state(Tango::ON);
    set_status("Device is ON");

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::on
}
//--------------------------------------------------------
/**
 *	Command Off related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void WebAuthTng2::off()
{
	DEBUG_STREAM << "WebAuthTng2::Off()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::off) ENABLED START -----*/

    set_state(Tango::OFF);
    set_status("Device is OFF");

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::off
}
//--------------------------------------------------------
/**
 *	Command check_permissions related method
 *	Description: Checks opened session for given IP and PID, determines username and checks its access permissions.
 *
 *	@param argin Strings;
 *               argin[0]:device;
 *               argin[1]:cmd;
 *               argin[2]:IP;
 *               argin[3]:login;
 *	@returns true if user can execute command or write attribute, false otherwise
 */
//--------------------------------------------------------
Tango::DevBoolean WebAuthTng2::check_permissions(const Tango::DevVarStringArray *argin)
{
	Tango::DevBoolean argout;
	DEBUG_STREAM << "WebAuthTng2::check_permissions()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::check_permissions) ENABLED START -----*/

    argout = false;
    if (argin->length() > 3)
    {
        std::string device=CORBA::string_dup((*argin)[0]);
        std::string cmd=CORBA::string_dup((*argin)[1]);
        std::string ip=CORBA::string_dup((*argin)[2]);
        std::string login=CORBA::string_dup((*argin)[3]);

        MYSQL_RES *res;
        MYSQL_ROW row;
        try
        {
            MysqlPing();
            std::stringstream ss;
            ss << "select username, priority from access_rights where username='" << login << "' and '" << device << "/" << cmd << "' REGEXP device_name and '" << ip << "' REGEXP ip ORDER by priority;";
            mysql_query(connection, ss.str().c_str());
            CheckError();

            // Getting a result table handler
            res = mysql_store_result(connection);
            CheckError();

            // How many rows are in the answer
            int num = mysql_num_rows(res);
            CheckError();

            if (num > 0)
            {
                argout = true;
            }

            mysql_free_result(res);
        }
        catch (MySQLError &err)
        {
            set_state(Tango::FAULT);
            set_status(err.errorMessage);
        }
    }
    DEBUG_STREAM << "check_permissions status is " << std::boolalpha << argout << endl;
    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::check_permissions
	return argout;
}
//--------------------------------------------------------
/**
 *	Command check_user related method
 *	Description: 
 *
 *	@param argin Strings;
 *               argin[0]:login;
 *               argin[1]:password;
 *	@returns true if user was authorised
 */
//--------------------------------------------------------
Tango::DevBoolean WebAuthTng2::check_user(const Tango::DevVarStringArray *argin)
{
	Tango::DevBoolean argout;
	DEBUG_STREAM << "WebAuthTng2::check_user()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::check_user) ENABLED START -----*/
    argout = false;
    if (argin->length() > 1)
    {
        std::string login=CORBA::string_dup((*argin)[0]);
        std::string password=CORBA::string_dup((*argin)[1]);
        MYSQL_RES *res;
        MYSQL_ROW row;
        try
        {
            MysqlPing();
            std::stringstream ss;
            ss << "select login from person where login='" << login << "' and password = MD5('" << password << "') limit 1;";
            mysql_query(connection, ss.str().c_str());
            CheckError();

            // Getting a result table handler
            res = mysql_store_result(connection);
            CheckError();

            // How many rows are in the answer
            int num = mysql_num_rows(res);
            CheckError();

            if (num > 0)
            {
                argout = true;
            }

            mysql_free_result(res);
        }
        catch (MySQLError &err)
        {
            set_state(Tango::FAULT);
            set_status(err.errorMessage);
        }
    }
    DEBUG_STREAM << "check_user status is " << std::boolalpha << argout << endl;

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::check_user
	return argout;
}
//--------------------------------------------------------
/**
 *	Command Send_log_command_ex related method
 *	Description: Send log to DB about command execute
 *
 *	@param argin Strings:
 *               [0] datetime in UNIX_TIMESTAMP formate
 *               [1] username
 *               [2] device_name
 *               [3] ip
 *               [4] command
 *               [5] command in json
 *               [6] access status
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevBoolean WebAuthTng2::send_log_command_ex(const Tango::DevVarStringArray *argin)
{
	Tango::DevBoolean argout;
	DEBUG_STREAM << "WebAuthTng2::Send_log_command_ex()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::send_log_command_ex) ENABLED START -----*/

    // argin[0] = timestamp_string UNIX_TIMESTAMP
    // argin[1] = login
    // argin[2] = deviceName
    // argin[3] = IP
    // argin[4] = commandName
    // argin[5] = commandJson
    // argin[6] = statusBool

    // for new version
    // argin[7] = isGroup

    // len == 7 Для старой версии
    // len == 8 Для старой версии

    unsigned long len = argin->length();
    //cout << "LENGTH " << argin->length();
    int numFields = getNumFields("command_history");
    DEBUG_STREAM << "Number of rows in command_history is " << numFields << endl;



    argout = false;
    if (len == 7 || len == 8)
    {
        try {
            std::stringstream query;
            std::stringstream values;
            for (int i = 0; i < len; i++)
            {
                if (i)
                    values << ",";
                if (i == 0) // FOR datetime
                    values << " FROM_UNIXTIME(";
                else
                    values << "\"";

                if (i!=5)
                    values << CORBA::string_dup((*argin)[i]);
                else {
                    //replace " -> \" in command_json
                    string tmp = CORBA::string_dup((*argin)[i]);
                    auto pos = tmp.find("\"");
                    while (pos != string::npos)
                        {
                            tmp.replace(pos, 1, "\\\"");
                            pos = tmp.find("\"",pos + 2);
                        }
                    values << tmp;
                }

                if (i == 0)
                    values << ")";
                else
                    values << "\"";
                // Для старой версии число полей 8 для новой 9
                // Если используется старая таблица, последняя итерация пропускается
                if (numFields==8 && len == 8 && i == 6)
                    break;
            }

            query << "INSERT INTO  command_history " << " VALUES(default," << values.str() << ")";
//            cout << "QUERY: " << query.str() << endl;

            mysql_query(connection, query.str().c_str());
            CheckError();
            argout =  true;
            DEBUG_STREAM << "query: " << query.str() << endl;
        }
        catch (MySQLError &err)
        {
            ERROR_STREAM << "MySQLError: " <<  err.errorMessage << endl;
            set_state(Tango::FAULT);
            set_status(err.errorMessage);
        }
    }

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::send_log_command_ex
	return argout;
}
//--------------------------------------------------------
/**
 *	Command check_user_ident related method
 *	Description: 
 *
 *	@param argin Strings:
 *               arg[0]: login // user login
 *               arg[1]: id_ri // id rand_identification
 *               arg[2]: rand_ident // rand_identification
 *               arg[3]: rand_ident_hash // hash of rand_identification
 */
//--------------------------------------------------------
void WebAuthTng2::check_user_ident(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "WebAuthTng2::check_user_ident()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(WebAuthTng2::check_user_ident) ENABLED START -----*/

    //    Add your own code
    if (argin->length() > 4) {
        std::string login=CORBA::string_dup((*argin)[0]);
        std::string id_ri=CORBA::string_dup((*argin)[1]);
        std::string rand_ident=CORBA::string_dup((*argin)[2]);
        std::string rand_ident_hash=CORBA::string_dup((*argin)[3]);
    }

    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::check_user_ident
}
//--------------------------------------------------------
/**
 *	Method      : WebAuthTng2::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void WebAuthTng2::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(WebAuthTng2::add_dynamic_commands) ENABLED START -----*/
    
    //    Add your own code to create and add dynamic commands if any
    
    /*----- PROTECTED REGION END -----*/	//	WebAuthTng2::add_dynamic_commands
}

/*----- PROTECTED REGION ID(WebAuthTng2::namespace_ending) ENABLED START -----*/

void WebAuthTng2::CheckError()
{
    const char* status = mysql_error(connection);
    if(status[0])
    {
        throw MySQLError(status);
    }
}

// if defined USEDDB dbuser and dbpass will redefine from DBUSER DBPASS
#ifdef USEDDB
void WebAuthTng2::initDbUserPass()
{
    stringstream ss;
    ss << DBUSER;
    dbuser = ss.str();
    ss.str(std::string());ss.clear();

    ss << DBPASS;
    dbpass = ss.str();
    ss.str(std::string());ss.clear();
}
#endif

void WebAuthTng2::MysqlConnect()
{
    connection = mysql_init(NULL);
    mysql_real_connect(connection, dbhost.c_str(), dbuser.c_str(), dbpass.c_str(), dbname.c_str(), 0, NULL, 0);
    bool b = true;
    my_bool bd = (my_bool)1;
    mysql_options(connection, MYSQL_OPT_RECONNECT, &bd);
    CheckError();
    mysql_query(connection, "SET NAMES 'utf8'");
    CheckError();
}

void WebAuthTng2::MysqlPing()
{
    int st = mysql_ping(connection);
    if (st != 0)
        throw MySQLError("MySQL Error");
}

int WebAuthTng2::getNumFields(string tableName)
{
    int numRows = 0;
    try {
        string forNumRows = "SELECT * FROM " + tableName + " order by id DESC LIMIT 1";
        mysql_query(connection, forNumRows.c_str());
        CheckError();

        // Getting a result table handler
        MYSQL_RES *res = mysql_store_result(connection);
        CheckError();

        //numRows = mysql_num_rows(res);
        numRows = mysql_num_fields(res);
        CheckError();
        mysql_free_result(res);
    }
    catch (MySQLError &err) {
        ERROR_STREAM << "MySQLError: " <<  err.errorMessage << endl;
        set_state(Tango::FAULT);
        set_status(err.errorMessage);
    }
    return numRows;
}

/*----- PROTECTED REGION END -----*/	//	WebAuthTng2::namespace_ending
} //	namespace
