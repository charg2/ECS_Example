export module Packet;

import Position;

export class IPacket {};

export class C_Move : public IPacket
{
public:
    Position fromPos;
    Position toPos;
};

export class S_MoveFail : public IPacket
{
public:
    Position fromPos;
};

export class S_MoveOk : public IPacket
{
public:
    Position fromPos;
    Position toPos;
};
