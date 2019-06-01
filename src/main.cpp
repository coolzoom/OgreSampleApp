/*
 * main.cpp
 *
 *  Created on: 31/5/2019
 *      Author: juanitov
 */


#include "ogre_sample_app.hpp"

int main(int argc, char** argv)
{

	COgreSampleApp app;
	app.initApp();
	app.getRoot()->startRendering();

	app.closeApp();
	return 0;
}

