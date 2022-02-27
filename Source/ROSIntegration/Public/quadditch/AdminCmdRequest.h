#pragma once

#include <CoreMinimal.h>
#include "ROSBaseServiceRequest.h"

namespace quadditch {
	class ROSINTEGRATION_API FAdminCmdRequest : public FROSBaseServiceRequest {

	public:
		FAdminCmdRequest() = default;
		~FAdminCmdRequest() = default;

		FString _cmd, _inter;
	};
}
