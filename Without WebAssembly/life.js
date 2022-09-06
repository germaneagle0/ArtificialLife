fast_reduce_particle_interaction = 0.6;
SCREEN_WIDTH = 500;
SCREEN_HEIGHT = 500;
// Random, define the range that the random function returns
random_least = 50;
random_increase = 400;
// 0-500 but fill 50-450
particle_size = 4;

force_reducer = 0.75;

random_variables = () => {
  negative = (Math.random() > 0.5) ? 1:-1;
  value = Math.random() * Math.random();
  return negative * value;
}

// Rules (raio_afetado_afeta) e (afetado_afeta)
r_y_y = 40 * fast_reduce_particle_interaction;
r_y_y += 10 * random_variables();
y_y = 0.25;
y_y = random_variables();

r_y_r = 40 * fast_reduce_particle_interaction;
r_y_r += 10 * random_variables();
y_r = 0.001;
y_r = random_variables();
r_y_g = 80 * fast_reduce_particle_interaction;
y_g = -0.2;

r_r_r = 40 * fast_reduce_particle_interaction;
r_r_r += 10 * random_variables();
r_r = -0.1
r_r = random_variables();

r_r_y = 40 * fast_reduce_particle_interaction;
r_r_y += 10 * random_variables();
r_y = 0.001;
r_y = random_variables();

r_r_g = 40 * fast_reduce_particle_interaction;
r_r_g += 10 * random_variables();
r_g = -0.34;
r_g = random_variables();

r_g_g = 40 * fast_reduce_particle_interaction;
r_g_g += 10 * random_variables();
g_g = -0.32;
g_g = random_variables();

r_g_r = 40 * fast_reduce_particle_interaction;
r_g_r += 10 * random_variables();
g_r = -0.17;
g_r = random_variables();

r_g_y = 40 * fast_reduce_particle_interaction;
r_g_r += 10 * random_variables();
g_y = 0.34;
g_y = random_variables();

particles = [];

canvas = document.getElementById("life").getContext('2d');

draw_rectangle = (x, y, color, width, height) => {
  canvas.fillStyle = color;
  canvas.fillRect(x, y, width, height);
}

create_particle = (x,y,color) => {
  return {
    "x": x,
    "y": y,
    "vx": 0,
    "vy": 0,
    "color": color
  }
}

random_pos = () => {
  return (Math.random()*random_increase) + random_least;
}

// como a particula1 afeta a particula2
create_rule = (particles1, particles2, g, radius) => {
  if (g*g > 0) {
    for (let i = 0; i < particles1.length; i++) {
      fx = 0
      fy = 0
      a = particles1[i];
      for (let j = 0; j < particles2.length; j++) {
        b = particles2[j];
        dx = a.x - b.x;
        dy = a.y - b.y;
        pythagorian = (dx*dx + dy*dy);
        d = Math.sqrt(pythagorian);
        if (d > 0 && d < radius) {
          F = g/(d); // MULTIPLICAR POR INV_PYTHAGORIAN E TESTAR
          fx += (F*dx);
          fy += (F*dy);
        }
      }
      a.vx = (a.vx + fx) * force_reducer;
      a.vy = (a.vy + fy) * force_reducer;
      a.x += a.vx;
      a.y += a.vy;
      if (a.x < 0) {
        a.x = 0;
        a.vx *= -1;
      }
      if (a.x > SCREEN_WIDTH) {
        a.x = SCREEN_WIDTH;
        a.vx *= -1;
      }
      if (a.y < 0) {
        a.y = 0;
        a.vy *= -1;
      }
      if (a.y > SCREEN_HEIGHT) {
        a.y = SCREEN_HEIGHT;
        a.vy *= -1;
      }
    }
  }
}

create_particles = (amount, color) => {
  group = [];
  for (let i = 0; i < amount; i++) {
    group.push(create_particle(random_pos(), random_pos(), color));
    particles.push(group[i]);
  }
  return group;
}

yellow = create_particles(400, "yellow")
red = create_particles(400, "red");
green = create_particles(400, "green")

update = () => {
  canvas.clearRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
  create_rule(yellow, yellow, y_y, r_y_y);
  create_rule(yellow, green, y_g, r_y_g);
  create_rule(yellow, red, y_r, r_y_r);

  create_rule(red, red, r_r, r_r_r);
  create_rule(red, green, r_g, r_r_g);
  create_rule(red, yellow, r_y, r_r_y);

  create_rule(green, green, g_g, r_g_g);
  create_rule(green, red, g_r, r_g_r);
  create_rule(green, yellow, g_y, r_g_y);
  
  draw_rectangle(0,0, "black", SCREEN_WIDTH, SCREEN_HEIGHT);
  for (let i = 0;  i < particles.length; i++) {
    p = particles[i];
    draw_rectangle(p.x,p.y,p.color, particle_size, particle_size)
  }
  requestAnimationFrame(update);
}
update();