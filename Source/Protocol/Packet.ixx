export module Packet;

import Position;

export class IPacket {};

export class C_Move : public IPacket
{
public:
    Position fromPos;
    Position toPos;
};

export class S_Move : public IPacket
{
public:
    Position fromPos;
    Position toPos;
};
