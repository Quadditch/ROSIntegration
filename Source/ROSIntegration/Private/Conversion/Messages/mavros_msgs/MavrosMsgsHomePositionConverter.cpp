#include "Conversion/Messages/mavros_msgs/MavrosMsgsHomePositionConverter.h"


UMavrosMsgsHomePositionConverter::UMavrosMsgsHomePositionConverter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	_MessageType = "mavros_msgs/HomePosition";
}

bool UMavrosMsgsHomePositionConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg)
{
	auto p = new ROSMessages::mavros_msgs::HomePosition();
	BaseMsg = TSharedPtr<FROSBaseMsg>(p);

	if (!UStdMsgsHeaderConverter::_bson_extract_child_header(message->full_msg_bson_, TEXT("msg.header"), &p->header)) return false;
	if (!UGeometryMsgsPointConverter::_bson_extract_child_point(message->full_msg_bson_, TEXT("msg.position"), &p->position)) return false;
	if (!UGeometryMsgsQuaternionConverter::_bson_extract_child_quaternion(message->full_msg_bson_, TEXT("msg.orientation"), &p->orientation)) return false;
	if (!UGeometryMsgsVector3Converter::_bson_extract_child_vector3(message->full_msg_bson_, TEXT("msg.approach"), &p->approach)) return false;
	if (!UGeographicMsgsGeoPointConverter::_bson_extract_child_geo_point(message->full_msg_bson_, TEXT("msg.geo"), &p->geo)) return false;

	return true;
}

bool UMavrosMsgsHomePositionConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message)
{
	auto HomePosition = StaticCastSharedPtr<ROSMessages::mavros_msgs::HomePosition>(BaseMsg);

	*message = new bson_t;
	bson_init(*message);

	_bson_append_home_position(*message, HomePosition.Get());

	return true;
}
