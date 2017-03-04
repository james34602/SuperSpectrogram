# SuperSpectrogram
Super spectrogram powered by Qt cross platform!

# Frequency plotting style
1. Log(Default)
2. Linear

You might want to switch between this two kind of plot by clicking(Or tap screen on Android) the application screen area.

# Colormap and colormap license
6 colormap built-in, double click(Or double tap screen on Android) the application screen area to switch 6 colormap display.

Colormap itself is converted from csv to c header file. And do not restricted by GPL v2.

They are downloaded from http://www.kennethmoreland.com/color-advice/ generated by __**Kenneth Moreland**__

# Screenshots
![Screenshot1](https://rawgit.com/james34602/SuperSpectrogram/master/Screenshot1.png "Vibrato!")
![Screenshot2](https://rawgit.com/james34602/SuperSpectrogram/master/Screenshot2.png "Vibrato!")

# Android user
You need a powerful device to run this app, because the computation may not be ARM-friendly.

# Non-Windows user
Default buffer size for 44.1kHz or 48kHz sampling rate should be approximately divided by 10, should be enough for displaying low frequency, but don't expect you can distinguish frequency within 10Hz.

# More...
Remove # in .pro file for enabling title bar text peak display.