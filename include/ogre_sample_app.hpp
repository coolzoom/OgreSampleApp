/*
 * ogre_sample_app.hpp
 *
 *  Created on: 31/5/2019
 *      Author: juanitov
 */

#ifndef OGRE_SAMPLE_APP_HPP_
#define OGRE_SAMPLE_APP_HPP_


#define INCLUDE_RTSHADER_SYSTEM 1

#include <iostream>

#include "OgreApplicationContext.h"

#include "OgreRoot.h"
#include "OgreOverlaySystem.h"
#include "OgreResourceManager.h"
#include "OgreComponents.h"

#include "OgreInput.h"

#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>


#include "OgreFileSystemLayer.h"

#ifdef INCLUDE_RTSHADER_SYSTEM
#   include "OgreRTShaderSystem.h"
#endif //INCLUDE_RTSHADER_SYSTEM

#include "OgreInput.h"


class COgreSampleApp : public OgreBites::ApplicationContext,
						public OgreBites::InputListener
{
	public:

		COgreSampleApp():
			OgreBites::ApplicationContext("OgreSampleApp"){}

		virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

		virtual void frameRendered(const Ogre::FrameEvent& evt)
		{
			std::cout << "frameRendered " << std::endl;
		}

		virtual void setup();

	private:

};

#endif /* OGRE_SAMPLE_APP_HPP_ */
