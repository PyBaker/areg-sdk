/************************************************************************
 * This file is part of the AREG SDK core engine.
 * AREG SDK is dual-licensed under Free open source (Apache version 2.0
 * License) and Commercial (with various pricing models) licenses, depending
 * on the nature of the project (commercial, research, academic or free).
 * You should have received a copy of the AREG SDK license description in LICENSE.txt.
 * If not, please contact to info[at]aregtech.com
 *
 * \copyright   (c) 2017-2021 Aregtech UG. All rights reserved.
 * \file        areg/persist/private/Property.cpp
 * \ingroup     AREG Asynchronous Event-Driven Communication Framework
 * \author      Artak Avetyan
 * \brief       Property object for persisting data
 ************************************************************************/
#include "areg/persist/Property.hpp"
#include "areg/persist/private/NEPersistence.hpp"
#include "areg/base/NEUtilities.hpp"

#include <utility>

Property::Property(const char * keySet, const char * valueSet, const char * comment /*= nullptr */)
    : mComment  ( comment != nullptr ? comment : "")
    , mProperty ( PropertyKey(keySet), PropertyValue(valueSet) )
{
}

Property::Property(const Property::Entry & newProperty, const char * comment /*= nullptr */)
    : mComment  ( comment != nullptr ? comment : "")
    , mProperty ( newProperty )
{
}

Property::Property(const Property & source)
    : mComment  ( source.mComment )
    , mProperty ( source.mProperty )
{
}

Property::Property( Property && source ) noexcept
    : mComment  ( std::move(source.mComment) )
    , mProperty ( std::move(source.mProperty) )
{
}

Property & Property::operator = ( const Property & source )
{
    mComment    = source.mComment;
    mProperty   = source.mProperty;

    return (*this);
}

Property & Property::operator = ( Property && source ) noexcept
{
    mComment    = std::move(source.mComment);
    mProperty   = std::move(source.mProperty);

    return (*this);
}

bool Property::operator == ( const Property & other ) const
{
    return (this != &other ? mProperty == other.mProperty : true);
}

bool Property::operator != (const Property & other) const
{
    return (this != &other ? mProperty != other.mProperty : false);
}

Property::operator unsigned int ( void ) const
{
    return static_cast<unsigned int>(mProperty.mValue.first);
}

void Property::parseKey(const char * keySet)
{
    mProperty.mValue.first.parseKey(keySet);
}

void Property::setKey(const PropertyKey & Key)
{
    mProperty.mValue.first = Key;
}

void Property::setKey( PropertyKey && Key )
{
    mProperty.mValue.first = static_cast<PropertyKey &&>(Key);
}

const PropertyKey & Property::getKey(void) const
{
    return mProperty.mValue.first;
}

String Property::getKeyString(void) const
{
    return mProperty.mValue.first.convToString();
}

void Property::parseValue(const char * valueSet)
{
    mProperty.mValue.second.parseValue(valueSet);
}

void Property::setValue(const PropertyValue & Value)
{
    mProperty.mValue.second = Value;
}

void Property::setValue( PropertyValue && Value )
{
    mProperty.mValue.second = static_cast<PropertyValue &&>(Value);
}

const PropertyValue & Property::getValue(void) const
{
    return mProperty.mValue.second;
}

String Property::getValueString(void) const
{
    return mProperty.mValue.second.getString();
}

void Property::setComment(const char * comment)
{
    mComment = comment;
}

void Property::addComment(const char * comment)
{
    if ( mComment.isEmpty() == false )
    {
        mComment.append( NEPersistence::SYNTAX_LINEEND.data( ), static_cast<int>(NEPersistence::SYNTAX_LINEEND.length( )) );
    }

    String temp(comment);
    // if does not begin with "# "
    if ( (temp.isEmpty() == false) && (temp.compare(NEPersistence::SYNTAX_COMMENT.data()) != NEMath::eCompare::Equal) )
    {
        mComment.append( NEPersistence::SYNTAX_COMMENT.data(), static_cast<int>(NEPersistence::SYNTAX_COMMENT.length()) );
    }

    mComment.append(temp.getString(), temp.getLength());
}

const char * Property::getComment(void) const
{
    return mComment.getString();
}

void Property::setPropertyPair(const Property::Entry & newPair)
{
    mProperty = newPair;
}

void Property::setPropertyPair( Property::Entry && newPair )
{
    mProperty = static_cast<Property::Entry &&>(newPair);
}

const Property::Entry & Property::getPropertyPair(void) const
{
    return mProperty;
}

bool Property::isValid(void) const
{
    return mProperty.mValue.first.isValid();
}

bool Property::parseProperty(const char * strProperties)
{
    if ( NEString::isEmpty<char>(strProperties) == false )
    {
        String values         = strProperties != nullptr ? strProperties : "";
        NEString::CharPos pos = values.findFirst(NEPersistence::SYNTAX_COMMENT.data());

        if (values.isValidPosition(pos))
        {
            addComment( strProperties + static_cast<int>(pos));
            values.substring(0, pos);
        }

        if ( values.isEmpty() == false )
        {
            const char * value  = nullptr;
            String key          = String::getSubstring(values.getString(), NEPersistence::SYNTAX_EQUAL.data(), &value);

            mProperty.mValue.first.parseKey(key);
            mProperty.mValue.second.parseValue(value);
        }

        if ( mProperty.mValue.first.isValid() == false )
        {
            mProperty.mValue.first.resetKey();
            mProperty.mValue.second.resetValue();
        }
    }
    else
    {
        addComment("");
    }

    return isValid();
}

String Property::convToString(void) const
{
    String result = "";
    String key     = mProperty.mValue.first.convToString();
    String value   = mProperty.mValue.second.convToString();
    if ( !key.isEmpty() && !value.isEmpty() )
    {
        key += NEPersistence::SYNTAX_WHITESPACE_DELIMITER;
        key += NEPersistence::SYNTAX_EQUAL.data();
        key += NEPersistence::SYNTAX_WHITESPACE_DELIMITER;
        key += value;
    }

    if ( mComment.isEmpty() == false )
    {
        if (mComment.isValidPosition(mComment.findFirst(NEPersistence::SYNTAX_LINEEND.data())) || (mComment.getLength() >= 64))
        {
            result += mComment;
            result += NEPersistence::SYNTAX_LINEEND.data();
            result += key;
        }
    }
    else if ( mComment.isEmpty() == false )
    {
        result += key;
        result += NEPersistence::SYNTAX_WHITESPACE_DELIMITER;
        result += mComment;
    }
    else
    {
        result = key;
    }

    return result;
}

void Property::resetData(void)
{
    mProperty.mValue.first.resetKey();
    mProperty.mValue.second.resetValue();
    mComment.clear();
}
