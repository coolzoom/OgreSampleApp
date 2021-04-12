
#include <iostream>

#include "ogre_sample_app.hpp"

#include "OgreSceneNode.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "OgreEntity.h"
#include "OgreParticleSystem.h"


void COgreSampleApp::setupView()
{
	// setup default viewport layout and camera
	mCamera = scnMgr->createCamera("MainCamera");
	mCameraNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	mCameraNode->attachObject(mCamera);
	mCameraNode->setFixedYawAxis(true);
	mViewport = mWindow->addViewport(mCamera);
	mCamera->setAspectRatio((Ogre::Real)mViewport->getActualWidth() / (Ogre::Real)mViewport->getActualHeight());
	mCamera->setAutoAspectRatio(true);
	mCamera->setNearClipDistance(5);

	mCameraMan = new CameraMan(mCameraNode);   // create a default camera controller
}

void COgreSampleApp::setDragLook(bool enabled)
{
	if (enabled)
	{
		mCameraMan->setStyle(CS_MANUAL);
		mTrayMgr->showCursor();
		mDragLook = true;
	}
	else
	{
		mCameraMan->setStyle(CS_FREELOOK);
		mTrayMgr->hideCursor();
		mDragLook = false;
	}
}

void COgreSampleApp::checkBoxToggled(CheckBox* box)
{
	// show or hide the particle system with the same name as the check box
	scnMgr->getParticleSystem(box->getName())->setVisible(box->isChecked());
}

void COgreSampleApp::setupParticles()
{
	ParticleSystem::setDefaultNonVisibleUpdateTimeout(5);  // set nonvisible timeout

	ParticleSystem* ps;

	// create some nice fireworks and place it at the origin
	ps = scnMgr->createParticleSystem("Fireworks", "Examples/Fireworks");
	scnMgr->getRootSceneNode()->attachObject(ps);

	// create a green nimbus around the ogre head
	ps = scnMgr->createParticleSystem("Nimbus", "Examples/GreenyNimbus");
	scnMgr->getRootSceneNode()->attachObject(ps);

	ps = scnMgr->createParticleSystem("Rain", "Examples/Rain");  // create a rainstorm
	ps->fastForward(5);   // fast-forward the rain so it looks more natural
	scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(0, 1000, 0))->attachObject(ps);

	// create aureola around ogre head perpendicular to the ground
	ps = scnMgr->createParticleSystem("Aureola", "Examples/Aureola");
	scnMgr->getRootSceneNode()->attachObject(ps);

	// create shared pivot node for spinning the fountains
	mFountainPivot = scnMgr->getRootSceneNode()->createChildSceneNode();

	ps = scnMgr->createParticleSystem("Fountain1", "Examples/PurpleFountain");  // create fountain 1
	// attach the fountain to a child node of the pivot at a distance and angle
	mFountainPivot->createChildSceneNode(Vector3(200, -100, 0), Quaternion(Degree(20), Vector3::UNIT_Z))->attachObject(ps);

	ps = scnMgr->createParticleSystem("Fountain2", "Examples/PurpleFountain");  // create fountain 2
	// attach the fountain to a child node of the pivot at a distance and angle
	mFountainPivot->createChildSceneNode(Vector3(-200, -100, 0), Quaternion(Degree(-20), Vector3::UNIT_Z))->attachObject(ps);
}

void COgreSampleApp::setupTogglers()
{
	// create check boxes to toggle the visibility of our particle systems
	mTrayMgr->createLabel(TL_TOPLEFT, "VisLabel", "Particles");
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Fireworks", "Fireworks", 130)->setChecked(true);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Fountain1", "Fountain A", 130)->setChecked(true);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Fountain2", "Fountain B", 130)->setChecked(true);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Aureola", "Aureola", 130)->setChecked(false);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Nimbus", "Nimbus", 130)->setChecked(false);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Rain", "Rain", 130)->setChecked(false);
}
void COgreSampleApp::setupContent()
{
	// setup some basic lighting for our scene
	scnMgr->setAmbientLight(ColourValue(0.3, 0.3, 0.3));
	scnMgr->getRootSceneNode()
		->createChildSceneNode(Vector3(20, 80, 50))
		->attachObject(scnMgr->createLight());

	// set our camera to orbit around the origin and show cursor
	mCameraMan->setStyle(CS_ORBIT);
	mCameraMan->setYawPitchDist(Degree(0), Degree(15), 250);
	mTrayMgr->showCursor();

	// create an ogre head entity and place it at the origin
	Entity* ent = scnMgr->createEntity("Head", "ogrehead.mesh");
	scnMgr->getRootSceneNode()->attachObject(ent);

	setupParticles();   // setup particles
	setupTogglers();    // setup particle togglers
}

////////////////////////////////////////////////////////////////////////////////
bool COgreSampleApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	std::cout << " COgreSampleApp::keyPressed " << std::endl;

	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		std::cout << " SDLK_ESCAPE " << std::endl;
		getRoot()->queueEndRendering();
	}
	else if (evt.keysym.sym == OgreBites::SDLK_F9)
	{
		std::cout << " SDLK_F9 " << std::endl;
		getRoot()->queueEndRendering();
	}
	else if (evt.keysym.sym == OgreBites::BUTTON_LEFT)
	{
		std::cout << " BUTTON_LEFT " << std::endl;
	}
	else if (evt.keysym.sym == OgreBites::BUTTON_RIGHT)
	{
		std::cout << " BUTTON_RIGHT " << std::endl;
	}

	std::cout << "input listeners " << this->mInputListeners.size() << std::endl;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
void COgreSampleApp::setup(void)
{
	// do not forget to call the base first
	OgreBites::ApplicationContext::setup();
	mWindow = getRenderWindow();
	std::cout << "windows list size " << this->mWindows.size() << std::endl;

	// register for input events
	addInputListener(this);

	// get a pointer to the already created root
	Ogre::Root* root = getRoot();
	//Ogre::SceneManager* scnMgr = root->createSceneManager();
	scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);
	// without light we would just get a black screen
	Ogre::Light* light = scnMgr->createLight("MainLight");
	Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 10, 15);
	lightNode->attachObject(light);
	// also need to tell where we are
	//Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	//camNode->setPosition(0, 0, 15);
	//camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	//// create the camera
	//Ogre::Camera* cam = scnMgr->createCamera("myCam");
	//cam->setNearClipDistance(5); // specific to this sample
	//cam->setAutoAspectRatio(true);
	//camNode->attachObject(cam);
	//// and tell it to render into the main window
	//getRenderWindow()->addViewport(cam);

    setupView();
	mTrayMgr = new TrayManager("SampleControls", mWindow, this);  // create a tray interface
	// finally something to render
	Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
	Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);

	setupContent();


	OgreBites::Event evt;

	evt.type = OgreBites::KEYDOWN;
	evt.key.keysym.sym = OgreBites::SDLK_ESCAPE; //BUTTON_LEFT;
	evt.key.keysym.mod = 0;
	evt.key.repeat = 1;
	evt.key.type = OgreBites::KEYDOWN;

	this->_fireInputEvent(evt, 0);

}



