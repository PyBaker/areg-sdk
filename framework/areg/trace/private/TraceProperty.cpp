/************************************************************************
 * \file        areg/trace/private/TraceProperty.cpp
 * \ingroup     AREG Asynchronous Event-Driven Communication Framework
 * \author      Artak Avetyan
 * \brief       AREG Platform, Trace Property value class. Used when reading or 
 *              saving configuration file
 ************************************************************************/
#include "areg/trace/private/TraceProperty.hpp"

#include "areg/trace/private/NELogConfig.hpp"
#include "areg/base/File.hpp"
#include "areg/base/NEUtilities.hpp"

TraceProperty::TraceProperty( const char * Key, const char * Value )
    : mProperty ( )
    , mComment  ( )
{
    mProperty.mValue.first  = Key;
    mProperty.mValue.second = Value;
}

TraceProperty::TraceProperty( const char * Key, unsigned int Value )
    : mProperty ( )
    , mComment  ( )
{
    mProperty.mValue.first  = Key;
    mProperty.mValue.second = Value;
}

TraceProperty::TraceProperty( const char * Key, NETrace::eLogPriority Value )
    : mProperty ( )
    , mComment  ( )
{
    mProperty.mValue.first  = Key;
    mProperty.mValue.second = Value;
}

TraceProperty::TraceProperty( const char * Key, bool Value )
    : mProperty ( )
    , mComment  ( )
{
    mProperty.mValue.first  = Key;
    mProperty.mValue.second = Value;
}

TraceProperty::TraceProperty( const TraceProperty & source )
    : mProperty ( source.mProperty )
    , mComment  ( source.mComment )
{
}

TraceProperty::TraceProperty( TraceProperty && source ) noexcept
    : mProperty ( std::move(source.mProperty) )
    , mComment  ( std::move(source.mComment) )
{
}

TraceProperty & TraceProperty::operator = ( const TraceProperty & source )
{
    mProperty   = source.mProperty;
    mComment    = source.mComment;

    return (*this);
}

TraceProperty & TraceProperty::operator = ( TraceProperty && source ) noexcept
{
    mProperty   = std::move(source.mProperty);
    mComment    = std::move( source.mComment);

    return (*this);
}

void TraceProperty::setData( const char * Key, const char * Value )
{
    mProperty.mValue.first  = Key;
    mProperty.mValue.second = Value;
}

void TraceProperty::setData(const char * Key, const char * Value, const char * Comment )
{
    mProperty.mValue.first  = Key;
    mProperty.mValue.second = Value;
    mComment                = Comment;
}

bool TraceProperty::readProperty( const File & fileConfig )
{
    clearProperty();
    if ( fileConfig.isOpened() )
    {
        String line;
        while ( fileConfig.readLine(line) > 0 && parseProperty(line) == false )
            ;
    }
    return isValid();
}

void TraceProperty::clearProperty( bool clearComment /* = true */ )
{
    mProperty.mValue.first  = String::EmptyString.data();
    mProperty.mValue.second = String::EmptyString.data();
    if ( clearComment )
        mComment = String::EmptyString.data();
}

bool TraceProperty::parseProperty( const char * logSetting )
{
    bool result = false;
    if ( NEString::isEmpty<char>(logSetting) == false )
    {
        String setting(logSetting);
        result = parseProperty(setting);
    }

    return result;
}

bool TraceProperty::parseProperty( String & line)
{
    NEString::CharPos posComment  = line.findFirst(NELogConfig::SYNTAX_COMMENT);
    bool isValidPos = false;
    if (line.isValidPosition(posComment))
    {
        isValidPos = true;
        line.substring(mComment, posComment);
        mComment   += NELogConfig::SYNTAX_LINEEND;
        
        line.substring(0, posComment);
    }

    NEString::CharPos posEqual    = line.findFirst(NELogConfig::SYNTAX_EQUAL);
    if ( line.isValidPosition(posEqual) && ((isValidPos == false) || (posEqual < posComment))  )
    {
        String temp;

        line.substring(temp, NEString::START_POS, posEqual);
        mProperty.mValue.first = temp.getString();

        line.substring(temp, posEqual + 1, isValidPos ? posComment - posEqual : NEString::END_POS);
        mProperty.mValue.second = temp.getString();
    }
    return isValid();
}

bool TraceProperty::operator == ( const TraceProperty & other ) const
{
    return mProperty.mValue.first == other.mProperty.mValue.first;
}
