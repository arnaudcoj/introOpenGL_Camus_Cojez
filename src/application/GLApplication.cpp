#include "GLApplication.h"

#include <iostream>

using namespace std;

static const float PI = 3.14159;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() : _animation(false), _coeff(1.0){

    /*
      _trianglePosition = {
        -0.8,-0.5,0.0, // vertex 0
        -0.2,-0.5,0.0, // 1
        -0.5,0.5,0.0,  // 2

        0.2,0.5,0.0,  // 3
        0.8,0.5,0.0,  // 4
        0.5,-0.5,0.0  // 5
      };
    */

    /*
     _trianglePosition = {
       -0.8,-0.5,0.0, // vertex 0 anciennement vertex 0
       0.8,0.5,0.0, // 1 anciennement 4
       -0.5,0.5,0.0, // 2 anciennement 2
       -0.2,-0.5,0.0, // 3 anciennement 1
       0.5,-0.5,0.0, // 4 anciennement 5
       0.2,0.5,0.0 // 5 anciennement 3
    };
*/
/*
     _trianglePosition = { -0.8,-0.8,0.0,
                           0.8,0.8,0.0,
                           0.0,0.2,0.0,
                           -0.8,0.8,0.0,
                           0.8,-0.8,0.0
                         };


     _elementData = {
         0,
         3,
         2,
         2,
         1,
         4
    };

   _triangleColor = {
     0.3,0,0.6,1,
     0.3,0,0.6,1,
     0.0,0.9,0.0,1,

     0.0,0.5,0.6,1,
     0.0,0.5,0.6,1,
     0.9,0.0,0.0,1
   };

*/

/*
  _trianglePosition = {
     -0.8,-0.8,0.0,
     -0.6,0.8,0.0,
     -0.4,-0.6,0.0,
     -0.2,0.6,0.0,
     0.0,-0.8,0.0,
     0.2,0.8,0.0,
     0.4,-0.6,0.0,
     0.6,0.6,0.0,
     0.8,-0.8,0.0
 };
 */

    /*
    _trianglePosition = {
       -0.8,-0.8,0.0,
       -0.8,0.8,0.0,
       -0.4,-0.8,0.0,
       -0.4,0.8,0.0,
       0.0,-0.8,0.0,
       0.0,0.8,0.0,
       0.4,-0.8,0.0,
       0.4,0.8,0.0
   };

 // tous les sommets à rouge :
 _triangleColor.clear();
 for(unsigned int i=0;i<8;++i) {
     _triangleColor.push_back(1);
     _triangleColor.push_back(0);
     _triangleColor.push_back(0);
     _triangleColor.push_back(1);
 }
   */

//    initStrip(20, -0.8, 0.8, -0.8, 0.8);

//    initRing(50, 0.2, 0.8);

   _trianglePosition = {

       // rectangle tracé avec TRIANGLE_STRIP
       -0.6,-0.8,0,
       -0.6,0.8,0,
       0.6,-0.8,0,
       0.6,0.8,0
   };
   _triangleColor = {
       // tous les sommets en rouge
       1,0,0,1,
       1,0,0,1,
       1,0,0,1,
       1,0,0,1,
   };

   _triangleTexCoord = {
       // coordonnées de texture en chaque sommet
       0,1,
       0,0,
       1,1,
       1,0
   };
}




/** ********************************************************************** **/
void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL
  glClearColor(1,1,1,1);

  glLineWidth(2.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


  _shader0 = initProgram("simple");


  initTriangleBuffer();
  initTriangleVAO();
  initTexture();


}

void GLApplication::resize(int width,int height) {
  // appelée à chaque dimensionnement du widget OpenGL
  // (inclus l'ouverture de la fenêtre)
  // => réglages liés à la taille de la fenêtre
  glViewport(0,0,width,height);
  // ...
}

