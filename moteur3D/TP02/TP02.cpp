#include <osgViewer/Viewer> 


int main()
{
  osgViewer::Viewer viewer;

  //Réglages de la fenetre
  osgViewer::Viewer::Windows fenetres;
  viewer.getWindows(fenetres);
  fenetres[0]->setWindowName("Armée de vaches");
  viewer.setUpViewInWindow(100, 50, 800, 600);

  return viewer.run();
}
