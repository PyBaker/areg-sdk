/************************************************************************
 * This file is part of the AREG SDK core engine.
 * AREG SDK is dual-licensed under Free open source (Apache version 2.0
 * License) and Commercial (with various pricing models) licenses, depending
 * on the nature of the project (commercial, research, academic or free).
 * You should have received a copy of the AREG SDK license description in LICENSE.txt.
 * If not, please contact to info[at]aregtech.com
 *
 * \copyright   (c) 2017-2021 Aregtech UG. All rights reserved.
 * \file        areg/component/private/NERegistry.cpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit
 * \author      Artak Avetyan
 * \brief       AREG Platform, classes of NCRegistry namespace.
 *
 ************************************************************************/
#include "areg/component/NERegistry.hpp"
#include "areg/component/Component.hpp"
#include "areg/base/NEUtilities.hpp"
#include "areg/base/NECommon.hpp"

#include <utility>

//////////////////////////////////////////////////////////////////////////
// NERegistry namespace implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// NERegistry namespace Predefined constants
//////////////////////////////////////////////////////////////////////////

/**
 * \brief   Predefined invalid Service Entry.
 **/
AREG_API const NERegistry::ServiceEntry           NERegistry::INVALID_SERVICE_ENTRY;
/**
 * \brief   Predefined invalid Service List.
 **/
AREG_API const NERegistry::ServiceList            NERegistry::INVALID_SERVICE_LIST;
/**
 * \brief   Predefined invalid Worker Thread Entry.
 **/
AREG_API const NERegistry::WorkerThreadEntry      NERegistry::INVALID_WORKER_THREAD_ENTRY;
/**
 * \brief   Predefined invalid Worker Thread List.
 **/
AREG_API const NERegistry::WorkerThreadList       NERegistry::INVALID_WORKER_THREAD_LIST;
/**
 * \brief   Predefined invalid service dependency entry.
 **/
AREG_API const NERegistry::DependencyEntry        NERegistry::INVALID_DEPENDENCY_ENTRY;
/**
 * \brief   Predefined invalid service dependency entry.
 **/
AREG_API const NERegistry::DependencyList         NERegistry::INVALID_DEPENDENCY_LIST;
/**
 * \brief   Predefined Invalid Component Entry.
 **/
AREG_API const NERegistry::ComponentEntry         NERegistry::INVALID_COMPONENT_ENTRY;
/**
 * \brief   Predefined invalid Component List.
 **/
AREG_API const NERegistry::ComponentList          NERegistry::INVALID_COMPONENT_LIST;
/**
 * \brief   Predefined invalid Thread Entry.
 **/
AREG_API const NERegistry::ComponentThreadEntry   NERegistry::INVALID_THREAD_ENTRY;
/**
 * \brief   Predefined invalid Thread List.
 **/
AREG_API const NERegistry::ComponentThreadList    NERegistry::INVALID_THREAD_LIST;
/**
 * \brief   Predefined invalid Model.
 **/
AREG_API const NERegistry::Model                  NERegistry::INVALID_MODEL;

//////////////////////////////////////////////////////////////////////////
// class NERegistry::ServiceEntry implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::ServiceEntry::ServiceEntry( const char* serviceName, unsigned int major, unsigned int minor, unsigned int patch )
    : mName     ( serviceName )
    , mVersion  ( major, minor, patch )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( const std::string & serviceName, unsigned int major, unsigned int minor, unsigned int patch )
    : mName     ( serviceName )
    , mVersion  ( major, minor, patch )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( const std::string_view & serviceName, unsigned int major, unsigned int minor, unsigned int patch )
    : mName     ( serviceName )
    , mVersion  ( major, minor, patch )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( std::string && serviceName, unsigned int major, unsigned int minor, unsigned int patch )
    : mName     ( serviceName )
    , mVersion  ( major, minor, patch )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( const char* serviceName, const Version & version )
    : mName     (serviceName)
    , mVersion  (version)
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( const std::string & serviceName, const Version & version )
    : mName     ( serviceName )
    , mVersion  ( version )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( const std::string_view & serviceName, const Version & version )
    : mName     ( serviceName )
    , mVersion  ( version )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

