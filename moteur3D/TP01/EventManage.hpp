#include <osgGA/GUIEventHandler>


class EventManage : public osgGA::GUIEventHandler
{
    private :
        osg::ref_ptr<osg::Group> scene;

    public :
        EventManage(osg::ref_ptr<osg::Group> _scene);
        virtual bool handle( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa );
};



EventManage::EventManage(osg::ref_ptr<osg::Group> _scene)
    :scene(_scene)
{}


bool EventManage::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    switch(ea.getEventType())
    {
        case osgGA::GUIEventAdapter::KEYDOWN :  // appui sur une touche
            switch(ea.getKey())
            {
                case '&' :
                    scene->getOrCreateStateSet()->setMode( GL_LIGHT0, osg::StateAttribute::ON );
                    break;

                case 'a' :
                    scene->getOrCreateStateSet()->setMode( GL_LIGHT0, osg::StateAttribute::OFF );
                    break;
            }
    }
    return false;
}
