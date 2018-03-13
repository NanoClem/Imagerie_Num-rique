#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osgGA/NodeTrackerManipulator>
#include <osg/PositionAttitudeTransform>
#include <osg/LightSource>
#include "EventManage.hpp"


int main()
{
    osgViewer::Viewer viewer;
    osg::Group *scene = new osg::Group;


    //Boîte de dimension 2x3x4
    osg::Geode *boiteGeode = new osg::Geode();
    boiteGeode->setName("une boite");
    osg::Box *boite = new osg::Box(osg::Vec3(1, 0, 0), 2,3,4);
    osg::PositionAttitudeTransform *boiteTransform = new osg::PositionAttitudeTransform();
    osg::ShapeDrawable *boiteDrawable = new osg::ShapeDrawable(boite);
    osg::Material *boiteMat = new osg::Material;

    boiteTransform->setPosition(osg::Vec3(0,0,0));
    boiteTransform->setScale(osg::Vec3(1, 1, 1));                                                       //coef multiplicateurs
    boiteTransform->setAttitude(osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(0.0, 0.0, 1.0)));

    boiteGeode->addDrawable(boiteDrawable);
    boiteMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.0, 0.0, 1.0));
    boiteMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.0, 0.0, 1.0));
    boiteMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
    boiteMat->setShininess(osg::Material::FRONT_AND_BACK, 64);
    boiteDrawable->getOrCreateStateSet()->setAttributeAndModes(boiteMat);


    //Sphère de rayon 1
    osg::Geode *sphereGeode = new osg::Geode();
    sphereGeode->setName("une sphere");
    osg::Sphere *sphere = new osg::Sphere( osg::Vec3(0,0,0), 1.0 );
    osg::PositionAttitudeTransform *sphereTransform = new osg::PositionAttitudeTransform();
    osg::ShapeDrawable *sphereDrawable = new osg::ShapeDrawable(sphere);
    osg::Material* sphereMat = new osg::Material;

    sphereTransform->setPosition(osg::Vec3(0,0,0));
    sphereTransform->setScale(osg::Vec3(1, 1, 1));                                                       //coef multiplicateurs
    sphereTransform->setAttitude(osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(0.0, 0.0, 1.0)));

    sphereGeode->addDrawable(sphereDrawable);
    sphereMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.5, 0.0, 1.0));
    sphereMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.9, 0.0, 1.0));
    sphereMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
    sphereMat->setShininess(osg::Material::FRONT_AND_BACK, 64);
    sphereDrawable->getOrCreateStateSet()->setAttributeAndModes(sphereMat);


    //Cone de rayon 1 et de hauteur 2
    osg::Geode *coneGeode = new osg::Geode();
    coneGeode->setName("un cone");
    osg::Cone *cone = new osg::Cone( osg::Vec3(1, 0, 2), 1, 2);
    osg::PositionAttitudeTransform *coneTransform = new osg::PositionAttitudeTransform();
    osg::ShapeDrawable *coneDrawable = new osg::ShapeDrawable(cone);
    osg::Material* coneMat = new osg::Material;

    coneTransform->setPosition(osg::Vec3(0,0,0));
    coneTransform->setScale(osg::Vec3(1, 1, 1));                                                       //coef multiplicateurs
    coneTransform->setAttitude(osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(0.0, 0.0, 1.0)));

    coneGeode->addDrawable(coneDrawable);
    coneMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.0, 0.5, 1.0));
    coneMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.0, 0.9, 1.0));
    coneMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
    coneMat->setShininess(osg::Material::FRONT_AND_BACK, 64);
    coneDrawable->getOrCreateStateSet()->setAttributeAndModes(coneMat);



    //REGLAGES DE LA LUMIERE

    osg::Group *lumiere = new osg::Group;  //Noeud pour utiliser plusieurs lumières
    scene->addChild(lumiere);

    //Lumière directionnelle
    osg::ref_ptr<osg::LightSource> dirLumiere = new osg::LightSource;
    dirLumiere->getLight()->setLightNum(1); //GL_LIGHT1
    dirLumiere->getLight()->setPosition(osg::Vec4(1, -1, 1, 0));                // 0 = directionnelle
    dirLumiere->getLight()->setAmbient(osg::Vec4(0.4, 0.2, 0.3, 1.0));
    dirLumiere->getLight()->setDiffuse(osg::Vec4(0.8, 0.4, 0.6, 1.0));
    dirLumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

    lumiere->addChild(dirLumiere.get());


    //Lumière ponctuelle
    osg::ref_ptr<osg::LightSource> ponctLumiere = new osg::LightSource;
    ponctLumiere->getLight()->setLightNum(2);   //GL_LIGHT2
    ponctLumiere->getLight()->setPosition(osg::Vec4(1, -1, 1, 1));              // 1 = ponctuelle
    ponctLumiere->getLight()->setAmbient(osg::Vec4(0.4, 0.2, 0.3, 1.0));
    ponctLumiere->getLight()->setDiffuse(osg::Vec4(0.8, 0.4, 0.6, 1.0));
    ponctLumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

    lumiere->addChild(ponctLumiere.get());


    //Etat de la lumière
    osg::StateSet *state = scene->getOrCreateStateSet();
    state->setMode( GL_LIGHT0, osg::StateAttribute::OFF );                      //Lumière éteinte
    state->setMode( GL_LIGHT1, osg::StateAttribute::ON );
    state->setMode( GL_LIGHT2, osg::StateAttribute::OFF );


    boiteTransform->addChild(boiteGeode);
    scene->addChild(boiteTransform);

    sphereTransform->addChild(sphereGeode);
    scene->addChild(sphereGeode);

    coneTransform->addChild(coneGeode);
    scene->addChild(coneGeode);


    //Réglages de la caméra
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manip
        = new osgGA::NodeTrackerManipulator;
    manip->setTrackNode(coneGeode);                                             //caméra centrée sur le cone
    manip->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER);
    viewer.setCameraManipulator(manip.get());


    //Gestion des évènements du clavier
    osg::ref_ptr<EventManage> gestionnaire = new EventManage(scene);
    viewer.addEventHandler(gestionnaire.get());


    //Réglages de la fenetre
    osg::DisplaySettings::instance()->setNumMultiSamples(4);                    //Antialiasing
    viewer.setUpViewInWindow( 100, 50, 800, 600 );
    viewer.getCamera()->setClearColor( osg::Vec4( 0.9, 0.9, 0.9, 0.5 ) );
    osgViewer::Viewer::Windows fenetres;
    viewer.getWindows(fenetres);
    fenetres[0]->setWindowName("La baleine");

    viewer.setSceneData(scene);
    return viewer.run();
}
