#ifndef TUNGUSSKA_CVAR_H
#define TUNGUSSKA_CVAR_H

#include <iostream> /*cout, cin*/
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <typeinfo> /*typeid*/
#include <sstream>
#include <stdlib.h> /*stof, stoa, stoi*/
#include <algorithm> /*std::transform*/
#include <cxxabi.h> /*abi*/

#include "Log.h"

extern std::map< std::string, std::vector< std::string > > cvars;

/**
 * Console variable usage guide
 * 
 * The variables should be created in any place.
 * Available types: int, float, double
 * Boolean type provides by INT (0 = false, 1 = true)
 *
 * Example:
 *     mCVar = new CVar();                                              init CVar instance (at once in scope)
 *     mCVar->registerVar<double>( "cvarDouble", 15.1, 1.01, "help" );  register new var
 *     mCVar->set<double>( "cvarDouble", 9.437 );                       set new value
 *     mCVar->reset( "cvarDouble" );                                    reset to default value
 *     mCVar->getVar<double>( "cvarDouble" );                                   get value
 *     mCVar->unregister( "cvarDouble" );                               remove var (not declared after)
 */

class CVar {

public:

    /**
     * Constructor
     */
    CVar() = default;
    
    /**
     * Destructor
     */
    ~CVar()
    {
        // cvars.clear();
    };

     /**
     * Register console variable
     * 
     * @param   name            The name of this command (must not be nullptr)
     * @param   defaultValue    Default value
     * @param   value           Current value
     * @param   help            Help text for this command
     */
    template< class T >
    T registerVar( const std::string& name, T defaultValue, T value, const std::string& help )
    {
        if( cvars.empty() ) cvars.emplace( "0", 0 );

        // find std::string
        std::size_t checkType = demangle( typeid( value ).name() ).find( "basic_string" );
        std::string flag;
        if (checkType!=std::string::npos) {
            flag = "STRING";
        } else {
            flag = str_toupper( demangle( typeid( value ).name() ) );
        }

        try
        {
            // set exception
            // passed and declared type are different
            if( typeid( T ).name() != typeid( value ).name() )
                throw std::invalid_argument( "var values are different type" );
            // var exist
            if( cvars.count( name ) > 0 )
                throw std::invalid_argument( "[" + name + "] already exists" );

            // save
            cvars.emplace( name, 0 );
            cvars.find( name )->second.resize( 4 );
            cvars.find( name )->second[ 0 ] = NumberToString( defaultValue );
            cvars.find( name )->second[ 1 ] = NumberToString( value );
            cvars.find( name )->second[ 2 ] = NumberToString( help );
            cvars.find( name )->second[ 3 ] = flag;
        }
        catch ( std::exception& e )
        {
            LOG_INFO << e.what();
        }
        catch ( ... )
        {
            LOG_INFO << "cvars error";
        }
        return value;
    }

    /**
     * Unregister console variable
     * 
     * @param   name    The name of var
     */
    void unregister( const std::string& name )
    {
        try
        {
             if ( cvars.count( name ) == 0 ) throw std::invalid_argument( "[" + name + "] not register" );
             cvars.erase( name );
        }
        catch ( std::exception& e )
        {
            LOG_ERROR << e.what();
        }
         catch ( ... )
        {
            LOG_INFO << "cvars error";
        }
    }

    /**
     * Get console variable
     * 
     * @param   name    The name of variable
     * @return  value   FLOAT, INT, DOUBLE
     */
    // TODO: segfault if T = std:string
    template <class T>
    T getVar( const std::string& name, bool error = true )
    {
        try
        {
            // set exception
            if ( cvars.count( name ) == 0) throw std::invalid_argument( "[" + name + "] not register" );
            std::string flag = str_toupper( cvars.find( name )->second[ 3 ] );
            std::string passedType = str_toupper( demangle( typeid( T ).name() ) );
            if( passedType != flag ) throw std::invalid_argument( "trying to take " + passedType + " but " + flag + " expected");

            // get
            std::string value = cvars.find( name )->second[ 1 ];
            std::string defValue = cvars.find( name )->second[ 0 ];
            // segfault if T = std:string
            // if( flag == "STRING" ) return value;
            if( flag == "FLOAT" ) return std::stof( value );
            if( flag == "INT" ) return std::stoi( value );
            if( flag == "DOUBLE" ) return std::stod( value );
        }
        catch ( std::exception& e )
        {
            if( error ) LOG_ERROR << e.what();
        }
         catch ( ... )
        {
            LOG_INFO << "cvars error";
        }

        return 0;
    }

    /**
     * Reset to default value
     * 
     * @param   name    The name of variable
     */
    void reset( const std::string& name )
    {
        try
        {
            if( cvars.count( name ) == 0 ) throw std::invalid_argument( "[" + name + "] not register" );

            std::string value = cvars.find( name )->second[ 1 ];
            std::string defaultValue = cvars.find( name )->second[ 0 ];
            value = NumberToString( defaultValue );
        }
        catch ( std::exception& e )
        {
            LOG_ERROR << e.what();
        }
        catch ( ... )
        {
            LOG_INFO << "cvars error";
        }
    }

    /**
     * Set new value
     * 
     * @param   name    The name of variable
     * @param   value   New value. INT, DOUBLE, FLOAT
     */
    template<class T>
    T set( const std::string& name, T newValue )
    {
        try
        {
            if( cvars.count( name ) == 0 ) throw std::invalid_argument( "[" + name + "] not register" );
            std::string flag = str_toupper( cvars.find( name )->second[ 3 ] );
            std::string passedType = str_toupper( demangle( typeid( T ).name() ) );
            if( passedType != flag ) throw std::invalid_argument( "trying to set " + passedType + " but " + flag + " expected");

            cvars.find( name )->second[ 1 ] = std::to_string( newValue );
        }
        catch( std::exception& e )
        {
            LOG_ERROR << e.what();
        }
        catch ( ... )
        {
            LOG_INFO << "cvars error";
        }

        return 0;
    }

    /**
     * Get variable help
     * 
     * @param   name    The name of variable
     * @return          help text
     */
    std::string help( const std::string& name )
    {
        try
        {
            if( cvars.count( name ) == 0 ) throw std::invalid_argument( "[" + name + "] not register" );
            return cvars.find( name )->second[ 2 ];
        }
         catch( std::exception& e )
        {
            LOG_ERROR << e.what();
        }
        catch ( ... )
        {
            LOG_INFO << "cvars undefined error";
        }

         return 0;
    }

private:

    // std::map< std::string, std::vector< std::string > > cvars;

    /**
     * Demangle types
     * 
     * @param   mangled      string to mangle
     * @return  std::string  mangled string
     */
    std::string demangle(const char* mangled)
    {
        int status;
        std::unique_ptr<char[], void (*)(void*)> result(
            abi::__cxa_demangle(mangled, 0, 0, &status), std::free);
        return result.get() ? std::string(result.get()) : "error occurred";
    }

    /**
     * Convert number to string
     * 
     * @param   Number          float, int, double
     * @return  std::string     Converted string
     */
    template <typename T>
    std::string NumberToString ( T Number )
    {
        std::ostringstream ss;
        ss << Number;
        return ss.str();
   }

    /**
     * Convert string to uppercase
     * 
     * @param   s   string
     * @return      upprecased string
     */
    std::string str_toupper(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::toupper(c); } // correct
                   );
        return s;
    }
};

#endif //TUNGUSSKA_CVAR_H