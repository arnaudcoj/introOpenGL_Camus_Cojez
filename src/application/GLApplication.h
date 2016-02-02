#ifndef GLAPPLICATION_H
#define GLAPPLICATION_H


#include "GLWidget.h"
#include "Tools.h"

#include <string>
#include <cmath>

class GLApplication : public GLWidget {
  Q_OBJECT  
public:
  GLApplication();
  virtual ~GLApplication();


  /** ***** **/
  /** GLApplication must implement these methods : */
  virtual void initialize();
  virtual void update();
  virtual void draw();
  virtual void resize(int width,int height);
  /** ***** **/
  virtual void leftPanel(int i, const std::string &s);
  virtual QSize sizeHint() const {return QSize(1000,1000);}
  /** ***** **/
  GLuint initProgram(const std::string &filename);
  void initTriangleBuffer();
  void initTriangleVAO();
  void initTexture();
  void initStrip(int nbSlice,float xmin,float xmax,float ymin,float ymax);
  void initRing(int nbSlice,float r0,float r1);
  void initRingText(int nbSlice,float r0,float r1);
  void initRingText2(int nbSlice,float r0,float r1);
  void initRingText3(int nbSlice,float r0,float r1);

private:
  std::vector<float> _trianglePosition;
  std::vector<float> _triangleColor;
  std::vector<float> _triangleTexCoord;
  std::vector<unsigned int> _elementData;

  bool _animation;
  float _coeff;
  bool _ascendingCoeff;

  GLuint _trianglePositionBuffer;
  GLuint _triangleColorBuffer;
  GLuint _triangleTexCoordBuffer;
  GLuint _elementBuffer;

  GLuint _triangleVAO;
  GLuint _shader0;
  GLuint _textureId;



};

//utils
void addPointToVector(std::vector<float> &vect, float x, float y, float z = 0.);
void addColorToVector(std::vector<float> &vect, float r, float g, float b, float a = 1.);
void addPointTextToVector(std::vector<float> &vect, float x, float y);

#endif // GLAPPLICATION_H