NERegistry::ServiceEntry::ServiceEntry( std::string && serviceName, const Version & version )
    : mName     ( serviceName )
    , mVersion  ( version )
{
    ASSERT( mName.empty( ) == false );
    ASSERT( mVersion.isValid( ) );
}

bool NERegistry::ServiceEntry::operator == ( const NERegistry::ServiceEntry & other ) const
{
    return (this == &other) || ((mName == other.mName) && (mVersion == other.mVersion));
}

bool NERegistry::ServiceEntry::isValid( void ) const
{
    return ( (mName.empty() == false) && mVersion.isValid() );
}

const std::string & NERegistry::ServiceEntry::getName( void ) const
{
    return mName;
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::ServiceList implementation
//////////////////////////////////////////////////////////////////////////
NERegistry::ServiceList::ServiceList( const NERegistry::ServiceEntry & entry )
    : NERegistry::TEListBase<NERegistry::ServiceEntry>  ( )
{
    if ( entry.isValid() )
    {
        mList.push_back(entry);
    }
}

const NERegistry::ServiceEntry & NERegistry::ServiceList::getService( const std::string_view & serviceName ) const
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::getEntry(serviceName, NERegistry::INVALID_SERVICE_ENTRY );
}

int NERegistry::ServiceList::findService( const NERegistry::ServiceEntry & entry ) const
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::findEntry(entry);
}

int NERegistry::ServiceList::findService( const std::string_view & serviceName ) const
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::findEntry(serviceName);
}

int NERegistry::ServiceList::addService( const std::string_view & serviceName, const Version & version )
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::placeEntry( NERegistry::ServiceEntry(serviceName, version), true );
}

int NERegistry::ServiceList::addService( const NERegistry::ServiceEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::addEntry(entry, true);
}

bool NERegistry::ServiceList::removeService( const std::string_view & serviceName )
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::removeEntry(serviceName);
}

bool NERegistry::ServiceList::removeService( const NERegistry::ServiceEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::ServiceEntry>::removeEntry(entry);
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::WorkerThreadEntry implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::WorkerThreadEntry::WorkerThreadEntry( const char * masterThreadName, const char* workerThreadName, const char * compRoleName, const char* compConsumerName )
    : mThreadName   (NEUtilities::createComponentItemName(masterThreadName, workerThreadName))
    , mConsumerName (NEUtilities::createComponentItemName(compRoleName, compConsumerName))
{
}

NERegistry::WorkerThreadEntry::WorkerThreadEntry( const std::string_view & masterThreadName, const std::string_view & workerThreadName, const std::string_view & compRoleName, const std::string_view & compConsumerName )
    : mThreadName   ( NEUtilities::createComponentItemName( std::string(masterThreadName), std::string(workerThreadName) ) )
    , mConsumerName ( NEUtilities::createComponentItemName( std::string(compRoleName), std::string(compConsumerName) ) )
{
}

NERegistry::WorkerThreadEntry::WorkerThreadEntry( const std::string & masterThreadName, const std::string & workerThreadName, const std::string & compRoleName, const std::string & compConsumerName )
    : mThreadName   ( NEUtilities::createComponentItemName( masterThreadName, workerThreadName ) )
    , mConsumerName ( NEUtilities::createComponentItemName( compRoleName, compConsumerName ) )
{
}

bool NERegistry::WorkerThreadEntry::operator == ( const NERegistry::WorkerThreadEntry & other ) const
{
    return (this == &other) || ((mThreadName == other.mThreadName) && (mConsumerName == other.mConsumerName));
}

bool NERegistry::WorkerThreadEntry::isValid( void ) const
{
    return ( (mThreadName.empty() == false) && (mConsumerName.empty() == false) );
}

const std::string & NERegistry::WorkerThreadEntry::getName( void ) const
{
    return mThreadName;
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::WorkerThreadList implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::WorkerThreadList::WorkerThreadList( const NERegistry::WorkerThreadEntry & entry )
    : NERegistry::TEListBase<NERegistry::WorkerThreadEntry> ( )
{
    if ( entry.isValid() )
    {
        mList.push_back(entry);
    }
}

const NERegistry::WorkerThreadEntry & NERegistry::WorkerThreadList::getWorkerThread( const std::string_view & threadName ) const
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::getEntry(threadName, NERegistry::INVALID_WORKER_THREAD_ENTRY );
}

int NERegistry::WorkerThreadList::findThread( const std::string_view & threadName ) const
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::findEntry(threadName);
}

