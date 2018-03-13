#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osgDB/ReadFile>



int main()
{
    osgViewer::Viewer viewer;
    osg::Group *scene = new osg::Group;

    //Noeud vache
    osg::Node *vache = osgDB::readNodeFile("cow_high.3ds");
    scene->addChild(vache);

    //Réglages de la fenetre
    osg::DisplaySettings::instance()->setNumMultiSamples(4);  //Antialiasing
    viewer.setUpViewInWindow( 100, 50, 800, 600 );
    viewer.getCamera()->setClearColor( osg::Vec4( 0.9, 0.9, 0.9, 0.5 ) );
    osgViewer::Viewer::Windows fenetres;
    viewer.getWindows(fenetres);
    fenetres[0]->setWindowName("La baleine");


    viewer.setSceneData(scene);
    return viewer.run();
}
