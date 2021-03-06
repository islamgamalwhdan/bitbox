// test simple by default
#include <string.h>

#include "bitbox.h" // gamepad

#define SND_IMPLEMENTATION
#include "data.h"

#include "lib/textmode/textmode.h"
#include "lib/sampler/sampler.h"

const char *instrs[8] = {
  "This is a demonstration of Bitbox simple sampler with sound in flash ",
  "(opposed to sounds streamed from sdcard)",
  "",
  "Press ABXY / UDLR buttons on the gamepad (or the emulated version ",
  "keyboard) and play with the sounds (sound output needs to be plugged ",
  "in of course).",
  "",
  "Check the source to see how to integrate sounds in your games."
};


extern const struct NoteEvent track_piano[];
extern const int track_piano_len;

void game_init() {
    const int tempo=80;
    const int piano_loop=-1; // don't ?
    
    // instructions
    clear(); // necessary 
    window(0,3,1,76,10);
    for (int i=0;i<8;i++)
        print_at(5, 2+i, 0,instrs[i]);
    
    play_track (
        track_piano_len,
        tempo,
        track_piano,

        snd_piano_note_raw, 
        piano_loop,
        sizeof(snd_piano_note_raw),
        44100);
}

#define ifplay(but,sndname, speed) \
    if((gamepad_buttons[0] & ~last_buts) & gamepad_##but) \
        play_sample(snd_##sndname##_raw, sizeof(snd_##sndname##_raw),speed,-1, 40,40); // no loop

void game_frame() {
    static uint16_t last_buts;
    uint16_t speed; 
    
    if (GAMEPAD_PRESSED(0,L)) 
        speed = 0x80;
    else if (GAMEPAD_PRESSED(0,R))
        speed = 0x180;
    else 
        speed=0x100;

    ifplay(A,bitbox_rules,speed);
    ifplay(B,monster,speed);
    ifplay(X,pouet,speed);
    ifplay(Y,guitar,speed);

    ifplay(up,sax,speed);
    ifplay(down,piano_note,speed);
    ifplay(left,warplevel,speed);
    ifplay(right,diam,speed);
       
    last_buts = gamepad_buttons[0];
}
