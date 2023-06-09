#pragma once

#include "network/IProtocolMessage.h"

class UpdatePointsMessage: public IProtocolMessage {
private:
	uint16_t _points;

public:
	explicit UpdatePointsMessage (uint16_t points) :
			IProtocolMessage(protocol::PROTO_UPDATEPOINTS), _points(points)
	{
	}

	PROTOCOL_CLASS_FACTORY(UpdatePointsMessage);

	explicit UpdatePointsMessage (ByteStream& input) :
			IProtocolMessage(protocol::PROTO_UPDATEPOINTS)
	{
		_points = input.readShort();
	}

	void serialize (ByteStream& out) const override
	{
		out.addByte(_id);
		out.addShort(_points);
	}

	inline uint16_t getPoints () const
	{
		return _points;
	}
};
