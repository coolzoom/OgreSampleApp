
#include <iostream>

#include "ogre_sample_app.hpp"

#include "OgreSceneNode.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "OgreEntity.h"

Ogre::SceneManager* scnMgr = nullptr;

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
	Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 15);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	// finally something to render
	Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
	Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);


	OgreBites::Event evt;

	evt.type = OgreBites::KEYDOWN;
	evt.key.keysym.sym = OgreBites::SDLK_ESCAPE; //BUTTON_LEFT;
	evt.key.keysym.mod = 0;
	evt.key.repeat = 1;
	evt.key.type = OgreBites::KEYDOWN;

	this->_fireInputEvent(evt, 0);

}