int NERegistry::WorkerThreadList::findThread( const NERegistry::WorkerThreadEntry & entry ) const
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::findEntry( entry );
}

int NERegistry::WorkerThreadList::addWorkerThread( const std::string_view & masterThreadName
                                                 , const std::string_view & workerThreadName
                                                 , const std::string_view & compRoleName
                                                 , const std::string_view & compConsumerName )
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::placeEntry( NERegistry::WorkerThreadEntry(masterThreadName, workerThreadName, compRoleName, compConsumerName));
}

int NERegistry::WorkerThreadList::addWorkerThread( const NERegistry::WorkerThreadEntry & workerThread )
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::addEntry(workerThread);
}

bool NERegistry::WorkerThreadList::removeWorkerThread( const std::string_view & workerThreadName )
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::removeEntry(workerThreadName);
}

bool NERegistry::WorkerThreadList::removeWorkerThread( const NERegistry::WorkerThreadEntry & workerThread )
{
    return NERegistry::TEListBase<NERegistry::WorkerThreadEntry>::removeEntry(workerThread);
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::DependencyEntry implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::DependencyEntry::DependencyEntry( const char* roleName )
    : mRoleName(roleName)
{
}

NERegistry::DependencyEntry::DependencyEntry( const std::string_view & roleName )
    : mRoleName(roleName)
{
}

NERegistry::DependencyEntry::DependencyEntry( const std::string & roleName )
    : mRoleName( roleName )
{
}

NERegistry::DependencyEntry::DependencyEntry( std::string && roleName )
    : mRoleName( roleName )
{
}

bool NERegistry::DependencyEntry::operator == ( const NERegistry::DependencyEntry & other ) const
{
    return (mRoleName == other.mRoleName);
}

bool NERegistry::DependencyEntry::isValid( void ) const
{
    return (mRoleName.empty() == false);
}

const std::string & NERegistry::DependencyEntry::getName( void ) const
{
    return mRoleName;
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::DependencyList implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::DependencyList::DependencyList( const NERegistry::DependencyEntry & entry  )
    : NERegistry::TEListBase<NERegistry::DependencyEntry>( )
{
    if ( entry.isValid())
    {
        mList.push_back(entry);
    }
}

const NERegistry::DependencyEntry & NERegistry::DependencyList::getDependency( const std::string_view & roleName ) const
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::getEntry(roleName, NERegistry::INVALID_DEPENDENCY_ENTRY );
}

int NERegistry::DependencyList::findDependency( const NERegistry::DependencyEntry & entry ) const
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::findEntry(entry);
}

int NERegistry::DependencyList::findDependency( const std::string_view & roleName ) const
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::findEntry(roleName);
}

int NERegistry::DependencyList::addDependency( const std::string_view & roleName )
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::addEntry( NERegistry::DependencyEntry(roleName), true );
}

int NERegistry::DependencyList::addDependency( const NERegistry::DependencyEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::addEntry(entry, true);
}

bool NERegistry::DependencyList::removeDependency( const std::string_view & roleName )
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::removeEntry(roleName);
}

