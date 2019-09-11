#include "al2o3_platform/platform.h"
#include "al2o3_catch2/catch2.hpp"
#include "physics_physx4/api.h"

TEST_CASE("Create and Destroy", "[physics_physx4]") {

	auto engine = Physics_EngineCreate();
	REQUIRE(engine);
	Physics_EngineDestroy(engine);
}
