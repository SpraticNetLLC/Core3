/*
 *	server/zone/ZoneProcessServer.cpp generated by engine3 IDL compiler 0.60
 */

#include "ZoneProcessServer.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/ZonePacketHandler.h"

#include "server/chat/ChatManager.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/zone/managers/name/NameManager.h"

#include "server/zone/managers/sui/SuiManager.h"

#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/managers/professions/ProfessionManager.h"

#include "server/zone/managers/object/ObjectManager.h"

/*
 *	ZoneProcessServerStub
 */

ZoneProcessServer::ZoneProcessServer(ZoneServer* server) : ManagedService(DummyConstructorParameter::instance()) {
	ZoneProcessServerImplementation* _implementation = new ZoneProcessServerImplementation(server);
	_impl = _implementation;
	_impl->_setStub(this);
}

ZoneProcessServer::ZoneProcessServer(DummyConstructorParameter* param) : ManagedService(param) {
}

ZoneProcessServer::~ZoneProcessServer() {
}


void ZoneProcessServer::initialize() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		method.executeWithVoidReturn();
	} else
		_implementation->initialize();
}

ZoneServer* ZoneProcessServer::getZoneServer() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);

		return (ZoneServer*) method.executeWithObjectReturn();
	} else
		return _implementation->getZoneServer();
}

ZonePacketHandler* ZoneProcessServer::getPacketHandler() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getPacketHandler();
}

ProfessionManager* ZoneProcessServer::getProfessionManager() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getProfessionManager();
}

ObjectController* ZoneProcessServer::getObjectController() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getObjectController();
}

PlayerManager* ZoneProcessServer::getPlayerManager() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 8);

		return (PlayerManager*) method.executeWithObjectReturn();
	} else
		return _implementation->getPlayerManager();
}

NameManager* ZoneProcessServer::getNameManager() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getNameManager();
}

ChatManager* ZoneProcessServer::getChatManager() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 9);

		return (ChatManager*) method.executeWithObjectReturn();
	} else
		return _implementation->getChatManager();
}

SuiManager* ZoneProcessServer::getSuiManager() {
	ZoneProcessServerImplementation* _implementation = (ZoneProcessServerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getSuiManager();
}

DistributedObjectServant* ZoneProcessServer::_getImplementation() {
	return _impl;}

void ZoneProcessServer::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;}

/*
 *	ZoneProcessServerImplementation
 */

ZoneProcessServerImplementation::ZoneProcessServerImplementation(DummyConstructorParameter* param) : ManagedServiceImplementation(param) {
	_initializeImplementation();
}


ZoneProcessServerImplementation::~ZoneProcessServerImplementation() {
	ZoneProcessServerImplementation::finalize();
}


void ZoneProcessServerImplementation::_initializeImplementation() {
	_setClassHelper(ZoneProcessServerHelper::instance());

	_serializationHelperMethod();
}

void ZoneProcessServerImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (ZoneProcessServer*) stub;
	ManagedServiceImplementation::_setStub(stub);
}

DistributedObjectStub* ZoneProcessServerImplementation::_getStub() {
	return _this;
}

ZoneProcessServerImplementation::operator const ZoneProcessServer*() {
	return _this;
}

void ZoneProcessServerImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void ZoneProcessServerImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void ZoneProcessServerImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void ZoneProcessServerImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void ZoneProcessServerImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void ZoneProcessServerImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void ZoneProcessServerImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void ZoneProcessServerImplementation::_serializationHelperMethod() {
	ManagedServiceImplementation::_serializationHelperMethod();

	_setClassName("ZoneProcessServer");

}

ZoneServer* ZoneProcessServerImplementation::getZoneServer() {
	// server/zone/ZoneProcessServer.idl(92):  		return zoneServer;
	return zoneServer;
}

ZonePacketHandler* ZoneProcessServerImplementation::getPacketHandler() {
	// server/zone/ZoneProcessServer.idl(97):  		return zonePacketHandler;
	return zonePacketHandler;
}

ProfessionManager* ZoneProcessServerImplementation::getProfessionManager() {
	// server/zone/ZoneProcessServer.idl(102):  		return professionManager;
	return professionManager;
}

ObjectController* ZoneProcessServerImplementation::getObjectController() {
	// server/zone/ZoneProcessServer.idl(107):  		return objectController;
	return objectController;
}

PlayerManager* ZoneProcessServerImplementation::getPlayerManager() {
	// server/zone/ZoneProcessServer.idl(111):  		return zoneServer.getPlayerManager();
	return zoneServer->getPlayerManager();
}

NameManager* ZoneProcessServerImplementation::getNameManager() {
	// server/zone/ZoneProcessServer.idl(116):  		return nameManager;
	return nameManager;
}

ChatManager* ZoneProcessServerImplementation::getChatManager() {
	// server/zone/ZoneProcessServer.idl(120):  		return zoneServer.getChatManager();
	return zoneServer->getChatManager();
}

SuiManager* ZoneProcessServerImplementation::getSuiManager() {
	// server/zone/ZoneProcessServer.idl(125):  		return suiManager;
	return suiManager;
}

/*
 *	ZoneProcessServerAdapter
 */

ZoneProcessServerAdapter::ZoneProcessServerAdapter(ZoneProcessServerImplementation* obj) : ManagedServiceAdapter(obj) {
}

Packet* ZoneProcessServerAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case 6:
		initialize();
		break;
	case 7:
		finalize();
		break;
	case 8:
		resp->insertLong(getZoneServer()->_getObjectID());
		break;
	case 9:
		resp->insertLong(getPlayerManager()->_getObjectID());
		break;
	case 10:
		resp->insertLong(getChatManager()->_getObjectID());
		break;
	default:
		return NULL;
	}

	return resp;
}

void ZoneProcessServerAdapter::initialize() {
	((ZoneProcessServerImplementation*) impl)->initialize();
}

void ZoneProcessServerAdapter::finalize() {
	((ZoneProcessServerImplementation*) impl)->finalize();
}

ZoneServer* ZoneProcessServerAdapter::getZoneServer() {
	return ((ZoneProcessServerImplementation*) impl)->getZoneServer();
}

PlayerManager* ZoneProcessServerAdapter::getPlayerManager() {
	return ((ZoneProcessServerImplementation*) impl)->getPlayerManager();
}

ChatManager* ZoneProcessServerAdapter::getChatManager() {
	return ((ZoneProcessServerImplementation*) impl)->getChatManager();
}

/*
 *	ZoneProcessServerHelper
 */

ZoneProcessServerHelper* ZoneProcessServerHelper::staticInitializer = ZoneProcessServerHelper::instance();

ZoneProcessServerHelper::ZoneProcessServerHelper() {
	className = "ZoneProcessServer";

	DistributedObjectBroker::instance()->registerClass(className, this);
}

void ZoneProcessServerHelper::finalizeHelper() {
	ZoneProcessServerHelper::finalize();
}

DistributedObject* ZoneProcessServerHelper::instantiateObject() {
	return new ZoneProcessServer(DummyConstructorParameter::instance());
}

DistributedObjectServant* ZoneProcessServerHelper::instantiateServant() {
	return new ZoneProcessServerImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ZoneProcessServerHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ZoneProcessServerAdapter((ZoneProcessServerImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

