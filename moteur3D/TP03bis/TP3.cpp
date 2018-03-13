#include <stdlib.h>
#include <time.h>
#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Switch>
#include <osg/Camera>
#include <osg/Fog>
#include <osgParticle/PrecipitationEffect>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include "EventManage.hpp"



osg::Group *creation_troupeau(int nbVache, float xsize, float ysize)
{
    osg::Group *troupeau  = new osg::Group;
    osg::Node *vache_low  = osgDB::readNodeFile("cow_low.3ds");
    osg::Node *vache_mid  = osgDB::readNodeFile("cow_mid.3ds");
    osg::Node *vache_high = osgDB::readNodeFile("cow_high.3ds");

    osg::LOD *vache_lod   = new osg::LOD;
    vache_lod->setRangeMode(osg::LOD::DISTANCE_FROM_EYE_POINT);
    vache_lod->addChild(vache_high, 0, 10);
    vache_lod->addChild(vache_mid, 10, 20);
    vache_lod->addChild(vache_low, 20, 1000);

    float xrand, yrand, rotation;
    xsize += 1.0f;                        //car rand() % nb renvoie entre [0;nb[
    ysize += 1.0f;
    srand( time(NULL) );                  //initialisation de rand()
    for(size_t i = 0; i < nbVache; ++i)
    {
        xrand    = rand() % int(xsize);
        yrand    = rand() % int(ysize);
        rotation = rand() % 360;        //roation entre 0° et 359°
        osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform();
        transform->setPosition(osg::Vec3(xrand, yrand, 0 ));
        transform->setScale(osg::Vec3(1, 1, 1));
        transform->setAttitude(osg::Quat(osg::DegreesToRadians(rotation),
        osg::Vec3(0.0, 0.0, 1.0)));

        transform->addChild(vache_lod);
        troupeau->addChild(transform);
    }

    return troupeau;
}



osg::Node *creation_sol(float xsize, float ysize)
{
    //Configuration de la texture du sol
    osg::ref_ptr<osg::Texture2D> texture_sol = new osg::Texture2D;
    texture_sol-> setImage(osgDB::readImageFile("herbe.jpg"));
    texture_sol-> setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texture_sol-> setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );
    texture_sol-> setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
    texture_sol-> setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );

    //Création du quadrilatère
    osg::ref_ptr<osg::Geometry> quad =
    osg::createTexturedQuadGeometry(
        osg::Vec3(-10.0f, -20.0f, 0.0f),
        osg::Vec3(xsize, ysize, 0.0f),
        osg::Vec3(0.0, 50.0, 0.0),
        0.0f, 0.0f, 1.0f, 1.0f
    );
    quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture_sol.get());
    quad->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    osg::Geode *geode = new osg::Geode;
    geode->addDrawable(quad);
    return geode;
}



osg::Fog *brouillard_lineaire(float start, float end)
{
    osg::Fog *pFog = new osg::Fog();
    pFog->setColor(osg::Vec4(0.7, 0.7, 0.7, 1.0));
    pFog->setMode(osg::Fog::LINEAR);
    pFog->setStart(start);
    pFog->setEnd(end);

    return pFog;
}


osg::Fog *brouillard_exponentiel(float density)
{
    osg::Fog *fog = new osg::Fog();
    fog->setColor(osg::Vec4(0.7, 0.7, 0.7, 1.0));
    fog->setMode(osg::Fog::EXP2);
    fog->setDensity(0.05f);

    return fog;
}



osgParticle::PrecipitationEffect *ajouter_pluie(osg::Vec3 vent, float vitesse)
{
    osgParticle::PrecipitationEffect *pluie = new osgParticle::PrecipitationEffect;
    pluie->setWind(vent);
    pluie->setParticleSpeed(vitesse);
    pluie->rain(0.2f);

    return pluie;
}



osg::ref_ptr<osgShadow::ShadowedScene> shadowedScene(osg::Group *scene, osg::ref_ptr<osg::LightSource> lumiere)
{
    osg::ref_ptr<osgShadow::ShadowedScene> shadowScene
    = new osgShadow::ShadowedScene;
    osg::ref_ptr<osgShadow::ShadowMap> sm
    = new osgShadow::ShadowMap;
    shadowScene->setShadowTechnique(sm.get());
    shadowScene->addChild(lumiere.get());
    shadowScene->addChild(scene);

    return shadowScene;
}




