#include <stdlib.h>
#include <time.h>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/Material>
#include <osg/TexMat>
#include <osg/PositionAttitudeTransform>
// #include "EventManage.hpp"

using namespace std;

//Compilation :
// g++ -o prog TP4.cpp -losg -losgViewer -losgGA -losgDB -losgUtil




osg::Node *creation_terrain(string img, string texture)
{
    osg::HeightField *terrain = new osg::HeightField();
    osg::Image *hauteurTerrain = osgDB::readImageFile(img);

    terrain->allocate(hauteurTerrain->s(), hauteurTerrain->t());
    terrain->setOrigin( osg::Vec3(-hauteurTerrain->s()/2,
                                  -hauteurTerrain->t()/2,
                                  0) );
    terrain->setXInterval(10.0f);
    terrain->setYInterval(10.0f);

    for(size_t r = 0; r < terrain->getNumRows(); r++)
        for(size_t c = 0; c < terrain->getNumColumns(); c++)
        {
            terrain->setHeight(c, r, ((*hauteurTerrain->data(c,r))/255.0f)*300.0f);
        }

    //Configuration du terrain
    osg::ShapeDrawable *fieldDrawable = new osg::ShapeDrawable(terrain);
    osg::Material *mat = new osg::Material;
    mat->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.5, 0.5, 1.0));
    mat->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.9, 0.9, 1.0));
    mat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.1, 0.1, 0.1, 1.0));

    //Configuration de la texture du terrain
    osg::Texture2D *tex = new osg::Texture2D(osgDB::readImageFile(texture));
    tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR_MIPMAP_LINEAR);
    tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
    tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
    tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

    //Pouvoir modifier les coordonnées de texture
    //ici on la réptère 10 fois
    osg::Matrix matrix;
    matrix.makeScale(osg::Vec3(10, 10, 1.0));
    osg::ref_ptr<osg::TexMat> matTexture = new osg::TexMat;
    matTexture->setMatrix(matrix);

    osg::Geode *geode = new osg::Geode();
    geode->getOrCreateStateSet()->setTextureAttributeAndModes(0,
        matTexture.get(), osg::StateAttribute::ON);
    geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex);
    geode->addDrawable(fieldDrawable);

    return geode;
}


//Calcule la position et la normale d'un point à la surface du terrain
//en calculant l'intersection d'un segment de droite avec le terrain
bool intersection_terrain(float x, float y,
osg::Node *terrain,
osg::Vec3& position,
osg::Vec3& normale)
{
    //ligne de longueur 1000
    osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
    new osgUtil::LineSegmentIntersector(osg::Vec3(x,y,1000), osg::Vec3(x, y,-1000));

    osgUtil::IntersectionVisitor iv(intersector.get());
    terrain->accept(iv);

    if (intersector->containsIntersections())
    {
        osgUtil::LineSegmentIntersector::Intersections& intersections = intersector->getIntersections();
        // Le segment étant vertical, on prend la première (et à priori unique) intersection trouvée
        const osgUtil::LineSegmentIntersector::Intersection& intersection = *(intersections.begin());
        position = intersection.getWorldIntersectPoint();
        normale = intersection.getWorldIntersectNormal();
        return true;
    }
    return false;
}



//Créé une forêt
osg::Group *creation_foret(osg::Node *terrain, float xsize, float ysize, int nbArbres, string texture)
{
    osg::Group *foret = new osg::Group;                     //Noeud racine foret

    //texture des arbres
    osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
    tex->setImage(osgDB::readImageFile(texture));
    tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
    tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

    //Objet géométrique arbre
    osg::Geometry *arbre = osg::createTexturedQuadGeometry( osg::Vec3(0.0f, 0.0f, 0.0f),           //coin de départ
                                                            osg::Vec3(50.0f, 0.0f, 0.0f),            //largeur
                                                            osg::Vec3(0.0f, 0.0f, 100.0f),           //hauteur
                                                            0.0f, 0.0f, 1.0f, 1.0f);                //coords de texture
    arbre->getOrCreateStateSet()->setTextureAttributeAndModes(0.0f, tex.get());
    arbre->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
    // On ajoute le quad dans le TRANSPARENT BIN, une collection d'objets transparents,
    // pour qu'ils soient triés selon la profondeur et affichés du plus éloigné au plus proche
    arbre->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    //Billboard
    osg::Billboard *billboard = new osg::Billboard;
    billboard->setMode(osg::Billboard::AXIAL_ROT);
    billboard->addDrawable(arbre);


    float xrand, yrand, rotation;
    xsize += 1.0f;                        //car rand() % nb renvoie entre [0;nb[
    ysize += 1.0f;
    srand( time(NULL) );                  //initialisation de rand()

    for(size_t i = 0; i < nbArbres; i++)
    {
        xrand    = rand() % int(xsize);
        yrand    = rand() % int(ysize);
        rotation = rand() % 359;        //roation entre 0° et 359°

        //Intersections avec le terrain
        osg::Vec3 position, normale;
        intersection_terrain(xrand, yrand, terrain, position, normale);

        osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform();
        transform->setPosition(position);
        transform->setScale(osg::Vec3(1, 1, 1));
        transform->setAttitude(osg::Quat(osg::DegreesToRadians(rotation),
        osg::Vec3(0.0, 0.0, 1.0)));

        transform->addChild(billboard);
        foret->addChild(transform);
    }

    return foret;
}



