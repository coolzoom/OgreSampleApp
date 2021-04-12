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
			//mCamera = 0;
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

		//virtual void frameRendered(const Ogre::FrameEvent& evt)
		//{
		//	std::cout << "frameRendered " << std::endl;
		//}

        /*-----------------------------------------------------------------------------
      | Extends frameRenderingQueued to update tray manager and carousel.
      -----------------------------------------------------------------------------*/
        bool frameRenderingQueued(const Ogre::FrameEvent& evt)
        {
            std::cout << "frameRenderingQueued " << std::endl;
			mTrayMgr->frameRendered(evt);
			mControls->frameRendered(evt);

			mCameraMan->frameRendered(evt);   // if dialog isn't up, then update the camera


            try
            {
                return OgreBites::ApplicationContext::frameRenderingQueued(evt);
            }
            catch (Ogre::Exception& e)   // show error and fall back to menu
            {
                mTrayMgr->showOkDialog("Error!", e.getDescription() + "\nSource: " + e.getSource());
            }

            return true;
        }
        /*-----------------------------------------------------------------------------
   | Extends pointerPressed to inject mouse press into tray manager, and to check
   | for thumbnail clicks, just because we can.
   -----------------------------------------------------------------------------*/
        virtual bool mousePressed(const MouseButtonEvent& evt)
        {
            mTrayMgr->mousePressed(evt);
            mControls->mousePressed(evt);
            
            if (mDragLook && evt.button == BUTTON_LEFT)
            {
                mCameraMan->setStyle(CS_FREELOOK);
                mTrayMgr->hideCursor();
            }
            mCameraMan->mousePressed(evt);
            std::cout << "mousePressed " << std::endl;
            return true;
        }

        // convert and redirect
        virtual bool touchPressed(const TouchFingerEvent& evt) {
            MouseButtonEvent e;
            e.button = BUTTON_LEFT;
            std::cout << "touchPressed " << std::endl;
            return mousePressed(e);
        }

        /*-----------------------------------------------------------------------------
          | Extends pointerReleased to inject mouse release into tray manager.
          -----------------------------------------------------------------------------*/
        virtual bool mouseReleased(const MouseButtonEvent& evt)
        {
            std::cout << "mouseReleased " << std::endl;
            mTrayMgr->mouseReleased(evt);
            if (mDragLook && evt.button == BUTTON_LEFT)
            {
                mCameraMan->setStyle(CS_MANUAL);
                mTrayMgr->showCursor();
            }
            mCameraMan->mouseReleased(evt);
            mControls->mousePressed(evt);
            return true;
        }

        virtual bool keyPressed(const KeyboardEvent& evt)
        {
            mTrayMgr->keyPressed(evt);
            mCameraMan->keyPressed(evt);
            mControls->keyPressed(evt);
            std::cout << "keyPressed " << std::endl;
            return true;
        }

        virtual bool keyReleased(const KeyboardEvent& evt)
        {
            mTrayMgr->keyReleased(evt);
            mCameraMan->keyReleased(evt);
            mControls->keyReleased(evt);
            std::cout << "keyReleased " << std::endl;
            return true;
        }

        // convert and redirect
        virtual bool touchReleased(const TouchFingerEvent& evt) {
            MouseButtonEvent e;
            e.button = BUTTON_LEFT;
            std::cout << "touchReleased " << std::endl;
            return mouseReleased(e);
        }

        /*-----------------------------------------------------------------------------
          | Extends pointerMoved to inject mouse position into tray manager, and checks
          | for mouse wheel movements to slide the carousel, because we can.
          -----------------------------------------------------------------------------*/
        virtual bool mouseMoved(const MouseMotionEvent& evt)
        {
            mTrayMgr->mouseMoved(evt);
            mCameraMan->mouseMoved(evt);
            mControls->mouseMoved(evt);
            std::cout << "mouseMoved " << std::endl;
            return true;
        }

        // convert and redirect
        virtual bool touchMoved(const TouchFingerEvent& evt) {
            MouseMotionEvent e;
            e.x = evt.x * getRenderWindow()->getWidth();
            e.y = evt.y * getRenderWindow()->getHeight();
            e.xrel = evt.dx * getRenderWindow()->getWidth();
            e.yrel = evt.dy * getRenderWindow()->getHeight();
            std::cout << "touchMoved " << std::endl;
            return mouseMoved(e);
        }

        //TODO: Handle iOS and Android.
        /** Mouse wheel scrolls the sample list.
         */
        virtual bool mouseWheelRolled(const MouseWheelEvent& evt)
        {
            mTrayMgr->mouseWheelRolled(evt);
            mCameraMan->mouseWheelRolled(evt);
            mControls->mouseWheelRolled(evt);
            std::cout << "mouseWheelRolled " << std::endl;
            return true;
        }
		virtual void setup();

	private:
		Ogre::SceneManager* scnMgr = nullptr;

		Ogre::Viewport* mViewport = nullptr;          // main viewport
		//Ogre::Camera* mCamera = nullptr;              // main camera
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
