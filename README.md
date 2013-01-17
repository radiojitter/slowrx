slowrx
======

Slowrx is an SSTV decoder for Linux.

Created by Oona Räisänen / OH2-250 (windyoona at gmail).

Features
--------

* Support for a multitude of modes (see `modespec.c` for a list)
* Detect frequency-shifted signals – no need to fine-tune the radio
* Automatic slant correction (compensation for sound card clock error), also manual adjustments are simple
* Adaptive noise reduction
* Decode digital FSK ID
* Save received pictures as PNG
* Written in C99

Requirements
------------

* Linux
* Alsa
* Gtk+ 3.4
* FFTW 3

And, obviously:

* shortwave radio with SSB
* computer with sound card
* means of getting sound from one to the other

References
----------

The program was inspired by several articles:

* Barber, JL (N7CXI) (May 2000). ["Proposal for SSTV Mode Specifications"](http://www.barberdsp.com/files/Dayton%20Paper.pdf). Presented at the Dayton SSTV forum, 20 May 2000.
* Cordesses L, Cordesses R (F2DC) (May 2003). ["Some thoughts on 'Real-Time' SSTV Processing"](http://lionel.cordesses.free.fr/gpages/Cordesses.pdf). *QEX* May/June 2003: 3–20.
* Gasior M, Gonzalez J L (May 2004). ["Improving FFT Frequency Measurement Resolution by Parabolic and Gaussian Spectrum Interpolation"](http://cdsweb.cern.ch/record/738182/files/ab-2004-023.pdf). *AIP Conf. Proc.* (Geneva: CERN) **732** (2004): 276–285.
* Jones, D (KB4YZ) (Feb 1998). ["List of SSTV Modes with VIS Codes"](http://www.tima.com/~djones/vis.txt).
* Jones, D (KB4YZ) (May 1999). ["List of SSTV Modes with Line Timing"](http://www.tima.com/~djones/line.txt).

Licensing
---------

    Copyright (c) 2007-2013, Oona Räisänen (windyoona at gmail)
    
    Permission to use, copy, modify, and/or distribute this software for any
    purpose with or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
