//
// Created by David on 12/15/2021.
//

#include "SerialNetworkHandler.h"

bool SerialNetworkHandler::IsSerialConnected()
{
    return false;
}

void SerialNetworkHandler::SendByte(Byte byte)
{

}

bool SerialNetworkHandler::ByteRecieved()
{
    return false;
}

Byte SerialNetworkHandler::RecieveByte()
{
    return 0xFF;
}
