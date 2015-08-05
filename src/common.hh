#ifndef _COMMON_H_
#define _COMMON_H_

#define MINSLANT   30
#define MAXSLANT   150
#define CIRBUF_LEN 4096
#define READ_CHUNK_LEN 1024
#define MOMENT_LEN 1023
#define SYNCPIXLEN 1.5e-3

#include <iostream>
#include "portaudio.h"
#include "sndfile.hh"
#include "fftw3.h"
#include "gtkmm.h"

using namespace std;

enum WindowType {
  WINDOW_HANN47 = 0,
  WINDOW_HANN63,
  WINDOW_HANN95,
  WINDOW_HANN127,
  WINDOW_HANN255,
  WINDOW_HANN511,
  WINDOW_HANN1023
};

enum SSTVMode {
 MODE_UNKNOWN=0,
 MODE_M1, MODE_M2, MODE_M3, MODE_M4,
 MODE_S1, MODE_S2, MODE_SDX,
 MODE_R72, MODE_R36, MODE_R24, MODE_R24BW, MODE_R12BW, MODE_R8BW,
 MODE_PD50, MODE_PD90, MODE_PD120, MODE_PD160, MODE_PD180, MODE_PD240, MODE_PD290,
 MODE_P3, MODE_P5, MODE_P7,
 MODE_W2120, MODE_W2180
};

enum eColorEnc {
  COLOR_GBR, COLOR_RGB, COLOR_YUV, COLOR_MONO
};

enum eSyncType {
  SYNC_STRAIGHT, SYNC_SCOTTIE
};

typedef struct _FFTStuff FFTStuff;
struct _FFTStuff {
  double       *in;
  fftw_complex *out;
  fftw_plan     Plan1024;
  fftw_plan     Plan2048;
};
extern FFTStuff fft;

typedef struct _PcmData PcmData;
struct _PcmData {
//  snd_pcm_t *handle;
  void      *handle;
  gint16    *Buffer;
  int        WindowPtr;
  bool   BufferDrop;
};
//extern PcmData pcm;


class PCMworker {

  public:

    PCMworker();

    void open_audio_file(string);
    void read_more();
    void next_moment();
    vector<short> get_windowed_moment(WindowType);


    vector<short> getsamples(int);

  private:

    mutable Glib::Threads::Mutex Mutex;
    short *win_lens;
    double window[7][1024];
    short cirbuf[CIRBUF_LEN * 2];
    int   cirbuf_head;
    int   cirbuf_tail;
    bool  please_stop;
    SndfileHandle file;

};

class SlowGUI {

  public:

    SlowGUI();

    void ping();

  private:

    Gtk::Button *button_abort;
    Gtk::Button *button_browse;
    Gtk::Button *button_clear;
    Gtk::Button *button_start;
    Gtk::ComboBoxText *combo_card;
    Gtk::ComboBox *combo_mode;
    Gtk::Entry *entry_picdir;
    Gtk::EventBox *eventbox_img;
    Gtk::Frame *frame_manual;
    Gtk::Frame *frame_slant;
    Gtk::Grid *grid_vu;
    Gtk::IconView *iconview;
    Gtk::Image *image_devstatus;
    Gtk::Image *image_pwr;
    Gtk::Image *image_rx;
    Gtk::Image *image_snr;
    Gtk::Label *label_fskid;
    Gtk::Label *label_lastmode;
    Gtk::Label *label_utc;
    Gtk::MenuItem *menuitem_about;
    Gtk::MenuItem *menuitem_quit;
    Gtk::SpinButton *spin_shift;
    Gtk::Widget *statusbar;
    Gtk::ToggleButton *tog_adapt;
    Gtk::ToggleButton *tog_fsk;
    Gtk::ToggleButton *tog_rx;
    Gtk::ToggleButton *tog_save;
    Gtk::ToggleButton *tog_setedge;
    Gtk::ToggleButton *tog_slant;
    Gtk::Window *window_about;
    Gtk::Window *window_main;
};

extern Glib::RefPtr<Gdk::Pixbuf> pixbuf_PWR;
extern Glib::RefPtr<Gdk::Pixbuf> pixbuf_SNR;
extern Glib::RefPtr<Gdk::Pixbuf> pixbuf_rx;
extern Glib::RefPtr<Gdk::Pixbuf> pixbuf_disp;

extern Gtk::ListStore *savedstore;

extern Glib::KeyFile config;


typedef struct _PicMeta PicMeta;
struct _PicMeta {
  int    HedrShift;
  int    Mode;
  double Rate;
  int    Skip;
  Gdk::Pixbuf *thumbbuf;
  char   timestr[40];
};
extern PicMeta CurrentPic;


typedef struct ModeSpec {
  string    Name;
  string    ShortName;
  double    tSync;
  double    tPorch;
  double    tSep;
  double    tPixel;
  double    tLine;
  int       ImgWidth;
  int       NumLines;
  int       LineHeight;
  eColorEnc ColorEnc;
  eSyncType SyncType;
} _ModeSpec;

extern _ModeSpec ModeSpec[];

double   power         (fftw_complex coeff);
int      clip          (double a);
void     createGUI     ();
double   deg2rad       (double Deg);
double   FindSync      (SSTVMode Mode, double Rate, int *Skip);
string   GetFSK        ();
bool     GetVideo      (SSTVMode Mode, double Rate, int Skip, bool Redraw);
SSTVMode GetVIS        ();
int      GetBin        (double Freq, int FFTLen);
int      initPcmDevice (std::string);
void     *Listen       ();
void     populateDeviceList ();
void     readPcm       (int numsamples);
void     saveCurrentPic();
void     setVU         (double *Power, int FFTLen, int WinIdx, bool ShowWin);
int      startGui      (int, char**);

void     evt_AbortRx       ();
void     evt_changeDevices ();
void     evt_chooseDir     ();
void     evt_clearPix      ();
void     evt_clickimg      (Gtk::Widget*, GdkEventButton*, Gdk::WindowEdge);
void     evt_deletewindow  ();
void     evt_GetAdaptive   ();
void     evt_ManualStart   ();
void     evt_show_about    ();


class MyPortaudioClass{

  int myMemberCallback(const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags);

  static int myPaCallback(
      const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags,
      void *userData ) {
      return ((MyPortaudioClass*)userData)
             ->myMemberCallback(input, output, frameCount, timeInfo, statusFlags);
  }
};

#endif