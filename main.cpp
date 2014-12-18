#include<allegro.h>
#include<string>
#include<time.h>
#include<math.h>
#include <cmath>

using namespace std;

// Images
BITMAP* buffer;

// Sounds
SAMPLE* piano;

// Variables
int piano_width = 0;
int piano_height = 0;
double frequency = 0;

// Program setup
void setup(){
  // Create buffer
  buffer = create_bitmap( 640, 480);

  // Load instruments
  piano = load_sample( "piano.wav");

  // Width of piano tiles in px
  piano_width = 60;
  piano_height = piano_width * 3;
}

// Main game loop
void game(){
  // Background
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(0,0,0));

  // Draw piano
  for( int i = 0; i < 10; i ++){
    rectfill( buffer, i* piano_width, 10, i* piano_width + piano_width, 10 + piano_height, makecol(0,0,0));
    rectfill( buffer, i* piano_width + 1, 10, i* piano_width + piano_width - 1, 10 + piano_height, makecol(255,255,255));
  }

  // Change frequency depending on mouse location
  frequency = 440 * pow(2.0, ((mouse_x/4) - 69.0)/12.0);

  // Play note
  if( mouse_b & 1){
    play_sample( piano, 255, 127, frequency, 0);
  }

  // Draw frequency to screen
  textprintf_ex( buffer, font, 0, 0, makecol(0,0,0), makecol(255,255,255), "Frequency: %f Mouse_x: %i", frequency, (mouse_x/4));

  // Cursor
  rectfill( buffer, mouse_x, mouse_y, mouse_x + 4, mouse_y + 4, makecol(255,0,0));

  draw_sprite( screen, buffer, 0, 0);
}

int main(){
  //Makes sure allegro is running properly
  if (allegro_init() != 0){
    return 1;
  }

  //Initializing
  install_mouse();
  install_keyboard();
  set_palette(desktop_palette);
  set_color_depth(32);
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_window_title("Math Blocks");

  // Setup game
  setup();

  // Start game
  while( !key[KEY_ESC])
    game();

  delete [] buffer;

  allegro_exit();

  return 0;
}
END_OF_MAIN();
