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
#include "OgreAdvancedRenderControls.h"
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
			OgreBites::ApplicationContext("OgreSampleApp"){
			// so we don't have to worry about checking if these keys exist later

			mTrayMgr = 0;
			mCameraMan = 0;
			mCamera = 0;
			mCameraNode = 0;
			mViewport = 0;
			mControls = 0;
			mCursorWasVisible = false;
			mDragLook = false;
		}

		virtual void setDragLook(bool enabled);
		virtual void checkBoxToggled(CheckBox* box);
		//virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
		virtual void setupParticles();

		virtual void frameRendered(const Ogre::FrameEvent& evt)
		{
			//std::cout << "frameRendered " << std::endl;
		}
        /*-----------------------------------------------------------------------------
      | Extends frameRenderingQueued to update tray manager and carousel.
      -----------------------------------------------------------------------------*/
        bool frameRenderingQueued(const Ogre::FrameEvent& evt)
        {

			mTrayMgr->frameRendered(evt);
			mControls->frameRendered(evt);
			if (!mTrayMgr->isDialogVisible())
			{
				mCameraMan->frameRendered(evt);   // if dialog isn't up, then update the camera
			}

            try
            {
                return ApplicationContext::frameRenderingQueued(evt);
            }
            catch (Ogre::Exception& e)   // show error and fall back to menu
            {
                mTrayMgr->showOkDialog("Error!", e.getDescription() + "\nSource: " + e.getSource());
            }

            return true;
        }

		virtual void setup();

	private:
		Ogre::SceneManager* scnMgr = nullptr;

		Ogre::Viewport* mViewport = nullptr;          // main viewport
		Ogre::Camera* mCamera = nullptr;              // main camera
		Ogre::SceneNode* mCameraNode = nullptr;       // camera node
		//Ogre::RenderWindow* mWindow = nullptr;      // context render window
		TrayManager* mTrayMgr = nullptr;           // tray interface manager
		CameraMan* mCameraMan = nullptr;           // basic camera controller
		bool mCursorWasVisible = false;             // was cursor visible before dialog appeared
		bool mDragLook = false;                     // click and drag to free-look
		AdvancedRenderControls* mControls;
		SceneNode* mFountainPivot = nullptr;
};

#endif /* OGRE_SAMPLE_APP_HPP_ */
