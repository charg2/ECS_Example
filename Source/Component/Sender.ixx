export module Sender;

import <memory>;
import <iostream>;


export class IPacket;

export class Sender
{
public:
    void Send( const IPacket& packet )
    {
        std::cout << "Packet sent!" << std::endl;
    }
};

export using SenderPtr = std::shared_ptr< Sender >;
export using SenderRef = const SenderPtr&;
