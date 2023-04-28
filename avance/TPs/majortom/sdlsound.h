#ifndef _SDLSOUND_H_
#define _SDLSOUND_H_

/* SDL audio - lib Ensimag */

#include <stdint.h>

/* Structure de représentation d'un son */
struct audio {
    char            *name;      // Nom du son
    uint8_t         *data;      // Tableau des échantillons du son
    uint32_t        frequency;  // Fréquence du son
    uint32_t        length;     // Nombre d'élements du tableau data
};

struct audio *get_audio_wav(char* filename);
void free_audio(struct audio *audio);
void play_audio(struct audio *audio);
void print_audio_specs(struct audio audio);
 
#endif /* _SDLSOUND_H_ */
