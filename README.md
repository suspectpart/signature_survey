# Signature Survey

Prints a [Signature Survey](http://c2.com/cgi/wiki?SignatureSurvey) for all source files in current folder and subfolders.

# Build and run
To build, just checkout this repo and run make:

```Shell
$ git clone git@github.com:suspectpart/signature_survey
$ cd signature_survey
$ make && sudo make install
```

`sigs` will be installed in `/usr/local/bin`. To run it call:

```Shell
$ sigs -t .java -l 100
``` 

# Uninstall
To uninstall `sigs` from your system, just run

```Shell
$ make uninstall
```
