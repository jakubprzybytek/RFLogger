# RFLogger

Lighweight tool for basic long lasting RF logging. Uses [SoapySDR](https://github.com/pothosware/SoapySDR/wiki) API to talk with SDR device.

```
Usage RFLogger [options]
  Options summary:
    -l, --list-device              List all available SDR devices and exit

    -i, --device-info              Display detailed information about the device in use
    -n, --number <number>          Perform <number> reads and exit. If '0' then read in loop.
    -b, --bandwidth <float>        Sets bandwidth to <float>
    -s, --samplerate <float>       Sets sample reate to <float>
    -f, --frequency <float>        Sets frequency to <float>
    -c, --console <number>         Use console as an output with width set to <number>

    -h, --help                     Display this help information and exit
```
