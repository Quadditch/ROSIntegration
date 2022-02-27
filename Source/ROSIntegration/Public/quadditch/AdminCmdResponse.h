#pragma once

#include <CoreMinimal.h>

#include "ROSBaseServiceResponse.h"

namespace quadditch {
	class ROSINTEGRATION_API FAdminCmdResponse : public FROSBaseServiceResponse {

	public:
		FAdminCmdResponse() = default;
		~FAdminCmdResponse() = default;

		bool _ack;
	};
}
