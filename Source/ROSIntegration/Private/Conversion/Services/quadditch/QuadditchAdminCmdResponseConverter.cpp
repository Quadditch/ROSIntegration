#include "Conversion/Services/quadditch/QuadditchAdminCmdResponseConverter.h"
#include "quadditch/AdminCmdResponse.h"
#include <bson.h>


UQuadditchAdminCmdResponseConverter::UQuadditchAdminCmdResponseConverter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	_ServiceType = "quadditch/AdminCmd";
}

bool UQuadditchAdminCmdResponseConverter::ConvertIncomingResponse(const ROSBridgeServiceResponseMsg &res, TSharedRef<TSharedPtr<FROSBaseServiceResponse>> Response)
{
	bool key_found = false;
	*Response = MakeShareable(new quadditch::FAdminCmdResponse);
	auto ServiceResponse = StaticCastSharedPtr<quadditch::FAdminCmdResponse>(*Response);

	ServiceResponse->_Result = res.result_;

	ServiceResponse->_ack = rosbridge2cpp::Helper::get_bool_by_key("values.ack", *res.full_msg_bson_, key_found);
	if (!key_found) {
		UE_LOG(LogTemp, Error, TEXT("Key values.ack not present in data"));
		return false;
	}

	return true;
}

bool UQuadditchAdminCmdResponseConverter::ConvertOutgoingResponse(TSharedPtr<FROSBaseServiceResponse> Response, ROSBridgeServiceResponseMsg &res)
{
	auto ServiceResponse = StaticCastSharedPtr<quadditch::FAdminCmdResponse>(Response);

	res.result_ = ServiceResponse->_Result;
	BSON_APPEND_INT32(res.values_bson_, "ack", ServiceResponse->_ack);
	return true;
}

TSharedPtr<FROSBaseServiceResponse> UQuadditchAdminCmdResponseConverter::AllocateConcreteResponse()
{
	return MakeShareable(new quadditch::FAdminCmdResponse);
}
