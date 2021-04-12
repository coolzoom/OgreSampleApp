# OgreSampleApp
OgreSampleApp
- download sdk
- run cmake and compile
- https://ogrecave.github.io/ogre/api/latest/setup.html
- https://blog.csdn.net/qq_28584889/article/details/97765623

- copy cfg file to the destination


below is not needed unless error occur
- set system env OGRE_DIR C:\Users\Administrator\Downloads\ogre-sdk-master2-vc15-x64\Cmake
- change cmakelist MY_OGRE_DIR, run cmake
- compile in release mode， copy necessary dll from SDK to bin folder


# Tips
- scnMgr->addRenderQueueListener(mOverlaySystem); //to update the gui otherwise tray wont show up https://forums.ogre3d.org/viewtopic.php?t=94386
- setWindowGrab(); // is to grab the windows mouser when mouser hover on the OGRE game window
- scnMgr->createEntity(Ogre::SceneManager::PrefabType::PT_SPHERE);
- setDragLook(true); is drag move