bool NERegistry::DependencyList::removeDependency( const NERegistry::DependencyEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::DependencyEntry>::removeEntry(entry);
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::ComponentEntry implementation
//////////////////////////////////////////////////////////////////////////
NERegistry::ComponentEntry::ComponentEntry( void )
    : mRoleName             ( )

    , mThreadName           ( )
    , mFuncCreate           (nullptr)
    , mFuncDelete           (nullptr)

    , mSupportedServices    ( )
    , mWorkerThreads        ( )
    , mDependencyServices   ( )

    , mComponentData        ( NEMemory::InvalidElement )
{
}

NERegistry::ComponentEntry::ComponentEntry( const std::string_view & masterThreadName
                                          , const std::string_view & roleName
                                          , FuncCreateComponent funcCreate
                                          , FuncDeleteComponent funcDelete )
    : mRoleName             (roleName)

    , mThreadName           (masterThreadName != nullptr ? masterThreadName : "")
    , mFuncCreate           (funcCreate)
    , mFuncDelete           (funcDelete)

    , mSupportedServices    ( )
    , mWorkerThreads        ( )
    , mDependencyServices   ( )

    , mComponentData        ( NEMemory::InvalidElement )
{
}

NERegistry::ComponentEntry::ComponentEntry(   const std::string_view & masterThreadName
                                            , const std::string_view & roleName
                                            , FuncCreateComponent funcCreate
                                            , FuncDeleteComponent funcDelete
                                            , const NERegistry::ServiceList & serviceList
                                            , const NERegistry::DependencyList & dependencyList
                                            , const NERegistry::WorkerThreadList & workerList )
    : mRoleName             (roleName)

    , mThreadName           (masterThreadName)
    , mFuncCreate           (funcCreate)
    , mFuncDelete           (funcDelete)

    , mSupportedServices    (serviceList)
    , mWorkerThreads        (workerList)
    , mDependencyServices   (dependencyList)

    , mComponentData        ( NEMemory::InvalidElement )
{
}

NERegistry::ComponentEntry::ComponentEntry(   const std::string_view & masterThreadName
                                            , const std::string_view & roleName
                                            , FuncCreateComponent funcCreate
                                            , FuncDeleteComponent funcDelete
                                            , const NERegistry::ServiceEntry & service
                                            , const NERegistry::DependencyEntry & dependency
                                            , const NERegistry::WorkerThreadEntry & worker )
    : mRoleName             (roleName)

    , mThreadName           (masterThreadName)
    , mFuncCreate           (funcCreate)
    , mFuncDelete           (funcDelete)

    , mSupportedServices    (service)
    , mWorkerThreads        (worker)
    , mDependencyServices   (dependency)

    , mComponentData        ( NEMemory::InvalidElement )
{
}

bool NERegistry::ComponentEntry::operator == ( const NERegistry::ComponentEntry & other ) const
{
    return (this != &other ? (mRoleName == other.mRoleName) && (mThreadName == other.mThreadName) : true);
}

void NERegistry::ComponentEntry::addSupportedService( const NERegistry::ServiceEntry & entry )
{
    mSupportedServices.addService( entry );
}

void NERegistry::ComponentEntry::addSupportedService( const NERegistry::ServiceList & serviceList )
{
    for ( const auto & entry : serviceList.mList )
    {
        mSupportedServices.addService( entry );
    }
}

NERegistry::ServiceEntry & NERegistry::ComponentEntry::addSupportedService(const std::string_view & serviceName, const Version & version)
{
    int index = mSupportedServices.addService( serviceName, version );
    return mSupportedServices[index];
}

bool NERegistry::ComponentEntry::removeSupportedService( const std::string_view & serviceName )
{
    return mSupportedServices.removeService(serviceName);
}

int NERegistry::ComponentEntry::findSupportedService( const NERegistry::ServiceEntry& entry ) const
{
    return mSupportedServices.findService(entry);
}

int NERegistry::ComponentEntry::findSupportedService( const std::string_view & serviceName ) const
{
    return mSupportedServices.findService(serviceName);
}

void NERegistry::ComponentEntry::addWorkerThread( const NERegistry::WorkerThreadEntry& entry )
{
    mWorkerThreads.addWorkerThread(entry);
}

void NERegistry::ComponentEntry::addWorkerThread( const NERegistry::WorkerThreadList & workerList )
{
    for ( const auto & entry : workerList.mList )
    {
        mWorkerThreads.addWorkerThread( entry );
    }
}

int NERegistry::ComponentEntry::findWorkerThread( const NERegistry::WorkerThreadEntry& entry ) const
{
    return mWorkerThreads.findThread(entry);
}

int NERegistry::ComponentEntry::findWorkerThread( const std::string_view & workerName ) const
{
    return mWorkerThreads.findThread(workerName);
}

bool NERegistry::ComponentEntry::removeWorkerThread( const std::string_view & workerName )
{
    return mWorkerThreads.removeWorkerThread(workerName);
}

void NERegistry::ComponentEntry::addDependencyService( const NERegistry::DependencyEntry& entry )
{
    mDependencyServices.addDependency(entry);
}

void NERegistry::ComponentEntry::addDependencyService( const NERegistry::DependencyList & dependencyList )
{
    for ( const auto & entry : dependencyList.mList )
    {
        mDependencyServices.addDependency( entry );
    }
}

NERegistry::DependencyEntry & NERegistry::ComponentEntry::addDependencyService(const std::string_view & roleName)
{
    int index = mDependencyServices.addDependency(roleName);
    return mDependencyServices[index];
}

int NERegistry::ComponentEntry::findDependencyService( const NERegistry::DependencyEntry & entry ) const
{
    return mDependencyServices.findDependency(entry);
}

bool NERegistry::ComponentEntry::removeDependencyService( const std::string_view & roleName )
{
    return mDependencyServices.removeDependency(roleName);
}

int NERegistry::ComponentEntry::findDependencyService( const std::string_view & roleName ) const
{
    return mDependencyServices.findDependency(roleName);
}

const NERegistry::ServiceList & NERegistry::ComponentEntry::getSupportedServices( void ) const
{
    return mSupportedServices;
}

const NERegistry::WorkerThreadList & NERegistry::ComponentEntry::getWorkerThreads( void ) const
{
    return mWorkerThreads;
}

const NERegistry::DependencyList & NERegistry::ComponentEntry::getDependencyServices( void ) const
{
    return mDependencyServices;
}

void NERegistry::ComponentEntry::setInstanceMethods( FuncCreateComponent fnCreate, FuncDeleteComponent fnDelete )
{
    mFuncCreate = fnCreate;
    mFuncDelete = fnDelete;
}

bool NERegistry::ComponentEntry::isValid( void ) const
{
    return (mRoleName.empty() == false);
}

const std::string & NERegistry::ComponentEntry::getName( void ) const
{
    return mRoleName;
}

void NERegistry::ComponentEntry::setComponentData( NEMemory::uAlign compData )
{
    mComponentData  = compData;
}

NEMemory::uAlign NERegistry::ComponentEntry::getComponentData( void ) const
{
    return mComponentData;
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::ComponentList implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::ComponentList::ComponentList(  const NERegistry::ComponentEntry & entry )
    : NERegistry::TEListBase<NERegistry::ComponentEntry>( )
{
    if ( entry.isValid() )
    {
        mList.push_back(entry);
    }
}

const NERegistry::ComponentEntry & NERegistry::ComponentList::getComponent( const std::string_view & roleName ) const
{
    return NERegistry::TEListBase<NERegistry::ComponentEntry>::getEntry(roleName, NERegistry::INVALID_COMPONENT_ENTRY );
}

int NERegistry::ComponentList::findComponent(const std::string_view & roleName) const
{
    return NERegistry::TEListBase<NERegistry::ComponentEntry>::findEntry(roleName);
}

int NERegistry::ComponentList::findComponent( const NERegistry::ComponentEntry & entry ) const
{
    return NERegistry::TEListBase<NERegistry::ComponentEntry>::findEntry(entry);
}

bool NERegistry::ComponentList::setComponentData( const std::string_view & roleName, NEMemory::uAlign compData )
{
    int index = NERegistry::TEListBase<NERegistry::ComponentEntry>::findEntry(roleName);
    if ( index != NECommon::INVALID_INDEX )
    {
        mList[index].setComponentData(compData);
    }

    return (index != NECommon::INVALID_INDEX);
}

int NERegistry::ComponentList::addComponent( const NERegistry::ComponentEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::ComponentEntry>::addEntry(entry, true);
}

bool NERegistry::ComponentList::removeComponent( const std::string_view & roleName )
{
    return NERegistry::TEListBase<NERegistry::ComponentEntry>::removeEntry(roleName);
}

bool NERegistry::ComponentList::removeComponent( const NERegistry::ComponentEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::ComponentEntry>::removeEntry(entry);
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::ComponentThreadEntry implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::ComponentThreadEntry::ComponentThreadEntry( const std::string_view & threadName )
    : mThreadName   (threadName)
    , mComponents   ( )
{
}

NERegistry::ComponentThreadEntry::ComponentThreadEntry( const std::string_view & threadName, const NERegistry::ComponentList & supCompList )
    : mThreadName   (threadName)
    , mComponents   (supCompList)
{
}

bool NERegistry::ComponentThreadEntry::operator == ( const NERegistry::ComponentThreadEntry & other ) const
{
    return (this == &other) || (mThreadName == other.mThreadName);
}

void NERegistry::ComponentThreadEntry::addComponent( const NERegistry::ComponentEntry & entry )
{
    mComponents.addComponent(entry);
}

void NERegistry::ComponentThreadEntry::addComponent( const NERegistry::ComponentList & componentList )
{
    for ( const auto & entry : componentList.mList )
    {
        mComponents.addComponent( entry );
    }
}

NERegistry::ComponentEntry & NERegistry::ComponentThreadEntry::addComponent( const std::string_view & roleName
                                                                           , FuncCreateComponent funcCreate
                                                                           , FuncDeleteComponent funcDelete)
{
    int index = mComponents.addComponent( NERegistry::ComponentEntry(mThreadName, roleName, funcCreate, funcDelete) );
    return mComponents[index];
}

bool NERegistry::ComponentThreadEntry::removeComponent( const std::string_view & roleName )
{
    return mComponents.removeComponent(roleName);
}

int NERegistry::ComponentThreadEntry::findComponentEntry( const NERegistry::ComponentEntry & entry ) const
{
    return mComponents.findComponent(entry);
}

int NERegistry::ComponentThreadEntry::findComponentEntry( const std::string_view & roleName ) const
{
    return mComponents.findComponent(roleName);
}

bool NERegistry::ComponentThreadEntry::isValid( void ) const
{
    return ( (mThreadName.empty() == false) && mComponents.isValid() );
}

const std::string & NERegistry::ComponentThreadEntry::getName( void ) const
{
    return mThreadName;
}

bool NERegistry::ComponentThreadEntry::setComponentData( const std::string_view & roleName, NEMemory::uAlign compData )
{
    return mComponents.setComponentData(roleName, compData);
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::ComponentThreadList implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::ComponentThreadList::ComponentThreadList( const NERegistry::ComponentThreadEntry & entry )
    : NERegistry::TEListBase<NERegistry::ComponentThreadEntry>( )
{
    if ( entry.isValid() )
    {
        mList.push_back(entry);
    }
}

const NERegistry::ComponentThreadEntry & NERegistry::ComponentThreadList::getThread( const std::string_view & threadName ) const
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::getEntry( threadName, NERegistry::INVALID_THREAD_ENTRY );
}

int NERegistry::ComponentThreadList::findThread( const NERegistry::ComponentThreadEntry& entry ) const
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::findEntry( entry );
}

int NERegistry::ComponentThreadList::findThread( const std::string_view & threadName ) const
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::findEntry( threadName );
}

int NERegistry::ComponentThreadList::addThread( const NERegistry::ComponentThreadEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::addEntry( entry, true );
}

int NERegistry::ComponentThreadList::addThread( const std::string_view & threadName, const NERegistry::ComponentList & compList )
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::addEntry( NERegistry::ComponentThreadEntry(threadName, compList), true );
}

