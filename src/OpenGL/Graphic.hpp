#ifndef _GRAPHICS_H_
# define _GRAPHICS_H_

# include "IGraphics.hpp"
# include <GL/glut.h>
# include <GL/freeglut_ext.h>
# include "Camera.hpp"
# include <map>
# include <string>
# include <sstream>
# include <utility>

# define VIEW_FOV       120.0
# define FOV_ANGLE      40.0
# define COLOR_FLOAT(x)	(static_cast<float>(x) / 255.0)

struct		colorEntities
{
  colorEntities(GLfloat r, GLfloat g, GLfloat b) {
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    rgb[3] = 1.0;
  }
  GLfloat	rgb[4];
};

class Graphics : public IGraphics
{
public:
  Graphics();
  virtual ~Graphics();

  virtual bool create_window(const std::string &name, const int *, const int *);
  virtual void handleEvent(bool *key);
  virtual void clear();
  virtual void draw(int x, int y, int type, int dir);
  virtual void display_score(int score);
  virtual void update();
  virtual void destroyWindow();
  virtual void setKey(int index, bool value);
  virtual void updateDisplayMap();
  virtual void updateCam();
  virtual void init_cam();
  virtual void initColor();
  virtual void init_light();
  virtual void display_f_score(const std::string &, int, int);
  virtual void display_pause_msg();
  virtual void changeFirst();
  virtual void changeFollowSnake();
  std::map<unsigned char, Keypos>	getAssocitedKey() const;
  int		*getHeadPos();
  Camera	*getCam();
  void		create_plane();
  void		displayString(const char *score, int x, int y);
  void		setWinSize(int width, int height);
private:
  bool					_key[LAST];		// status des key
  int					_displayId;
  std::map<std::string, float>		_size;
  std::map<Entities, colorEntities *>	_color_entities;
  int					_pos[2];
  int					_headpos[2];
  int					_type;
  int					_dir;
  float					_eye[3];
  float					_vecdir[3];
  bool					_isFirst;
  bool					_followSnake;
  std::map<unsigned char, Keypos>	_associatedKey;
  Camera				*cam;
};

void		catchSpecialKey(int key, int x, int y);
void		catchBasicKey(unsigned char key, int x, int y);
void		resize(int width, int height);
void		display(void);
void		idle(void);
void		catchBasicKeyUp(unsigned char key, int x, int y);
void		updateCamTimer(int value);
void		DrawScreen();
#endif /* _GRAPHICS_H_ */
