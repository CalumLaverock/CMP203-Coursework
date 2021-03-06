#include "Cube.h"

Cube::Cube()
{
	verts.assign
	({	-1.0, 1.0, 1.0,			// #0 - Front
		-1.0, -1.0, 1.0,		// #1
		1.0,  -1.0, 1.0,		// #2
		1.0,  1.0, 1.0,		// #3

		-1.0, 1.0, -1.0,		// #4 - Left
		-1.0, -1.0, -1.0,		// #5
		-1.0, -1.0, 1.0,		// #6
		-1.0, 1.0, 1.0,			// #7

		1.0, 1.0, -1.0,		// #8 - Back
		1.0, -1.0, -1.0,		// #9
		-1.0, -1.0, -1.0,		// #10
		-1.0, 1.0, -1.0,		// #11

		1.0, 1.0, 1.0,			// #12 - Right
		1.0, -1.0, 1.0,		// #13
		1.0, -1.0, -1.0,		// #14
		1.0, 1.0, -1.0,		// #15

		-1.0, 1.0, -1.0,		// #16 - Top
		-1.0, 1.0, 1.0,			// #17
		1.0, 1.0, 1.0,			// #18
		1.0, 1.0, -1.0,		// #19

		-1.0, -1.0, 1.0,		// #20 - Bottom
		-1.0, -1.0, -1.0,		// #21
		1.0, -1.0, -1.0,		// #22
		1.0, -1.0, 1.0,		// #23
		});

	norms.assign
	({	0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,

		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,

		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,

		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,

		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,

		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		});

	texCoords.assign
	({	0.0, 0.0,	
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,

		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,

		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,

		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,

		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,

		0.0, 0.0, 
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
		});
}

Cube::~Cube()
{
}
