#ifndef EVENT_SENDER_CC_TEMPLATE
#define EVENT_SENDER_CC_TEMPLATE
#include <iostream>
#include <assert.h>
/**
 \file
 Class template methods definition file.
 \copyright
 Copyright (C) 2002, 2003 Oliver Schoenborn

 This software is provided 'as-is', without
 any express or implied warranty. In no event
 will the authors be held liable for any
 damages arising from the use of this
 software.

 You can redistribute it and/or modify it
 under the terms found in the LICENSE file that
 is included in the library distribution.
 \endcopyright
 */

#include <algorithm>
#include "EventSender.hh"
#include "pasync.h"
#include "ptypes.h"

namespace
{
/// The various debug levels available
enum DEBUG_LEVELS
{
	NO_DEBUG = 1, DEBUG_VERBOSE = 2
};
/** The debug level for this file. The constant allows
 the optimizer to discard the debug info if not used. */
const DEBUG_LEVELS DEBUG_LEVEL = NO_DEBUG;
//const DEBUG_LEVELS DEBUG_LEVEL = DEBUG_VERBOSE;
}

/**
 Get the unique instance of event sender for this type of event.
 Putting it in a member function insures that the instance
 cannot be accessed via one of the static methods before it has
 been created. See C++FAQ book for example of technique.
 */
template<typename EvType>
EventSender<EvType>&
EventSender<EvType>::instance()
{
	static EventSender<EvType> eventSender;
	return eventSender;
}

