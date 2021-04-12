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
#include "OgreTrays.h"
#include "OgreRoot.h"
#include "OgreOverlaySystem.h"
#include "OgreResourceManager.h"
#include "OgreComponents.h"
#include "OgreCameraMan.h"
#include "OgreInput.h"

#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>


#include "OgreFileSystemLayer.h"

#ifdef INCLUDE_RTSHADER_SYSTEM
#   include "OgreRTShaderSystem.h"
#endif //INCLUDE_RTSHADER_SYSTEM

#include "OgreInput.h"


using namespace Ogre;
using namespace OgreBites;

class COgreSampleApp : public OgreBites::ApplicationContext,
						public OgreBites::InputListener, public TrayListener
{
	public:

		COgreSampleApp():
			OgreBites::ApplicationContext("OgreSampleApp"){}

		virtual void setupView();
		virtual void setDragLook(bool enabled);
		virtual void checkBoxToggled(CheckBox* box);
		virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
		virtual void setupParticles();
		virtual void setupTogglers();
		virtual void setupContent();
		virtual void frameRendered(const Ogre::FrameEvent& evt)
		{
			std::cout << "frameRendered " << std::endl;
		}

		virtual void setup();

	private:
		Ogre::SceneManager* scnMgr = nullptr;

		Ogre::Viewport* mViewport = nullptr;          // main viewport
		Ogre::Camera* mCamera = nullptr;              // main camera
		Ogre::SceneNode* mCameraNode = nullptr;       // camera node
		Ogre::RenderWindow* mWindow = nullptr;      // context render window
		TrayManager* mTrayMgr = nullptr;           // tray interface manager
		CameraMan* mCameraMan = nullptr;           // basic camera controller
		bool mCursorWasVisible = false;             // was cursor visible before dialog appeared
		bool mDragLook = false;                     // click and drag to free-look
		SceneNode* mFountainPivot = nullptr;
};

#endif /* OGRE_SAMPLE_APP_HPP_ */
