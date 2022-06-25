/************************************************************************
 * This file is part of the AREG SDK core engine.
 * AREG SDK is dual-licensed under Free open source (Apache version 2.0
 * License) and Commercial (with various pricing models) licenses, depending
 * on the nature of the project (commercial, research, academic or free).
 * You should have received a copy of the AREG SDK license description in LICENSE.txt.
 * If not, please contact to info[at]aregtech.com
 *
 * \copyright   (c) 2017-2021 Aregtech UG. All rights reserved.
 * \file        areg/base/private/Process.cpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit
 * \author      Artak Avetyan
 * \brief       The class to handle process. Get process ID, process handle, process name, etc.
 *              OS indipendant implementation
 ************************************************************************/
#include "areg/base/Process.hpp"

#include "areg/base/File.hpp"

//////////////////////////////////////////////////////////////////////////
// Process class implementation
//////////////////////////////////////////////////////////////////////////

Process Process::_theProcess;

Process::Process( void )
    : mProcEnv          ( static_cast<Process::eProcEnv>(sizeof(id_type)) )
    , mProcessId        ( Process::UNKNOWN_PROCESS )
    , mProcessHandle    ( nullptr )
    , mAppName          ( )
    , mProcessName      ( )
    , mProcessExt       ( )
    , mProcessPath      ( )
    , mProcessFullPath  ( )
    , mIsInitialized    ( false )
{
}

void Process::_initPaths( const char * fullPath )
{
    mProcessFullPath= fullPath;


    NEString::CharPos pos = mProcessFullPath.findLast(File::PATH_SEPARATOR);
    if (mProcessFullPath.isValidPosition(pos))
    {
        mProcessFullPath.substring(mProcessPath, NEString::START_POS, static_cast<NEString::CharCount>(pos));
        mProcessFullPath.substring(mProcessName, pos + 1, NEString::END_POS);
        mAppName       = mProcessName;     // initial value
    }

    pos = mProcessName.findLast(File::EXTENSION_SEPARATOR);
    if ( mProcessName.isValidPosition(pos) )
    {
        mProcessName.substring(mAppName, NEString::START_POS, static_cast<NEString::CharCount>(pos));
        mProcessName.substring(mProcessExt, pos + 1, NEString::END_POS);
    }
}
