#include <stdio.h>
#include <emscripten/emscripten.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int NUMBER_PARTICLES = 3000;
const float fast_reduce_particle_interaction = 0.6;
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const int random_least = 50;
const int random_increase = 400;
const float force_reducer = 0.95;
int ready = 0;
const float min_radius_squared = 6;
const int common_multipler = 30;
const int sum_multipler = 10;
const float strength_multiplier = 1.2;


double rand_0_1(void)
{
    return rand() / ((double) RAND_MAX);
}
float random_variables() {
  int negative = (rand() % 2) ? 1 : -1;
  float value = rand_0_1() * rand_0_1();
  return negative*value;
}
float random_pos() {
  return (rand_0_1() * random_increase) + random_least;
}
float r_y_y = common_multipler * fast_reduce_particle_interaction;
float y_y;

float r_y_r = common_multipler * fast_reduce_particle_interaction;

float y_r;

float r_y_g = common_multipler * fast_reduce_particle_interaction;
float y_g ;

float r_r_r = common_multipler * fast_reduce_particle_interaction;
float r_r ;

float r_r_y = common_multipler * fast_reduce_particle_interaction;
float r_y ;

float r_r_g = common_multipler * fast_reduce_particle_interaction;
float r_g ;

float r_g_g = common_multipler * fast_reduce_particle_interaction;
float g_g ;

float r_g_r = common_multipler * fast_reduce_particle_interaction;
float g_r ;

float r_g_y = common_multipler * fast_reduce_particle_interaction;
float g_y ;

typedef struct particle
{
  float x;
  float y; 
  float vx;
  float vy;
  char* cor;
} Particle;

typedef struct group
{
  int start;
  int end;
} ParticleGroup;

Particle* particles;
int size=0;

ParticleGroup create_particles(int amount, char* color) {
  int start = size;
  for (int i = 0; i < amount ; i++) {
    particles[start + i].cor = color;
    particles[start + i].x = random_pos();
    particles[start + i].y = random_pos();
    particles[start + i].vx = 0;
    particles[start + i].vy = 0;
    size++;
  }
  ParticleGroup c;
  c.start = start;
  c.end = size - 1;
  return c;
}

float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 );   
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );
	return y;
}

void create_rule(ParticleGroup p1, ParticleGroup p2, float g, float radius) {
  if (g*g > 0) {
    for (int i = p1.start; i <= p1.end; i++) {
      float fx = 0;
      float fy = 0;
      Particle* a = &particles[i];
      for (int j = p2.start; j <= p2.end; j++ ) {
        Particle* b = &particles[j];
        float dx = a->x - b->x;
        float dy = a->y - b->y;
        float pythagorian = (dx*dx + dy*dy);
        if (pythagorian > min_radius_squared && pythagorian < radius*radius) {
          float inv_d = Q_rsqrt(pythagorian);
          float F = g * inv_d;
          fx += (F*dx);
          fy += (F*dy);
        }
      }
      a->vx = (a->vx + fx) * force_reducer;
      a->vy = (a->vy + fy) * force_reducer;
      a->x += (a->vx);
      a->y += (a->vy);
      if (a->x < 0) {
        a->x = 0;
        a->vx *= -1;
      }
      if (a->x > SCREEN_WIDTH) {
        a->x = SCREEN_WIDTH;
        a->vx *= -1;
      }
      if (a->y < 0) {
        a->y = 0;
        a->vy *= -1;
      }
      if (a->y > SCREEN_HEIGHT) {
        a->y = SCREEN_HEIGHT;
        a->vy *= -1;
      }
    }
  }
}
ParticleGroup yellow;
ParticleGroup red;
ParticleGroup green;

void init() { 
  y_y = strength_multiplier * random_variables();
  y_r = strength_multiplier * random_variables();
  y_g = strength_multiplier * random_variables();
  r_r = strength_multiplier * random_variables();
  r_y = strength_multiplier * random_variables();
  r_g = strength_multiplier * random_variables();
  g_g = strength_multiplier * random_variables();
  g_r = strength_multiplier * random_variables();
  g_y = strength_multiplier * random_variables();
  
  r_g_y += sum_multipler * random_variables();
  r_g_r += sum_multipler * random_variables();
  r_g_g += sum_multipler * random_variables();
  r_r_g += sum_multipler * random_variables();
  r_r_y += sum_multipler * random_variables();
  r_r_r += sum_multipler * random_variables();
  r_y_g += sum_multipler * random_variables();
  r_y_y += sum_multipler * random_variables();
  r_y_r += sum_multipler * random_variables();

  yellow = create_particles(1000, "yellow");
  red = create_particles(1000, "red");
  green = create_particles(1000, "green");
}

void update() {
  if (ready) {
    create_rule(yellow, yellow, y_y, r_y_y);
    create_rule(yellow, green, y_g, r_y_g);
    create_rule(yellow, red, y_r, r_y_r);

    create_rule(red, red, r_r, r_r_r);
    create_rule(red, green, r_g, r_r_g);
    create_rule(red, yellow, r_y, r_r_y);

    create_rule(green, green, g_g, r_g_g);
    create_rule(green, red, g_r, r_g_r);
    create_rule(green, yellow, g_y, r_g_y);
  }
}

int getX(int i) {
  return particles[i].x;
}

int getY(int i) {
  return particles[i].y;
}

char* getColor(int i) {
  return particles[i].cor;
}

int main() {
  srand(time(NULL));
  particles = (Particle*) malloc(NUMBER_PARTICLES * sizeof(Particle));
  init();
  ready = 1;
  return 0;
}

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE int get_x(int i) {
    return particles[i].x;
}
EXTERN EMSCRIPTEN_KEEPALIVE int get_y(int i) {
    return particles[i].y;
}
EXTERN EMSCRIPTEN_KEEPALIVE int get_vx(int i) {
    return particles[i].vx;
}
EXTERN EMSCRIPTEN_KEEPALIVE int get_vy(int i) {
    return particles[i].vy;
}
EXTERN EMSCRIPTEN_KEEPALIVE char get_cor(int i) {
    return particles[i].cor[0];
}
EXTERN EMSCRIPTEN_KEEPALIVE void update_particles() {
  update();
}
EXTERN EMSCRIPTEN_KEEPALIVE int get_total() {
  return NUMBER_PARTICLES;
}
