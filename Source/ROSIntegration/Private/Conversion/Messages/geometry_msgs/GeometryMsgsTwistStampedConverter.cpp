#include "Conversion/Messages/geometry_msgs/GeometryMsgsTwistStampedConverter.h"


UGeometryMsgsTwistStampedConverter::UGeometryMsgsTwistStampedConverter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	_MessageType = "geometry_msgs/TwistStamped";
}

bool UGeometryMsgsTwistStampedConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg)
{
	auto p = new ROSMessages::geometry_msgs::TwistStamped();
	BaseMsg = TSharedPtr<FROSBaseMsg>(p);

	if (!UStdMsgsHeaderConverter::_bson_extract_child_header(message->full_msg_bson_, TEXT("msg.header"), &p->header)) return false;
	if (!UGeometryMsgsTwistConverter::_bson_extract_child_twist(message->full_msg_bson_, TEXT("msg.twist"), &p->twist)) return false;

	return true;
}

bool UGeometryMsgsTwistStampedConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message)
{
	auto TwistStamped = StaticCastSharedPtr<ROSMessages::geometry_msgs::TwistStamped>(BaseMsg);

	*message = new bson_t;
	bson_init(*message);

	_bson_append_twist_stamped(*message, TwistStamped.Get());

	return true;
}
