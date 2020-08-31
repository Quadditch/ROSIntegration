#include "Conversion/Messages/geographic_msgs/GeographicMsgsGeoPointConverter.h"

#include "geographic_msgs/GeoPoint.h"

UGeographicMsgsGeoPointConverter::UGeographicMsgsGeoPointConverter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	_MessageType = "geographic_msgs/GeoPoint";
}

bool UGeographicMsgsGeoPointConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg)
{
	auto p = new ROSMessages::geographic_msgs::GeoPoint();
	BaseMsg = TSharedPtr<FROSBaseMsg>(p);
	return _bson_extract_child_geo_point(message->full_msg_bson_, "msg", p);
}

bool UGeographicMsgsGeoPointConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message)
{
	auto GeoPoint = StaticCastSharedPtr<ROSMessages::geographic_msgs::GeoPoint>(BaseMsg);

	*message = new bson_t;
	bson_init(*message);
	_bson_append_geo_point(*message, GeoPoint.Get());

	return true;
}