//Deuxième manière de créer une forêt d'abres
//la position des arbres est déterminée en fonction d'une image en niveaux de gris
//Si le pixel est noir, on n'ajoute pas d'abres, et inversement s'il est blanc
osg::Group *creation_foret_img(osg::Node *terrain, string imgHeightTree, string texture)
{
    osg::Group *foret = new osg::Group;
    osg::Image *heightTree = osgDB::readImageFile(imgHeightTree);

    //texture des arbres
    osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
    tex->setImage(osgDB::readImageFile(texture));
    tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
    tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

    //Objet géométrique arbre
    osg::Geometry *arbre = osg::createTexturedQuadGeometry( osg::Vec3(0.0f, 0.0f, 0.0f),           //coin de départ
                                                            osg::Vec3(50.0f, 0.0f, 0.0f),            //largeur
                                                            osg::Vec3(0.0f, 0.0f, 100.0f),           //hauteur
                                                            0.0f, 0.0f, 1.0f, 1.0f);                //coords de texture
    arbre->getOrCreateStateSet()->setTextureAttributeAndModes(0.0f, tex.get());
    arbre->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
    // On ajoute le quad dans le TRANSPARENT BIN, une collection d'objets transparents,
    // pour qu'ils soient triés selon la profondeur et affichés du plus éloigné au plus proche
    arbre->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    //Billboard
    osg::Billboard *billboard = new osg::Billboard;
    billboard->setMode(osg::Billboard::AXIAL_ROT);
    billboard->addDrawable(arbre);


    for(size_t x = 0; x < heightTree->s(); x++)
        for(size_t y = 0; y < heightTree->t(); y++)
        {
            if( *heightTree->data(x,y) != 0 )
            {
                //Intersections avec le terrain
                osg::Vec3 position, normale;
                intersection_terrain(x, y, terrain, position, normale);

                osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform();
                transform->setPosition(position);
                transform->setScale(osg::Vec3(1, 1, 1));
                // transform->setAttitude(osg::Quat(osg::DegreesToRadians(rotation),
                // osg::Vec3(0.0, 0.0, 1.0)));

                transform->addChild(billboard);
                foret->addChild(transform);
            }
        }

    return foret;
}




//Créé un tank et l'oriente selon la normale du point sur le terrain
osg::Group *creation_tank(osg::Node *terrain, string tankName)
{
    osg::Group *finalTank = new osg::Group;
    osg::Node *tank = osgDB::readNodeFile(tankName);
    osg::Vec3 position, normale;

    float xrand, yrand;
    srand( time(NULL) );
    xrand    = rand() % int(1000);
    yrand    = rand() % int(1000);

    //Calcul de la position et de la normale d'un point du terrain
    intersection_terrain(xrand, yrand, terrain, position, normale);

    //Rotation selon la normale
    osg::Quat rotation;
    rotation.makeRotate(osg::Vec3f(0, 0, 1), normale);

    //On positionne le tank en ce point à la surface du terrain
    osg::PositionAttitudeTransform* transform = new osg::PositionAttitudeTransform();
    transform->setPosition(position);
    transform->setAttitude(rotation);;
    transform->setScale(osg::Vec3(15.0, 15.0, 15.0));
    transform->addChild(tank);

    finalTank->addChild(transform);
    return finalTank;
}




//MAIN

int main()
{
    osgViewer::Viewer viewer;
    osg::Group *scene = new osg::Group;

    //Réglages de la fenêtre
    viewer.setUpViewInWindow( 100, 50, 800, 600 );
    osgViewer::Viewer::Windows fenetres;
    viewer.getWindows(fenetres);
    fenetres[0]->setWindowName("Tank war");

    //Gestion de la hauteur du terrain
    osg::Node *terrain = creation_terrain("terrain.tga", "herbe.tga");
    scene->addChild(terrain);

    //Gestion de la forêt
    // osg::Group *foret = creation_foret(terrain, -1100.0f, 1100.0f, 100, "arbre.tga");
    // scene->addChild(foret);
    osg::Group *foret_img = creation_foret_img(terrain, "foret.tga", "arbre.tga");
    scene->addChild(foret_img);

    //Gestion du tank
    osg::Node *tank = creation_tank(terrain, "t72-tank_des.flt");
    scene->addChild(tank);

    viewer.setSceneData(scene);
    return viewer.run();
}
