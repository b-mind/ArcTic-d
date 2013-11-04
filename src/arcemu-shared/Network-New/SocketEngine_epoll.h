/*
 * Arc MMORPG Server
 * Copyright (C) 2005-2010 Arc Team <http://www.arcemulator.net/>
 *
 * This software is  under the terms of the EULA License
 * All title, including but not limited to copyrights, in and to the ArcNG Software
 * and any copies there of are owned by ZEDCLANS INC. or its suppliers. All title
 * and intellectual property rights in and to the content which may be accessed through
 * use of the ArcNG is the property of the respective content owner and may be protected
 * by applicable copyright or other intellectual property laws and treaties. This EULA grants
 * you no rights to use such content. All rights not expressly granted are reserved by ZEDCLANS INC.
 *
 */

#ifndef _NETLIB_SOCKETENGINE_EPOLL_H
#define _NETLIB_SOCKETENGINE_EPOLL_H

#ifdef NETLIB_EPOLL

/** This is the maximum number of connections you will be able to hold at one time.
 * adjust it accordingly.
 */
#define MAX_DESCRIPTORS 1024

class epollEngine : public SocketEngine
{
	/** Created epoll file descriptor
	 */
	int epoll_fd;

	/** Thread running or not?
	 */
	bool m_running;

	/** Binding for fd -> pointer
	 */
	BaseSocket * fds[MAX_DESCRIPTORS];

public:
	epollEngine();
	~epollEngine();

	/** Adds a socket to the engine.
	 */
	void AddSocket(BaseSocket * s);

	/** Removes a socket from the engine. It should not receive any more events.
	 */
	void RemoveSocket(BaseSocket * s);

	/** This is called when a socket has data to write for the first time.
	 */
	void WantWrite(BaseSocket * s);

	/** Spawn however many worker threads this engine requires
	 */
	void SpawnThreads();

	/** Called by SocketWorkerThread, this is the network loop.
	 */
	void MessageLoop();
	
	/** Shutdown the socket engine, disconnect any associated sockets and 
	 * deletes itself and the socket deleter.
	 */
	void Shutdown();
};

/** Returns the socket engine
 */
inline void CreateSocketEngine() { new epollEngine; }

#endif		// NETLIB_EPOLL
#endif		// _NETLIB_SOCKETENGINE_EPOLL_H