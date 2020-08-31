#pragma once

#include <CoreMinimal.h>
#include <UObject/ObjectMacros.h>
#include <UObject/Object.h>
#include "Conversion/Messages/BaseMessageConverter.h"
#include "geographic_msgs/GeoPoint.h"
#include "Conversion/Messages/std_msgs/StdMsgsFloat32Converter.h"

#include "GeographicMsgsGeoPointConverter.generated.h"


UCLASS()
class ROSINTEGRATION_API UGeographicMsgsGeoPointConverter : public UBaseMessageConverter
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg);
	virtual bool ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message);

	static bool _bson_extract_child_geo_point(bson_t *b, FString key, ROSMessages::geographic_msgs::GeoPoint * ps, bool LogOnErrors = true)
	{
		bool KeyFound = true;

		ps->latitude = GetDoubleFromBSON(key + ".latitude", b, KeyFound, LogOnErrors); if (!KeyFound) return false;
		ps->longitude = GetDoubleFromBSON(key + ".longitude", b, KeyFound, LogOnErrors); if (!KeyFound) return false;
		ps->altitude = GetDoubleFromBSON(key + ".altitude", b, KeyFound, LogOnErrors); if (!KeyFound) return false;
		return true;
	}

	static void _bson_append_child_geo_point(bson_t *b, const char *key, const ROSMessages::geographic_msgs::GeoPoint * ps)
	{
		bson_t layout;
		BSON_APPEND_DOCUMENT_BEGIN(b, key, &layout);
		_bson_append_geo_point(&layout, ps);
		bson_append_document_end(b, &layout);
	}

	static void _bson_append_geo_point(bson_t *b, const ROSMessages::geographic_msgs::GeoPoint * ps)
	{
		BSON_APPEND_DOUBLE(b, "latitude", ps->latitude);
		BSON_APPEND_DOUBLE(b, "longitude", ps->longitude);
		BSON_APPEND_DOUBLE(b, "altitude", ps->altitude);
	}
};