bool NERegistry::ComponentThreadList::removeThread( const std::string_view & threadName )
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::removeEntry( threadName );
}

bool NERegistry::ComponentThreadList::removeThread( const NERegistry::ComponentThreadEntry & entry )
{
    return NERegistry::TEListBase<NERegistry::ComponentThreadEntry>::removeEntry( entry );
}

//////////////////////////////////////////////////////////////////////////
// class NERegistry::Model implementation
//////////////////////////////////////////////////////////////////////////

NERegistry::Model::Model( void )
    : mModelName    ( )
    , mModelThreads ( )
    , mIsLoaded     ( false )
{
}

NERegistry::Model::Model( const std::string_view & modelName )
    : mModelName    (modelName)
    , mModelThreads ( )
    , mIsLoaded     ( false )
{
}

NERegistry::Model::Model( const std::string_view & modelName, const ComponentThreadList & threadList  )
    : mModelName    (modelName)
    , mModelThreads (threadList)
    , mIsLoaded     ( false )
{
}

bool NERegistry::Model::operator == ( const NERegistry::Model & other ) const
{
    return ((this == &other) || ((mModelName == other.mModelName) && (mModelThreads == other.mModelThreads)));
}

bool NERegistry::Model::isValid( void ) const
{
    return ( (mModelName.empty() == false) && mModelThreads.isValid() );
}

