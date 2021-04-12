
#include <iostream>

#include "ogre_sample_app.hpp"

#include "OgreSceneNode.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "OgreEntity.h"
#include "OgreParticleSystem.h"
//#include "OgreHlmsManager.h"
//#include "OgreHlmsPbsMaterial.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
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

//////////////////////////////////////////////////////////////////////////////////
//bool COgreSampleApp::keyPressed(const OgreBites::KeyboardEvent& evt)
//{
//	std::cout << " COgreSampleApp::keyPressed " << std::endl;
//
//	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
//	{
//		std::cout << " SDLK_ESCAPE " << std::endl;
//		getRoot()->queueEndRendering();
//	}
//	else if (evt.keysym.sym == OgreBites::SDLK_F9)
//	{
//		std::cout << " SDLK_F9 " << std::endl;
//		getRoot()->queueEndRendering();
//	}
//	else if (evt.keysym.sym == OgreBites::BUTTON_LEFT)
//	{
//		std::cout << " BUTTON_LEFT " << std::endl;
//	}
//	else if (evt.keysym.sym == OgreBites::BUTTON_RIGHT)
//	{
//		std::cout << " BUTTON_RIGHT " << std::endl;
//	}
//
//	std::cout << "input listeners " << this->mInputListeners.size() << std::endl;
//
//	return true;
//}

////////////////////////////////////////////////////////////////////////////////
void COgreSampleApp::setup(void)
{
	// do not forget to call the base first
	OgreBites::ApplicationContext::setup();

	std::cout << "windows list size " << this->mWindows.size() << std::endl;


	// get a pointer to the already created root
	Ogre::Root* root = getRoot();
	//Ogre::SceneManager* scnMgr = root->createSceneManager();
	scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);
	// setup some basic lighting for our scene
	scnMgr->setAmbientLight(ColourValue(0.3, 0.3, 0.3));
	Ogre::Light* light = scnMgr->createLight("MainLight");
	Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 10, 15);
	lightNode->attachObject(light);

	scnMgr->addRenderQueueListener(mOverlaySystem);

	// also need to tell where we are
	mCameraNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	//mCameraNode->setPosition(0, 0, 15);
	mCameraNode->setFixedYawAxis(true);
	//mCameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	mCameraNode->attachObject(cam);
	// and tell it to render into the main window
	mViewport = getRenderWindow()->addViewport(cam);
	cam->setAspectRatio((Ogre::Real)mViewport->getActualWidth() / (Ogre::Real)mViewport->getActualHeight());


	////
	//// setup default viewport layout and camera
	//mCameraNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	//mCameraNode->setFixedYawAxis(true);
	//mCamera = scnMgr->createCamera("MainCamera");
	//mViewport = getRenderWindow()->addViewport(mCamera);
	//mCamera->setAspectRatio((Ogre::Real)mViewport->getActualWidth() / (Ogre::Real)mViewport->getActualHeight());
	//mCamera->setAutoAspectRatio(true);
	//mCamera->setNearClipDistance(5);
	//mCameraNode->attachObject(mCamera);
	//

	mCameraMan = new CameraMan(mCameraNode);   // create a default camera controller
	mCameraMan->setStyle(CS_ORBIT);
	mCameraMan->setYawPitchDist(Degree(0), Degree(15), 250);

	setupParticles();   // setup particles

	mTrayMgr = new TrayManager("SampleControls", getRenderWindow(), this);  // create a tray interface
	mTrayMgr->showCursor();
	//// create check boxes to toggle the visibility of our particle systems
	mTrayMgr->createLabel(TL_TOPLEFT, "VisLabel", "Particles");
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Fireworks", "Fireworks", 130)->setChecked(true);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Fountain1", "Fountain A", 130)->setChecked(true);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Fountain2", "Fountain B", 130)->setChecked(true);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Aureola", "Aureola", 130)->setChecked(false);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Nimbus", "Nimbus", 130)->setChecked(false);
	mTrayMgr->createCheckBox(TL_TOPLEFT, "Rain", "Rain", 130)->setChecked(false);
	mTrayMgr->showAll();
	//mTrayMgr->showCursor();
	mControls = new AdvancedRenderControls(mTrayMgr, cam);
	// create an ogre head entity and place it at the origin
	Entity* ent = scnMgr->createEntity("Head", "ogrehead.mesh");
	scnMgr->getRootSceneNode()->attachObject(ent);

	std::ifstream       file("C:\\Users\\Administrator\\Desktop\\data.csv");
	std::vector< std::vector<std::string> >   matrix;
	std::vector<std::string>   row;
	std::string                line;
	std::string                cell;

	while (file)
	{
		std::getline(file, line);
		std::stringstream lineStream(line);
		row.clear();

		while (std::getline(lineStream, cell, ','))
			row.push_back(cell);

		if (!row.empty())
			matrix.push_back(row);
	}

	for (int i = 0; i<int(matrix.size()); i++)
	{
		for (int j = 0; j<int(matrix[i].size()); j++)
		{
			std::cout << matrix[i][j] << " ";

		}
		if (i > 0)
		{
			float x = std::stof(matrix[i][0]);
			float y = std::stof(matrix[i][1]);
			float z = std::stof(matrix[i][2]) * 10;
			// do your stuff 
			//Entity* e = scnMgr->createEntity("ogrehead.mesh");
			//https://forums.ogre3d.org/viewtopic.php?p=301318&sid=ce193664e1d3d7c4af509e6f4e2718c6
			Entity* e = scnMgr->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);
			SceneNode* sceneNode = scnMgr->getRootSceneNode()->createChildSceneNode();
			sceneNode->setPosition(Vector3(x, y, z));
			sceneNode->setScale(Vector3(0.1f, 0.1f, 0.1f));
			sceneNode->attachObject(e);
			
			/*PbsMaterial* pbsMaterial = new PbsMaterial();
			pbsMaterial->setAlbedo(ColourValue::Green);

			pbsMaterial->setRoughness(0.012);
			pbsMaterial->setLightRoughnessOffset(0.2);

			float f0 = z;
			pbsMaterial->setF0(Ogre::ColourValue(f0, f0, f0));
			pbsMaterial->setEnvironmentMap(cubeMap);

			createHLMSMaterial(ent, pbsMaterial, "PBS_" + Ogre::StringConverter::toString(x) + "_" + Ogre::StringConverter::toString(z));*/
			std::cout << x << " " << y << " " << z;
		}

		std::cout << std::endl;
	}

	//// finally something to render
	//Ogre::Entity* ent2 = scnMgr->createEntity("Sinbad.mesh");
	//Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
	//node->attachObject(ent2);

	setDragLook(true);


	// register for input events
	addInputListener(this);

	//OgreBites::Event evt;

	//evt.type = OgreBites::KEYDOWN;
	//evt.key.keysym.sym = OgreBites::SDLK_ESCAPE; //BUTTON_LEFT;
	//evt.key.keysym.mod = 0;
	//evt.key.repeat = 1;
	//evt.key.type = OgreBites::KEYDOWN;

	//this->_fireInputEvent(evt, 0);
	//ApplicationContext::setup();
	//setWindowGrab();

}



