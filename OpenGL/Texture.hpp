
class Texture {

  private:
    GLuint id;
    int width, height, comp;
    bool mimap = false;

  public:
    Texture(GLuint _id, int _width, int _height, int _comp);
    ~Texture();
    inline int getWidth()  {return width;}
    inline int getHeight() {return height;}
    inline int getComp()   {return comp;}
    inline void setWidth(int _width)   {width = _width;}
    inline void setHeight(int _height) {height = _height;}
    inline void setComp(int _comp)     {comp = _comp;}

    bool load(char *filename);
    void use();
    void define_filter(GLint min_mode, GLint mag_mode);
    void define_loop(GLint mode_axe_s, GLint mode_axe_t);
    void define_melting(GLint mode);
};
