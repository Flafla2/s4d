
#pragma once

#include "../lib/gl.h"

#include <string>

namespace Util {

	GL::Mesh cube_mesh(float radius = 0.5f);
	std::string obj_mesh(std::string obj_file, GL::Mesh& mesh);
}