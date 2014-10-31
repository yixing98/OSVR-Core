/** @file
    @brief Header

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>
*/

// Copyright 2014 Sensics, Inc.
//
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

#ifndef INCLUDED_AsyncDeviceToken_h_GUID_654218B0_3900_4B89_E86F_D314EB6C0ABF
#define INCLUDED_AsyncDeviceToken_h_GUID_654218B0_3900_4B89_E86F_D314EB6C0ABF

// Internal Includes
#include <ogvr/PluginKit/DeviceToken.h>
#include <ogvr/PluginKit/DeviceInterfaceC.h>
#include <ogvr/Util/CallbackWrapper.h>

// Library/third-party includes
#include <boost/optional.hpp>

#ifdef TRY_WITH_THREADS
#include <boost/thread.hpp>
#endif

// Standard includes
// - none
namespace ogvr {
class AsyncDeviceToken : public DeviceToken {
  public:
    AsyncDeviceToken(std::string const &name);
    virtual ~AsyncDeviceToken();

    virtual AsyncDeviceToken *asAsyncDevice();

    void setWaitCallback(OGVR_AsyncDeviceWaitCallback cb, void *userData);

  private:
    void m_waitCallbackLoop();
    virtual void m_sendData(MessageType *type, const char *bytestream,
                            size_t len);
    virtual void m_connectionInteract();
    boost::optional<CallbackWrapper<OGVR_AsyncDeviceWaitCallback> > m_cb;

#ifdef TRY_WITH_THREADS
    boost::thread m_callbackThread;

    boost::mutex m_dataWaiting;
    boost::mutex m_interacting;
    boost::mutex m_conditionMut;
    boost::condition_variable m_cond;
#endif
    volatile bool m_interactionEnabled;
    volatile bool m_done;
};
} // end of namespace ogvr
#endif // INCLUDED_AsyncDeviceToken_h_GUID_654218B0_3900_4B89_E86F_D314EB6C0ABF