/// Send the event to each listener in the registry.
template<typename EvType>
void EventSender<EvType>::sendEvent(const EvType& event)
{
	/*
	 If isBusySending == true, then problem: an attempt
	 is being made to send an EvType while one is already
	 being sent to listeners. Since the same listeners will be
	 called again with the new event, this could lead to an
	 infinite loop.
	 */
	if (_isBusySending)
		throw IllegalSendError();

	// nothing else to do if no listeners registered
	if (_registry.empty())
	{
		if (DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << "No " << lisnrID() << " registered." << std::endl;
		return;
	}

	_isBusySending = true;
	_eventIgnored = 0; // reset the event-ignored counter

	// Send event to each listener currently in registry
	typename Registry::iterator registryIter = _registry.begin();
	for (typename Registry::iterator registryIter = _registry.begin(); registryIter != _registry.end(); ++registryIter)
	{
		if (DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << "Calling " << lisnrID(*registryIter) << "::processEventPublic" << std::endl;

		try
		{
			(*registryIter)->jobs.post(new EvType(event));
//			std::cout<<"\nBefore start";
//			std::cout<<"";
//			(*registryIter)->start();
//			std::cout<<"\nafter start";
			//(*registryIter)->processEventPublic(event);
		} catch (const IllegalSendError&)
		{
			// propagate recursive flushes up the stack
			_isBusySending = false;
			cleanupQueues();
			throw ;
		}
		catch (const std::exception& e)
		{
			std::cerr
			<< "*** BUG Alert: " << lisnrID(*registryIter)
			<< "::processEvent()\n    threw an EXCEPTION of type "
			<< typeid(e).name()
			<< ".\n    The processEvent() must NOT leak ANY exception."
			<< "  Message is:\n" << e.what() << "\n\n";
		}
		catch (...)
		{
			std::cerr
			<< "*** BUG Alert: " << lisnrID(*registryIter)
			<< "::processEvent() threw an EXCEPTION"
			<< "\n    of UNKNOWN type (not derived from std::exception)."
			<< "\n    The processEvent() must NOT leak ANY exception."
			<< "\n\n";
		}
	}

	_isBusySending = false;
	// hold promise: the registration queue must
	// be empty when isBusySending is over
	cleanupQueues();
}

/** When the EventSender is destroyed, every registered
 listener must first be deregistered.
 */
template<typename EvType>
EventSender<EvType>::~EventSender()
{
	// doesn't make sense to have EventSender destroyed while sending
	// deregister every listener
	while (!_registry.empty())
	{
		_registry.front()->TListener::ignoreEvents();
	}
}

/** Move listeners queued for registration into the list
 of active listeners, and remove listeners that are in
 the removal queue from the registry.
 */
template<typename EvType>
void EventSender<EvType>::cleanupQueues()
{
	// register listeners that have been queued for registration
	while (!_registrationQueue.empty())
	{
		typename Registry::iterator registryIter = _registrationQueue.begin();
		if (DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << "Registering queued " << lisnrID(*registryIter) << std::endl;
		// splice node from registration queue to registry
		_registry.splice(_registry.end(), _registrationQueue, registryIter);
		// make sure no other copy left in queue
		assert(std::find(_registrationQueue.begin(), _registrationQueue.end(), _registry.back()) == _registrationQueue.end());
	}

	// remove listeners that have been queued for removal
	while (!_removalQueue.empty())
	{
		TListener* lisnr = _removalQueue.back();
		if (DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << "Removing queued " << lisnrID(lisnr) << std::endl;

		if (!removeFrom(_registry, lisnr) && DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << "Listener " << lisnrID(lisnr) << " not in registry, removal ignored" << std::endl;
		_removalQueue.pop_back();
	}
}

/** Remove \a lisnr from \a container. Return true if the
 listener has been removed, false if it wasn't found in the
 container.
 */
template<typename EvType>
bool EventSender<EvType>::removeFrom(Registry& container, TListener* lisnr)
{
	// Find iterator for listener to be removed
	typename Registry::iterator removeIter = std::find(container.begin(), container.end(), lisnr);
	if (removeIter != container.end())
	{
		container.erase(removeIter);
		if (DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << lisnrID(lisnr) << " removed from list" << std::endl;
		return true;
	}

	// listener not found anywhere
	if (DEBUG_LEVEL >= DEBUG_VERBOSE)
		std::cout << lisnrID(lisnr) << " NOT found in list" << std::endl;
	return false;
}

/** Remove a Listener from this EventSender's list of listeners.
 This should only be called by Listener if it is currently
 registered or queued for registration.
 \note
 - Actual removal takes place just before send() returns, just
 after all listeners have processed the event, since the list of
 listeners must not change during a send() operation.

 \pre \a lisnr is not null (not checked)
 \param lisnr the listener to remove from the registry
 */
template<typename EvType>
void EventSender<EvType>::removeListener(TListener* lisnr)
{
	if (_isBusySending)
	{
		if (!removeFrom(_registrationQueue, lisnr))
		{
			_removalQueue.push_back(lisnr);

			if (DEBUG_LEVEL >= DEBUG_VERBOSE)
				std::cout << "Putting " << lisnrID(lisnr) << " on removal queue" << std::endl;
		}
		else // nothing to do, already removed from registration queue
		{
			if (DEBUG_LEVEL >= DEBUG_VERBOSE)
				std::cout << lisnrID(lisnr) << " removed from registration queue" << std::endl;
		}
	}
	else
	{

		const bool removed = removeFrom(_registry, lisnr);

	}
}

/** Register a Listener with this EventSender. This should only be
 called by Listener if it is currently not registered or is
 queued for removal.
 \note
 - If this is called while a send() is in progress, actual
 registration takes place at the end of a send() operation,
 so that the registry of listeners will not change during the
 send().
 \pre \a lisnr is not null (not checked)
 \param lisnr the listener to add to the registry.
 */
template<typename EvType>
void EventSender<EvType>::registerListener(TListener* lisnr)
{
	if (_isBusySending)
	// use queues instead
	{
		// first see if it is on the removal queue
		if (!removeFrom(_removalQueue, lisnr))
		{
			// wasn't in removal queue, so put on registration queue
			// note that it shouldn't be possible to have listener
			// register itself if it is already in the queue or registered
			assert(std::find(_registrationQueue.begin(), _registrationQueue.end(), lisnr) == _registrationQueue.end());
			_registrationQueue.push_back(lisnr);
			if (DEBUG_LEVEL >= DEBUG_VERBOSE)
				std::cout << "Putting " << lisnrID(lisnr) << " on registration queue" << std::endl;
		}
		else // nothing to do, already in queue
		{
			if (DEBUG_LEVEL >= DEBUG_VERBOSE)
				std::cout << lisnrID(lisnr) << " removed from registration queue" << std::endl;
		}
	}
	else // safe to register immediately
	{
		// this method never called if already registerd, so assert this:
		assert(std::find(_registry.begin(), _registry.end(), lisnr) == _registry.end());

		_registry.push_back(lisnr);
		if (DEBUG_LEVEL >= DEBUG_VERBOSE)
			std::cout << "Added (immediate) " << lisnrID(lisnr) << " to listeners list" << std::endl;
	}
}

#endif // EVENT_SENDER_CC_TEMPLATE
