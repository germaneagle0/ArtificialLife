SCREEN_WIDTH = 500;
SCREEN_HEIGHT = 500;
particle_size = 4;
canvas = document.getElementById("life").getContext('2d');

draw_rectangle = (x, y, color, width, height) => {
  canvas.fillStyle = color;
  canvas.fillRect(x, y, width, height);
}

update = () => {
  canvas.clearRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
  Module.ccall("update_particles",null,null,null);
  draw_rectangle(0,0, "black", SCREEN_WIDTH, SCREEN_HEIGHT);
  let number_of_particles = Module.ccall("get_total", null,null,null);
  for (let i = 0;  i < number_of_particles; i++) {
    let cor;
    switch(String.fromCharCode(Module.ccall("get_cor","String",["number"],[i]))) {
      case 'y':
        cor ="yellow";
        break;
      case 'r':
        cor = "red";
        break;
      case 'g':
        cor ="green";
        break;
      default:
        cor = "blue";
    }
    draw_rectangle(Module.ccall("get_x","number",["number"],[i]),
      Module.ccall("get_y","number",["number"],[i]), cor, particle_size, particle_size)
  }
  requestAnimationFrame(update);
}