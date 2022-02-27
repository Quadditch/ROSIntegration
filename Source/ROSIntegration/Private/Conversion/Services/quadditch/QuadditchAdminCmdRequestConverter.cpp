#include "Conversion/Services/quadditch/QuadditchAdminCmdRequestConverter.h"
#include "quadditch/AdminCmdRequest.h"

UQuadditchAdminCmdRequestConverter::UQuadditchAdminCmdRequestConverter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	_ServiceType = "quadditch/AdminCmd";
}

bool UQuadditchAdminCmdRequestConverter::ConvertOutgoingRequest(TSharedPtr<FROSBaseServiceRequest> Request, bson_t** BSONRequest)
{
	auto AdminCmdRequest = StaticCastSharedPtr<quadditch::FAdminCmdRequest>(Request);
	*BSONRequest = BCON_NEW(
		"command", BCON_UTF8(TCHAR_TO_UTF8(*AdminCmdRequest->_cmd)),
		"intermediate", BCON_UTF8(TCHAR_TO_UTF8(*AdminCmdRequest->_inter))
	);

	UE_LOG(LogTemp, Verbose, TEXT("This is rospy req converter"));
	return true;
}

bool UQuadditchAdminCmdRequestConverter::ConvertIncomingRequest(ROSBridgeCallServiceMsg &req, TSharedPtr<FROSBaseServiceRequest> Request)
{
	//*Request = MakeShareable(new quadditch::FAdminCmdRequest);
	auto ServiceRequest = StaticCastSharedPtr<quadditch::FAdminCmdRequest>(Request);
	bool key_found = false;

	// Retrieve attributes from wire-representation of class
	ServiceRequest->_cmd = rosbridge2cpp::Helper::get_utf8_by_key("args.command", *(req.full_msg_bson_), key_found).c_str();
	if (!key_found) {
		UE_LOG(LogTemp, Error, TEXT("Key args.command not present in data"));
		return false;
	}
	UE_LOG(LogTemp, Verbose, TEXT("Request.command is %s"), TCHAR_TO_UTF8(*ServiceRequest->_cmd));

	ServiceRequest->_inter = rosbridge2cpp::Helper::get_utf8_by_key("args.intermediate", *(req.full_msg_bson_), key_found).c_str();
	if (!key_found) {
		UE_LOG(LogTemp, Error, TEXT("Key args.intermediate not present in data"));
		return false;
	}
	UE_LOG(LogTemp, Verbose, TEXT("Request.intermediate is %s"), TCHAR_TO_UTF8(*ServiceRequest->_inter));

	return true;
}

TSharedPtr<FROSBaseServiceRequest> UQuadditchAdminCmdRequestConverter::AllocateConcreteRequest()
{
	return MakeShareable(new quadditch::FAdminCmdRequest);
}
