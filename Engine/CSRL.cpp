#include <ncurses.h>
#include <sys/time.h>
#include <unistd.h>
#include "Engine/CSRL.h"
#include "Engine/Graphics.h"
#include "Engine/Math.h"
#include "Entities/Console.h"
#include "Entities/Character.h"
#include "Weapons/Weapon.h"
#include "Network/Network.h"

// Initialize CSRL
CSRL::CSRL()
{
  // Setup instance
  inst = this;

  // Initialize NCurses
  initscr();
  nodelay(stdscr, true);
  noecho();
  curs_set(0);

  // Setup color
  //init_color(0,1000,0,0);
  //start_color();
  //init_pair(1, COLOR_RED, COLOR_WHITE);
  //attron(COLOR_PAIR(1));

  // Setup screen dimensions
  getmaxyx(stdscr, CSRL::height, CSRL::width);

  // Setup console
  console = new Console();

  // Setup player
  player = add_character(new Character("felix", CounterTerrorist, 5, 5));
  add_character(new Character("poop", Terrorist, 70, 5));
  //add_entity(new Server(1337));

  // Run game
  running = true;
  run();
}

// Deinitialize CSRL
CSRL::~CSRL()
{
  endwin();
  inst = NULL;
}

// Run game
void CSRL::run()
{
  // Setup time
  double delta, timer = 0.0, fps = 0.0;
  struct timeval time, last_time;
  gettimeofday(&time, NULL);
  int frames = 0;

  // Main game loop
  while(running)
  {
    // Get time
    last_time = time;
    gettimeofday(&time, NULL);
    delta = double(time.tv_sec - last_time.tv_sec) + double(time.tv_usec - last_time.tv_usec) / 1000000.0;
    if(delta < 0.0) delta = 0.0;
    else if(delta > 1.0) delta = 1.0;

    // FPS
    frames++;
    timer += delta;
    if(timer >= 0.25)
    {
      fps = frames / timer;
      timer = 0.0;
      frames = 0;
    }

    // Get player input
    get_input();

    // Update entities
    update(delta);

    // Clear screen
    clear();

    // Redraw entities
    draw();

    // Draw FPS
    mvprintw(0, width - 20, "%10.0f fps (%3i)", fps, entities.size());

    // Update screen
    refresh();

    // Sleep
    if(fps > 200)
    {
      usleep(2000);
    }
  }
}

// Get user input
void CSRL::get_input()
{
  int input;
  while((input = getch()) > 0)
  {
    // Resize screen
    if(input == KEY_RESIZE)
      resize();

    // Toggle console
    else if(input == '`' || input == '~')
      console->toggle();
    else if(console->display)
      console->input(input);

    // Player inputs
    else
      player->input(input);

    // Draw key pressed
    mvprintw(0, 0, " %c %i ", input, input);
  }
}

// Update entities
void CSRL::update(double delta)
{
  // Update console
  console->update(delta);

  // Update player
  //player->update(delta);

  // Update characters

  for(list <Character *>::iterator it = characters.begin(); it != characters.end(); it++)
  {
    if(!(*it)->update(delta))
    {
      delete (*it);
      it = characters.erase(it);
    }
  }

  // Update entities
  for(list <Entity *>::iterator it = entities.begin(); it != entities.end(); it++)
  {
    try
    {
      if(!(*it)->update(delta))
      {
        delete (*it);
        it = entities.erase(it);
      }
    }
    catch(const char *error)
    {
      console->add_line(string("Exception caught: ") + error);
    }
  }
}

// Draw entities and hud
void CSRL::draw()
{
  // Draw entities
  for(list <Entity *>::iterator it = entities.begin(); it != entities.end(); it++)
  {
    (*it)->draw();
  }

  // Draw objects
  for(list <Object *>::iterator it = objects.begin(); it != objects.end(); it++)
  {
    (*it)->draw();
  }

  // Draw characters
  for(list <Character *>::iterator it = characters.begin(); it != characters.end(); it++)
  {
    (*it)->draw();
  }

  // Draw HUD
  draw_hud();

  // Draw console
  console->draw();
}

// Draw HUD
void CSRL::draw_hud()
{
  // Draw name
  mvprintw(CSRL::inst->height - 2, 0, player->name.c_str());

  // Draw weapon info
  if(player->weapon)
  {
    player->weapon->draw_info();
  }

  // Draw team
  if(player->team == CounterTerrorist)
    mvprintw(CSRL::inst->height - 1, 0, "Counter-Terrorist");
  else if(player->team == Terrorist)
    mvprintw(CSRL::inst->height - 1, 0, "Terrorist");
  else
    mvprintw(CSRL::inst->height - 1, 0, "Spectator");

  // Draw money
  mvprintw(CSRL::inst->height - 1, 20, "$100");
}

// Screen has been resized
void CSRL::resize()
{
  // Get new screen size
  getmaxyx(stdscr, CSRL::height, CSRL::width);

  // Resize console
  console->resize();

  // Resize entities
  for(list <Entity *>::iterator it = entities.begin(); it != entities.end(); it++)
  {
    (*it)->resize();
  }

  // Resize objects
  for(list <Object *>::iterator it = objects.begin(); it != objects.end(); it++)
  {
    (*it)->resize();
  }

  // Resize characters
  for(list <Character *>::iterator it = characters.begin(); it != characters.end(); it++)
  {
    (*it)->resize();
  }

  // Redraw screen
  //clear();
  //draw();
  //refresh();
}

// Add entity to entities list
Entity *CSRL::add_entity(Entity *entity)
{
  entities.push_back(entity);
  return entity;
}

// Add character to characters list
Character *CSRL::add_character(Character *character)
{
  characters.push_back(character);
  return character;
}

// Initialize static variable inst
CSRL *CSRL::inst = NULL;