void GLApplication::update() {
  // appelée toutes les 20ms (60Hz)
  // => mettre à jour les données de l'application
  // avant l'affichage de la prochaine image (animation)
  // ...

  //Q24
    if(_animation) {
        if(_coeff >= 1.)
            _ascendingCoeff = false;
        else if (_coeff <= 0.)
            _ascendingCoeff = true;

        if(_ascendingCoeff)
          _coeff += 0.1;
        else
          _coeff -= 0.1;
      }

}

void GLApplication::draw() {
  // appelée après chaque update
  // => tracer toute l'image
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(_shader0);

  glActiveTexture(GL_TEXTURE0); // on travaille avec l'unité de texture 0
  glBindTexture(GL_TEXTURE_2D,_textureId); // l'unité de texture 0 correspond à la texture _textureId // (le fragment shader manipule des unités de textures et non les identifiants de texture directement)

  // dans l'instruction suivante, _textureId correspond à l'image "lagoon.jpg"; cf GLApplication::initTexture pour l'initialisation de _textureId
  glUniform1f(glGetUniformLocation(_shader0,"texture"),0); // on affecte la valeur du sampler2D du fragment shader à l'unité de texture 0.

  glBindVertexArray(_triangleVAO);

  glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);
  glBindVertexArray(0);
  glUseProgram(0);


  snapshot(); // capture opengl window if requested
}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
  cout << "GLApplication : button clicked " << i << " " << s << endl;
  /*
  switch (i) {
    case 0:menu0();break;
    case 1:menu1();break;
  }
  */
}




/** *********************************************************** **/
GLuint GLApplication::initProgram(const std::string &filename) {
  GLuint program;
  int infoLength; // for message error

  string vertexSource=p3d::readTextFile(filename+".vert");
  string fragmentSource=p3d::readTextFile(filename+".frag");

  program=glCreateProgram();
  GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
  glAttachShader(program,vertexShader);
  glAttachShader(program,fragmentShader);

  const char *source;
  source=vertexSource.c_str();
  glShaderSource(vertexShader,1,&source,NULL);
  source=fragmentSource.c_str();
  glShaderSource(fragmentShader,1,&source,NULL);

  GLint ok;
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&ok);
  if (!ok) {
    glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&infoLength);
    cout << "=============================" << endl;
    cout << "GLSL Error : " << endl;
    char *info=new char[infoLength];
    glGetShaderInfoLog(vertexShader,infoLength,NULL,info);
    cout << info;
    cout << endl;
    delete info;
    throw ErrorD("Vertex Shader compilation error");
  }

  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&ok);
  if (!ok) {
    glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&infoLength);
    cout << "=============================" << endl;
    cout << "GLSL Error : " << endl;
    char *info=new char[infoLength];
    glGetShaderInfoLog(fragmentShader,infoLength,NULL,info);
    cout << info;
    cout << endl;
    delete info;
    throw ErrorD("Vertex Shader compilation error");
  }

  glBindAttribLocation(program,0,"position");
  glBindAttribLocation(program,1,"color");
  glBindAttribLocation(program,2,"texCoord");



  glLinkProgram(program);
  glGetProgramiv(program,GL_LINK_STATUS,&ok);
  if (!ok) {
    char *info=new char[infoLength];
    glGetProgramInfoLog(program,infoLength,NULL,info);
    cout << "Info Log :" << endl;
    cout << info;
    cout << endl;
    delete info;
    throw ErrorD("Program Shader : link error (varyings ok ?)");
  }

  return program;
}


void GLApplication::initTexture() {
    QImage img;
    img.load("../media/lagoon.jpg");
    img=img.convertToFormat(QImage::Format_ARGB32).mirrored();

    glGenTextures(1,&_textureId);
    glBindTexture(GL_TEXTURE_2D,_textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width(),img.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.bits());



    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}


