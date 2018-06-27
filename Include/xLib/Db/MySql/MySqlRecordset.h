/**
 * \file  MySql.h
 * \brief MySql client
 */


#pragma once

#include <mysql/mysql.h>

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Db/MySql/MySqlConnection.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, db)

class MySqlRecordset
    /// MySql recordset
{
public:
                 MySqlRecordset(MySqlConnection &connection, cbool_t isUseResult);
        ///< constructor
    virtual     ~MySqlRecordset();
        ///< destructor

    HandleMySqlResult &get() xWARN_UNUSED_RV;
        ///< get handle

    uint_t       fieldsNum() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    my_ulonglong rowsNum() const xWARN_UNUSED_RV;
        ///< number of rows in the result set
    void_t       fetchField(MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the current column
    void_t       fetchFieldDirect(cuint_t &fieldNumber, MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the specified column
    void_t       fetchFields(MYSQL_FIELD *field) const;
        ///< An array of MYSQL_FIELD structures for all columns of a result set
    void_t       fetchRow(std::vec_tstring_t *row) const;
        ///< fetching row

private:
    MySqlConnection  *_conn;
        ///< pointer to connection object
    HandleMySqlResult _result;
        ///< for private use

    void_t       _fetchLengths(ulong_t **fieldLengths) const;
        ///< An array of unsigned long_t integers representing the size of each column
    void_t       _fetchRow(MYSQL_ROW *row) const;
        ///< A MYSQL_ROW structure for the next row

    xNO_COPY_ASSIGN(MySqlRecordset)
};

xNAMESPACE_END2(xl, db)
//-------------------------------------------------------------------------------------------------

#if xTODO
    MYSQL_ROW row;
    unsigned long_t *lengths;
    unsigned int_t num_fields;
    unsigned int_t i;

    row = mysql_fetch_row(result);
    if (row)
    {
        num_fields = mysql_num_fields(result);
        lengths = mysql_fetch_lengths(result);
        for(i = 0; i < num_fields; i++)
        {
             printf("Column %u is %lu bytes in length.\n",         i, lengths[i]);
        }
    }
#endif


#if xTODO
    mysql_library_init()
    {
        mysql_init()

        mysql_options()

        mysql_real_connect()
        {
            //mysql_query()
            mysql_real_query()

            //Recordset
            {
                mysql_use_result()
                mysql_store_result()

                {
                    mysql_num_fields()
                    mysql_num_rows()

                    mysql_fetch_row    (pMySqlRes); //row
                    mysql_fetch_lengths(result);    //row length
                }

                mysql_free_result()
            }
        }
        mysql_close()
    }
    mysql_library_end()
#endif
