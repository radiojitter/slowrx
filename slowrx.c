/*
 * slowrx - an SSTV decoder
 * * * * * * * * * * * * * *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <gtk/gtk.h>
#include <pthread.h>
#include <pnglite.h>

#include <alsa/asoundlib.h>

#include "common.h"


void *Listen() {

  int        Skip = 0, i=0;
  char       dest[40], pngfilename[40], lumfilename[40], infostr[60], rctime[8];
  guchar    *Lum, *pixels, Mode=0;
  guint      Rate = SRATE;
  struct tm *timeptr = NULL;
  time_t     timet;
  FILE      *LumFile;
  gboolean   Finished;

  while (TRUE) {

    // Wait for VIS
    HedrShift = 0;
    gdk_threads_enter();
    gtk_widget_set_sensitive(vugrid,   TRUE);
    gtk_widget_set_sensitive(btnabort, FALSE);
    gdk_threads_leave();

    snd_pcm_prepare(pcm_handle);
    snd_pcm_start  (pcm_handle);
    Mode = GetVIS();
    if (Mode == 0) exit(EXIT_FAILURE);

    printf("  ==== %s ====\n", ModeSpec[Mode].Name);

    timet = time(NULL);
    timeptr = gmtime(&timet);
    strftime(dest, sizeof(dest)-1,"%Y%m%d-%H%M%Sz", timeptr);
    snprintf(pngfilename, sizeof(dest)-1, "rx/%s_%s.png", ModeSpec[Mode].ShortName, dest);
    snprintf(lumfilename, sizeof(dest)-1, "rx/%s_%s-lum", ModeSpec[Mode].ShortName, dest);
    printf("  \"%s\"\n", pngfilename);
    
    // Allocate space for PCM
    PCM = calloc( (int)(ModeSpec[Mode].LineLen * ModeSpec[Mode].ImgHeight + 1) * SRATE, sizeof(double));
    if (PCM == NULL) {
      perror("Listen: Unable to allocate memory for PCM");
      exit(EXIT_FAILURE);
    }

    // Allocate space for cached FFT
    StoredFreq = calloc( (int)(ModeSpec[Mode].LineLen * ModeSpec[Mode].ImgHeight + 1) * SRATE, sizeof(double));
    if (StoredFreq == NULL) {
      perror("Listen: Unable to allocate memory for demodulated signal");
      free(PCM);
      exit(EXIT_FAILURE);
    }
  
    // Get video
    strftime(rctime, sizeof(rctime)-1, "%H:%M", timeptr);
    snprintf(infostr, sizeof(infostr)-1, "%s, %s UTC", ModeSpec[Mode].Name, rctime);
    gdk_threads_enter();
    gtk_widget_set_sensitive( manualframe, FALSE);
    gtk_widget_set_sensitive( btnabort,    TRUE);
    gtk_statusbar_push( GTK_STATUSBAR(statusbar), 0, "Receiving video" );
    gtk_label_set_markup(GTK_LABEL(infolabel), infostr);
    gdk_threads_leave();
    PcmPointer = 2048;
    Sample     = 0;
    Rate       = SRATE;
    Skip       = 0;
    printf("  getvideo @ %d Hz, Skip %d, HedrShift %d Hz\n", Rate, Skip, HedrShift);

    Finished = GetVideo(Mode, Rate, Skip, FALSE);
    gdk_threads_enter();
    gtk_widget_set_sensitive( btnabort,    FALSE);
    gtk_widget_set_sensitive( manualframe, TRUE);
    gdk_threads_leave();

    if (Finished) {
      GetFSK();
    }
    snd_pcm_drop(pcm_handle);

    if (Finished && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togslant))) {

      // Fix slant
      setVU(0,-100);
      gdk_threads_enter();
      gtk_statusbar_push( GTK_STATUSBAR(statusbar), 0, "Calculating slant" );
      gtk_widget_set_sensitive(vugrid, FALSE);
      gdk_threads_leave();
      printf("  FindSync @ %d Hz\n",Rate);
      Rate = FindSync(PcmPointer, Mode, Rate, &Skip);
   
      // Final image  
      gdk_threads_enter();
      gtk_statusbar_push( GTK_STATUSBAR(statusbar), 0, "Redrawing" );
      gdk_threads_leave();
      printf("  getvideo @ %d Hz, Skip %d, HedrShift %d Hz\n", Rate, Skip, HedrShift);
      GetVideo(Mode, Rate, Skip, TRUE);
    }
      
    free(PCM);
    PCM = NULL;
    
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(togsave))) {

      // Save the raw signal
      setVU(0,-100);
      gdk_threads_enter();
      gtk_statusbar_push( GTK_STATUSBAR(statusbar), 0, "Saving" );
      gdk_threads_leave();

      Lum = malloc( (ModeSpec[Mode].LineLen * ModeSpec[Mode].ImgHeight) * SRATE );
      if (Lum == NULL) {
        perror("Unable to allocate memory for lum data");
        exit(EXIT_FAILURE);
      }
      for (i=0; i<(ModeSpec[Mode].LineLen * ModeSpec[Mode].ImgHeight) * SRATE; i++)
        Lum[i] = clip((StoredFreq[i] - (1500 + HedrShift)) / 3.1372549);

      LumFile = fopen(lumfilename,"w");
      if (LumFile == NULL) {
        perror("Unable to open luma file for writing");
        exit(EXIT_FAILURE);
      }
      fwrite(Lum,1,(ModeSpec[Mode].LineLen * ModeSpec[Mode].ImgHeight) * SRATE,LumFile);
      fclose(LumFile);

      // Save the received image as PNG
      png_t png;
      png_init(0,0);

      pixels = gdk_pixbuf_get_pixels(RxPixbuf);

      png_open_file_write(&png, pngfilename);
      png_set_data(&png, ModeSpec[Mode].ImgWidth, ModeSpec[Mode].ImgHeight, 8, PNG_TRUECOLOR, pixels);
      png_close_file(&png);
    }
    
    free(StoredFreq);
    StoredFreq = NULL;
    
  }
}


/*
 * main
 */

int main(int argc, char *argv[]) {

  pthread_t thread1;

  gtk_init (&argc, &argv);

  g_thread_init (NULL);
  gdk_threads_init ();

  createGUI();
  initPcmDevice();

  pthread_create (&thread1, NULL, Listen, NULL);

  gtk_main();

  g_object_unref(RxPixbuf);
  free(PCM);
  free(StoredFreq);

  printf("Clean exit\n");

  return (EXIT_SUCCESS);
}
