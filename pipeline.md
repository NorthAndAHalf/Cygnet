Phase 1:
	Perform intersection tests with each traceable's root bounding box
	Store a pointer to each traceable that is intersected by the ray
Phase 2:
	Traverse the acceleration structures of each traceable that was intersected in phase 1
	Store the hitpoints if they are generated, discard the traceable if no hitpoint is generated (miss)
Phase 3:
	Find the closest hitpoint to the camera
	Store this hitpoint, discard all other hitpoints
Phase 4:
	Evaluate the rendering equation on this hitpoint (Recurse back to phase 1)