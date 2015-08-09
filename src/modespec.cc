#include "common.hh"

/*
 * SSTV mode specifications
 * ========================
 *
 * Name        Full human-readable name
 * ShortName   Abbreviation used in filenames
 * ImgWidth    Pixels per scanline
 * NumLines    Number of scanlines
 * LineHeight  Height of one scanline in pixels (1 or 2)
 * tSync       Duration of horizontal sync pulse
 * tPorch      Duration of sync porch pulse
 * tSep        Duration of channel separator pulse (+ separator porch)
 * tScan       Duration of visible part of a channel scan (or Y if YUV)
 * tLine       Time from the beginning of a sync pulse to the beginning
 *             of the next one
 * SyncOrder   Positioning of sync pulse (SYNC_SIMPLE, SYNC_SCOTTIE)
 * SubSamp     Chroma subsampling mode for YUV (SUBSAMP_444, SUBSAMP_2121,
 *             SUBSAMP_2112, SUBSAMP_211)
 * ColorEnc    Color format (COLOR_GBR, COLOR_RGB, COLOR_YUV, COLOR_MONO)
 *
 *
 * All timings are in seconds.
 *
 * References: 
 *             
 *             JL Barber N7CXI (2000): "Proposal for SSTV Mode Specifications".
 *             Presented at the Dayton SSTV forum, 20 May 2000.
 *
 *             Dave Jones KB4YZ (1999): "SSTV modes - line timing".
 *             <http://www.tima.com/~djones/line.txt>
 */

