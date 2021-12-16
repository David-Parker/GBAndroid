//
// Created by David on 12/15/2021.
//

#pragma once

#include <jni.h>
#include <GlobalDefinitions.h>
#include <ISerialHandler.h>

class SerialNetworkHandler : public ISerialHandler
{
public:
    SerialNetworkHandler()
    {

    }

    bool IsSerialConnected();
    void SendByte(Byte byte);
    bool ByteRecieved();
    Byte RecieveByte();
};