#pragma once

#include <CoreMinimal.h>
#include <UObject/ObjectMacros.h>
#include <UObject/Object.h>
#include "Conversion/Messages/BaseMessageConverter.h"
#include "geometry_msgs/TwistStamped.h"
#include "Conversion/Messages/std_msgs/StdMsgsHeaderConverter.h"
#include "Conversion/Messages/geometry_msgs/GeometryMsgsTwistConverter.h"

#include "GeometryMsgsTwistStampedConverter.generated.h"


UCLASS()
class ROSINTEGRATION_API UGeometryMsgsTwistStampedConverter : public UBaseMessageConverter
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg);
	virtual bool ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message);

	static bool _bson_extract_child_twist_stamped(bson_t *b, FString key, ROSMessages::geometry_msgs::TwistStamped * ps, bool LogOnErrors = true)
	{
		bool KeyFound = false;

		KeyFound = UStdMsgsHeaderConverter::_bson_extract_child_header(b, key + ".header", &ps->header);
		if (!KeyFound) return false;

		KeyFound = UGeometryMsgsTwistConverter::_bson_extract_child_twist(b, key + ".twist", &ps->twist);
		if (!KeyFound) return false;

		return true;
	}

	static void _bson_append_child_twist_stamped(bson_t *b, const char *key, const ROSMessages::geometry_msgs::TwistStamped * ps)
	{
		bson_t layout;
		BSON_APPEND_DOCUMENT_BEGIN(b, key, &layout);
		_bson_append_twist_stamped(&layout, ps);
		bson_append_document_end(b, &layout);
	}

	static void _bson_append_twist_stamped(bson_t *b, const ROSMessages::geometry_msgs::TwistStamped * ps)
	{
		UStdMsgsHeaderConverter::_bson_append_header(b, &(ps->header));
		UGeometryMsgsTwistConverter::_bson_append_child_twist(b, "twist", &(ps->twist));
	}
};
