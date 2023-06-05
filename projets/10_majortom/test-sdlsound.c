/* Test lib son SDL */

#include <stdlib.h>
#include "sdlsound.h"
#include "fonctions.h"

int main(void)
{
    struct audio *audio1, *audio2, *audio3, *mix;;
    audio1 = audio2 = audio3 = mix = NULL;

    audio1 = get_audio_wav("data/david-bowie-major-tom-extrait01-11025.wav");
    print_audio_specs(*audio1);
    play_audio(audio1);

    audio2 = get_audio_wav("data/david-bowie-china-girl-extrait01-22050.wav");
    print_audio_specs(*audio2);
    play_audio(audio2);

    audio3 = get_audio_wav("data/david-bowie-lets-dance-extrait01-44100.wav");
    print_audio_specs(*audio3);
    play_audio(audio3);

    /*  Mixer audio1 et audio2 et mettre le resultat dans mix
	Puis mixer audio1 et audio 3 et mettre le resultat dans mix
	Puis mixer audio3 et audio 2 et mettre le resultat dans mix
	Après chaque mixage, afficher les caractéristiques du son mix via la fonction print_audio_specs
	et bien sur jouer le son mix pour vérifier votre mixage
	Penser à libérer la mémoire quand c'est nécessaire et en fin de main également
    */
    return EXIT_SUCCESS;
}
