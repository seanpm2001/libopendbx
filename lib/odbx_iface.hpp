/*
 *  OpenDBX - A simple but extensible database abstraction layer
 *  Copyright (C) 2004-2008 Norbert Sendetzky and others
 *
 *  Distributed under the terms of the GNU Library General Public Licence
 * version 2 or (at your option) any later version.
 */



#include "lib/opendbx/api"
#include <string>
#include <vector>



#ifndef ODBX_IFACE_HPP
#define ODBX_IFACE_HPP



namespace OpenDBX
{

	class Lob_Iface
	{
	public:

		virtual ~Lob_Iface() throw( std::exception ) {}
		virtual void close() throw( std::exception ) = 0;

		virtual ssize_t read( void* buffer, size_t buflen ) throw( std::exception ) = 0;
		virtual ssize_t write( void* buffer, size_t buflen ) throw( std::exception ) = 0;
	};



	class Result_Iface
	{
	public:

		virtual ~Result_Iface() throw( std::exception ) {}
		virtual void finish() throw( std::exception ) = 0;

		virtual odbxres getResult( struct timeval* timeout, unsigned long chunk ) throw( std::exception ) = 0;

		virtual odbxrow getRow() throw( std::exception ) = 0;
		virtual uint64_t rowsAffected() throw( std::exception ) = 0;

		virtual unsigned long columnCount() throw( std::exception ) = 0;
		virtual unsigned long columnPos( const string& name ) throw( std::exception ) = 0;
		virtual const string columnName( unsigned long pos ) throw( std::exception ) = 0;
		virtual odbxtype columnType( unsigned long pos ) throw( std::exception ) = 0;

		virtual unsigned long fieldLength( unsigned long pos ) throw( std::exception ) = 0;
		virtual const char* fieldValue( unsigned long pos ) throw( std::exception ) = 0;

		virtual Lob_Iface* getLob( const char* value ) throw( std::exception ) = 0;
	};



	class Stmt_Iface
	{
	public:

		virtual ~Stmt_Iface() throw() {};
		virtual Result_Iface* execute() throw( std::exception ) = 0;

// 		virtual void bind( const void* data, unsigned long size, size_t pos, int flags ) = 0;
// 		virtual size_t count() = 0;
	};



	class Conn_Iface
	{
	public:

		virtual ~Conn_Iface() throw() {};
		virtual void finish() throw( std::exception ) = 0;

		virtual void bind( const char* database, const char* who, const char* cred, odbxbind method = ODBX_BIND_SIMPLE ) throw( std::exception ) = 0;
		virtual void unbind() throw( std::exception ) = 0;

		virtual bool getCapability( odbxcap cap ) throw( std::exception ) = 0;

		virtual void getOption( odbxopt option, void* value ) throw( std::exception ) = 0;
		virtual void setOption( odbxopt option, void* value ) throw( std::exception ) = 0;

		virtual string& escape( const char* from, unsigned long fromlen, string& to ) throw( std::exception ) = 0;

		virtual Stmt_Iface* create( const string& sql, Stmt::Type type ) throw( std::exception ) = 0;
	};

}   // namespace



#endif