// void Enable_cow(osg::Node *vache)
// {
//     osg::Switch *switch_vache = new osg::Switch;
//     switch_vache->addChld(vache.get());
//
//     switch (var)
//     {
//     case 'a':
//         switchNode->setSingleChildOn(1);
//         break;
//
//     case 'z':viewer.setSceneData(shad    = new osgShadow::ShadowedScene;
//         switchNode->setSingleChildOff(1);
//         break:
//     }
// }




int main()
{
    osgViewer::Viewer viewer;
    osg::Group *scene = new osg::Group;
    viewer.addEventHandler(new osgViewer::StatsHandler);      //Affichage des stats en appuyant plusieurs fois sur "s"

    //Réglages de la fenêtre
    viewer.setUpViewInWindow( 100, 50, 800, 600 );
    osgViewer::Viewer::Windows fenetres;
    viewer.getWindows(fenetres);
    fenetres[0]->setWindowName("L'attaque des vaches");

    //Creation du terrain
    osg::Node *sol = creation_sol(70, 20);
    scene->addChild(sol);

    //Creation du troupeau de vaches;
    osg::Group *troupeau = creation_troupeau(100, 50, 30);
    scene->addChild(troupeau);

    //Gestion du brouillard
    // osg::Fog *fog = brouillard_lineaire(10.0f, 20.0f);
    // // osg::Fog *fog = brouillard_exponentiel(0.05f);
    // scene->getOrCreateStateSet()->setAttribute(fog, osg::StateAttribute::ON);
    // scene->getOrCreateStateSet()->setMode(GL_FOG, osg::StateAttribute::ON);

    //Gestion de la pluie
    // osgParticle::PrecipitationEffect *pluie = ajouter_pluie(osg::Vec3(1.0f, 5.0f, 1.0f), 1.0f);
    // scene->addChild(pluie);


    //Gestion des évènements du clavier
    osg::ref_ptr<EventManage> gestionnaire = new EventManage(scene);
    viewer.addEventHandler(gestionnaire.get());



    //REGLAGES DE LA LUMIERE

    osg::Group *lumiere = new osg::Group;  //Noeud pour utiliser plusieurs lumières
    scene->addChild(lumiere);

    //Lumière directionnelle
    osg::ref_ptr<osg::LightSource> dirLumiere = new osg::LightSource;
    dirLumiere->getLight()->setLightNum(1); //GL_LIGHT1
    dirLumiere->getLight()->setPosition(osg::Vec4(1, -1, 1, 0));                // 0 = directosgShadow::ShadowedScene *shadowScene ionnelle
    dirLumiere->getLight()->setAmbient(osg::Vec4(0.4, 0.4, 0.4, 1.0));
    dirLumiere->getLight()->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));
    dirLumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

    lumiere->addChild(dirLumiere.get());


    //Lumière ponctuelle
    osg::ref_ptr<osg::LightSource> ponctLumiere = new osg::LightSource;
    ponctLumiere->getLight()->setLightNum(2);   //GL_LIGHT2
    ponctLumiere->getLight()->setPosition(osg::Vec4(1, -1, 1, 1));              // 1 = ponctuelle
    ponctLumiere->getLight()->setAmbient(osg::Vec4(0.4, 0.4, 0.4, 1.0));
    ponctLumiere->getLight()->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));
    ponctLumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

    lumiere->addChild(ponctLumiere.get());


    //Etat de la lumière
    osg::StateSet *state = scene->getOrCreateStateSet();
    state->setMode( GL_LIGHT0, osg::StateAttribute::OFF );                      //Lumière éteinte
    state->setMode( GL_LIGHT1, osg::StateAttribute::ON );
    state->setMode( GL_LIGHT2, osg::StateAttribute::OFF );


    //Gestion des ombres projetées
    osg::ref_ptr<osgShadow::ShadowedScene> shadowScene = shadowedScene(scene, dirLumiere);


    //Gestion des camera
    osg::ref_ptr<osg::Camera> myCam = new osg::Camera;
    myCam->setClearColor(osg::Vec4(0.0, 0.9, 0.9, 1));
    myCam->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
    myCam->setViewMatrixAsLookAt(
        osg::Vec3(0, -10, 10),
        osg::Vec3(0, 0, 0),
        osg::Vec3(0, 0, 1));


    viewer.setCamera(myCam);
    //viewer.setSceneData(scene);
    viewer.setSceneData(shadowScene);
    return viewer.run();
}