int NERegistry::Model::findThread( const NERegistry::ComponentThreadEntry& entry ) const
{
    return mModelThreads.findThread(entry);
}

int NERegistry::Model::findThread( const std::string_view & threadName ) const
{
    return mModelThreads.findThread(threadName);
}

void NERegistry::Model::addThread( const NERegistry::ComponentThreadEntry& entry )
{
    mModelThreads.addThread(entry);
}

void NERegistry::Model::addThread( const NERegistry::ComponentThreadList& threadList )
{
    for (int i = 0; i < threadList.getSize(); ++ i )
    {
        mModelThreads.addThread( threadList[i] );
    }
}

NERegistry::ComponentThreadEntry & NERegistry::Model::addThread(const std::string_view & threadName)
{
    int index = mModelThreads.addThread( NERegistry::ComponentThreadEntry( threadName ) );
    return mModelThreads[index];
}

bool NERegistry::Model::removeThread( const std::string_view & threadName )
{
    return mModelThreads.removeThread(threadName);
}

const std::string & NERegistry::Model::getModelName( void ) const
{
    return mModelName;
}

bool NERegistry::Model::hasRegisteredComponent( const NERegistry::ComponentEntry & entry ) const
{
    return hasRegisteredComponent(entry.getName());
}

bool NERegistry::Model::hasRegisteredComponent( const std::string_view & roleName ) const
{
    int result  = NECommon::INVALID_INDEX;
    int count   = mModelThreads.getSize( );

    for ( int i = 0; (result == NECommon::INVALID_INDEX) && (i < count); ++ i )
    {
        result = mModelThreads[i].findComponentEntry( roleName );
    }

    return (result >= 0);
}

bool NERegistry::Model::isModelLoaded( void ) const
{
    return mIsLoaded;
}

void NERegistry::Model::markModelLoaded( bool isLoaded /*= true */ )
{
    mIsLoaded = isLoaded;
}

const NERegistry::ComponentThreadList & NERegistry::Model::getThreadList( void ) const
{
    return mModelThreads;
}

bool NERegistry::Model::setComponentData( const std::string_view & roleName, NEMemory::uAlign compData )
{
    int result  = false;
    int count   = mModelThreads.getSize( );

    for ( int i = 0; (result == false) && (i < count); ++ i )
    {
        result = mModelThreads[i].setComponentData( roleName, compData );
    }

    return result;
}