_ModeSpec ModeSpec[] = {

  [MODE_M1] = {  // N7CXI, 2000
    .Name       = "Martin M1",
    .ShortName  = "M1",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tSync      = 4.862e-3,
    .tPorch     = 0.572e-3,
    .tSep       = 0.572e-3,
    .tScan      = 146.432e-3,
    .tLine      = 446.446e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_M2] = {  // N7CXI, 2000
    .Name       = "Martin M2",
    .ShortName  = "M2",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 73.216e-3,
    .tLine      = 226.7986e-3,
    .tSync      = 4.862e-3,
    .tPorch     = 0.572e-3,
    .tSep       = 0.572e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_M3] = {   // KB4YZ, 1999
    .Name       = "Martin M3",
    .ShortName  = "M3",
    .ImgWidth   = 320,
    .NumLines   = 128,
    .LineHeight = 2,
    .tScan      = 73.216e-3,
    .tLine      = 446.446e-3,
    .tSync      = 4.862e-3,
    .tPorch     = 0.572e-3,
    .tSep       = 0.572e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_M4] = {   // KB4YZ, 1999
    .Name       = "Martin M4",
    .ShortName  = "M4",
    .ImgWidth   = 320,
    .NumLines   = 128,
    .LineHeight = 2,
    .tScan      = 73.216e-3,
    .tLine      = 226.7986e-3,
    .tSync      = 4.862e-3,
    .tPorch     = 0.572e-3,
    .tSep       = 0.572e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_S1] = {  // N7CXI, 2000
    .Name       = "Scottie S1",
    .ShortName  = "S1",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tSync      = 9e-3,
    .tPorch     = 1.5e-3,
    .tSep       = 1.5e-3,
    .tScan      = 138.24e-3,
    .tLine      = 428.22e-3,
    .SyncOrder  = SYNC_SCOTTIE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_S2] = {  // N7CXI, 2000
    .Name       = "Scottie S2",
    .ShortName  = "S2",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 88.064e-3,
    .tLine      = 277.692e-3,
    .tSync      = 9e-3,
    .tPorch     = 1.5e-3,
    .tSep       = 1.5e-3,
    .SyncOrder  = SYNC_SCOTTIE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_SDX] = {  // N7CXI, 2000
    .Name       = "Scottie DX",
    .ShortName  = "SDX",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 345.6e-3,
    .tLine      = 1050.3e-3,
    .tSync      = 9e-3,
    .tPorch     = 1.5e-3,
    .tSep       = 1.5e-3,
    .SyncOrder  = SYNC_SCOTTIE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_GBR },

  [MODE_R72] = {  // N7CXI, 2000
    .Name       = "Robot 72",
    .ShortName  = "R72",
    .ImgWidth   = 320,
    .NumLines   = 240,
    .LineHeight = 1,
    .tScan      = 138e-3,
    .tLine      = 300e-3,
    .tSync      = 9e-3,
    .tPorch     = 3e-3,
    .tSep       = 6e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_422_YUV,
    .ColorEnc   = COLOR_YUV },

  [MODE_R36] = {  // N7CXI, 2000
    .Name       = "Robot 36",
    .ShortName  = "R36",
    .ImgWidth   = 320,
    .NumLines   = 240,
    .LineHeight = 1,
    .tScan      = 88e-3,
    .tLine      = 150e-3,
    .tSync      = 9e-3,
    .tPorch     = 3e-3,
    .tSep       = 6e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_420_YUYV,
    .ColorEnc   = COLOR_YUV },

  [MODE_R24] = {  // KB4YZ, 1999
    .Name       = "Robot 24",
    .ShortName  = "R24",
    .ImgWidth   = 320,
    .NumLines   = 240,
    .LineHeight = 1,
    .tScan      = 66e-3,
    .tLine      = 150e-3,
    .tSync      = 9e-3,
    .tPorch     = 3e-3,
    .tSep       = 6e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_420_YUYV,
    .ColorEnc   = COLOR_YUV },

  [MODE_R24BW] = {  // KB4YZ, 1999
    .Name       = "Robot 24 B/W",
    .ShortName  = "R24BW",
    .ImgWidth   = 320,
    .NumLines   = 240,
    .LineHeight = 1,
    .tScan      = 66e-3,
    .tLine      = 100e-3,
    .tSync      = 7e-3,
    .tPorch     = 0,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_MONO },

  [MODE_R12BW] = {  // KB4YZ, 1999
    .Name       = "Robot 12 B/W",
    .ShortName  = "R12BW",
    .ImgWidth   = 320,
    .NumLines   = 120,
    .LineHeight = 2,
    .tScan      = 66e-3,
    .tLine      = 100e-3,
    .tSync      = 7e-3,
    .tPorch     = 0,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_MONO },

  [MODE_R8BW] = {  // KB4YZ, 1999
    .Name       = "Robot 8 B/W",
    .ShortName  = "R8BW",
    .ImgWidth   = 320,
    .NumLines   = 120,
    .LineHeight = 2,
    .tScan      = 60e-3,
    .tLine      = 67e-3,
    .tSync      = 7e-3,
    .tPorch     = 0,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_MONO },
  
  [MODE_W2120] = { // KB4YZ, 1999
    .Name       = "Wraase SC-2 120",
    .ShortName  = "W2120",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 156.5025e-3,
    .tLine      = 475.530018e-3,
    .tSync      = 5.5225e-3,
    .tPorch     = 0.5e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_RGB },

  [MODE_W2180] = {  // N7CXI, 2000
    .Name       = "Wraase SC-2 180",
    .ShortName  = "W2180",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 235e-3,
    .tLine      = 711.0225e-3,
    .tSync      = 5.5225e-3,
    .tPorch     = 0.5e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_RGB },

  [MODE_PD50] = {  // N7CXI, 2000
    .Name       = "PD-50",
    .ShortName  = "PD50",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 91.52e-3,
    .tLine      = 388.16e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_PD90] = {  // N7CXI, 2000
    .Name       = "PD-90",
    .ShortName  = "PD90",
    .ImgWidth   = 320,
    .NumLines   = 256,
    .LineHeight = 1,
    .tScan      = 170.240e-3,
    .tLine      = 703.04e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_PD120] = {  // N7CXI, 2000
    .Name       = "PD-120",
    .ShortName  = "PD120",
    .ImgWidth   = 640,
    .NumLines   = 496,
    .LineHeight = 1,
    .tScan      = 121.6e-3,
    .tLine      = 508.48e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_PD160] = {  // N7CXI, 2000
    .Name       = "PD-160",
    .ShortName  = "PD160",
    .ImgWidth   = 512,
    .NumLines   = 400,
    .LineHeight = 1,
    .tScan      = 195.584e-3,
    .tLine      = 804.416e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_PD180] = {  // N7CXI, 2000
    .Name       = "PD-180",
    .ShortName  = "PD180",
    .ImgWidth   = 640,
    .NumLines   = 496,
    .LineHeight = 1,
    .tScan      = 183.04e-3,
    .tLine      = 754.24e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_PD240] = {  // N7CXI, 2000
    .Name       = "PD-240",
    .ShortName  = "PD240",
    .ImgWidth   = 640,
    .NumLines   = 496,
    .LineHeight = 1,
    .tScan      = 244.48e-3,
    .tLine      = 1000e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_PD290] = {  // N7CXI, 2000
    .Name       = "PD-290",
    .ShortName  = "PD290",
    .ImgWidth   = 800,
    .NumLines   = 616,
    .LineHeight = 1,
    .tScan      = 228.8e-3,
    .tLine      = 937.28e-3,
    .tSync      = 20e-3,
    .tPorch     = 2.08e-3,
    .tSep       = 0,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_440_YUVY,
    .ColorEnc   = COLOR_YUV },

  [MODE_P3] = {  // N7CXI, 2000
    .Name       = "Pasokon P3",
    .ShortName  = "P3",
    .ImgWidth   = 640,
    .NumLines   = 496,
    .LineHeight = 1,
    .tScan      = 133.333e-3,
    .tLine      = 409.375e-3,
    .tSync      = 5.208e-3,
    .tPorch     = 1.042e-3,
    .tSep       = 1.042e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_RGB },

  [MODE_P5] = {  // N7CXI, 2000
    .Name       = "Pasokon P5",
    .ShortName  = "P5",
    .ImgWidth   = 640,
    .NumLines   = 496,
    .LineHeight = 1,
    .tScan      = 200e-3,
    .tLine      = 614.065e-3,
    .tSync      = 7.813e-3,
    .tPorch     = 1.563e-3,
    .tSep       = 1.563e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_RGB },

  [MODE_P7] = {  // N7CXI, 2000
    .Name       = "Pasokon P7",
    .ShortName  = "P7",
    .ImgWidth   = 640,
    .NumLines   = 496,
    .LineHeight = 1,
    .tScan      = 266.666e-3,
    .tLine      = 818.747e-3,
    .tSync      = 10.417e-3,
    .tPorch     = 2.083e-3,
    .tSep       = 2.083e-3,
    .SyncOrder  = SYNC_SIMPLE,
    .SubSamp    = SUBSAMP_444,
    .ColorEnc   = COLOR_RGB }
 
};

/*
 * Mapping of 7-bit VIS codes to modes
 *
 * Reference: Dave Jones KB4YZ (1998): "List of SSTV Modes with VIS Codes".
 *            http://www.tima.com/~djones/vis.txt
 *
 */

map<int, SSTVMode> vis2mode = {
  {0x02,MODE_R8BW}, {0x04,MODE_R24},  {0x06,MODE_R12BW}, {0x08,MODE_R36},
  {0x0A,MODE_R24BW},{0x0C,MODE_R72},  {0x20,MODE_M4},    {0x24,MODE_M3},
  {0x28,MODE_M2},   {0x2C,MODE_M1},   {0x37,MODE_W2180}, {0x38,MODE_S2},
  {0x3C,MODE_S1},   {0x3F,MODE_W2120},{0x4C,MODE_SDX},   {0x5D,MODE_PD50},
  {0x5E,MODE_PD290},{0x5F,MODE_PD120},{0x60,MODE_PD180}, {0x61,MODE_PD240},
  {0x62,MODE_PD160},{0x63,MODE_PD90}, {0x71,MODE_P3},    {0x72,MODE_P5},
  {0x73,MODE_P7}
};