void GLApplication::initTriangleBuffer() {

  glGenBuffers(1,&_trianglePositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
  glBufferData(GL_ARRAY_BUFFER,_trianglePosition.size()*sizeof(float),_trianglePosition.data(),GL_STATIC_DRAW);


  glGenBuffers(1,&_triangleColorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
  glBufferData(GL_ARRAY_BUFFER,_triangleColor.size()*sizeof(float),_triangleColor.data(),GL_STATIC_DRAW);

   glGenBuffers(1,&_elementBuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER,_elementData.size()*sizeof(unsigned int),_elementData.data(),GL_STATIC_DRAW);

   glGenBuffers(1,&_triangleTexCoordBuffer);
   glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
   glBufferData(GL_ARRAY_BUFFER,_triangleTexCoord.size()*sizeof(float),_triangleTexCoord.data(),GL_STATIC_DRAW);
}


void GLApplication::initTriangleVAO() {
  glGenVertexArrays(1,&_triangleVAO);
  glBindVertexArray(_triangleVAO);

  //position
  glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

  //color
  glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
  glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);

  //element
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
  // pas besoin ! glVertexAttribPointer(2,1,GL_INT,GL_FALSE,0,0);


  //texture
  glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);


  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  //pas besoin ! glEnableVertexAttribArray(2);


  glBindVertexArray(0);
}


void GLApplication::initStrip(int nbSlice,float xmin,float xmax,float ymin,float ymax) {
    int i;
    float sliceSize = (xmax - xmin) / nbSlice;

    _trianglePosition.clear();

    // point en bas à gauche
    addPointToVector(_trianglePosition, xmin, ymin);
    addColorToVector(_triangleColor, 0., 0., 0.);


    for(i = 0; i < nbSlice; i++) {

        // tranche : point en haut à gauche
        addPointToVector(_trianglePosition, xmin + i * sliceSize, ymax);
        addColorToVector(_triangleColor, 0., 0., 1. - ( (float) i / nbSlice));

        // tranche : point en bas à droite
        addPointToVector(_trianglePosition, xmin + (i + 1) * sliceSize, ymin);
        addColorToVector(_triangleColor, 0., ((float) i / nbSlice), 0.);
    }

    // point en haut à droite
    addPointToVector(_trianglePosition, xmax, ymax);
    addColorToVector(_triangleColor, 0, 0, 0);

}

void GLApplication::initRing(int nbSlice,float r0,float r1) {
    int i;
    float angleDiff = 2 * PI / nbSlice;
    float angle = 0.;

    // point avec angle = 0 (cercle interieur)
    addPointToVector(_trianglePosition, r0, 0.);
    addColorToVector(_triangleColor, 0., 0., 0.);

    for(i = 0; i < nbSlice; i++) {

        // point cercle exterieur
        addPointToVector(_trianglePosition, r1 * std::cos(angle),  r1 * std::sin(angle));
        addColorToVector(_triangleColor, 0., 0., 1. - ( (float) i / nbSlice));

        angle += angleDiff;

        // point cercle interieur
        addPointToVector(_trianglePosition,  r0 * std::cos(angle), r0 * std::sin(angle));
        addColorToVector(_triangleColor, 0., ((float) i / nbSlice), 0.);
    }

    // point avec angle = 2*PI (cercle exterieur)
    addPointToVector(_trianglePosition, r1, 0.);
    addColorToVector(_triangleColor, 0., 0., 0.);


}

/*
 * Ajoute le x, y, z (0 par défaut) dans un vector
 * */
void addPointToVector(std::vector<float> &vect, float x, float y, float z) {
    vect.push_back(x);
    vect.push_back(y);
    vect.push_back(z);
}

/*
 * Ajoute le r, g, b, a (1 par défaut) dans un vector
 * */
void addColorToVector(std::vector<float> &vect, float r, float g, float b, float a) {
    vect.push_back(r);
    vect.push_back(g);
    vect.push_back(b);
    vect.push_back(a);
}
