#pragma once
#include "../../../dependencies/utilities/singleton.hpp"
class c_visuals : public singleton< c_visuals > {
private:

public:
	void run();
	void run_viewmodel();
	void force_crosshair();
};