#pragma once

#include "ROSBaseMsg.h"

#include "geometry_msgs/Twist.h"
#include "std_msgs/Header.h"

namespace ROSMessages {
	namespace geometry_msgs {
		class TwistStamped : public FROSBaseMsg {
		public:
			TwistStamped() {
				_MessageType = "geometry_msgs/TwistStamped";
			}

			std_msgs::Header header;
			geometry_msgs::Twist twist;
		};
	}
}
