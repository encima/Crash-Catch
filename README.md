# To Catch A Criminal

---

## Prerequisites

* OpenCV
* Python
	* BeautifulSoup
	* Requests

---

## Structure

* data - supporting data files (input videos and output images)
* src - Cpp and Python Script
* build - output files for Cpp

---

## Usage

* `cd src`
* `make`
* `cd ../build`
* `./crash-catch`
* Run through the input video and select an ROI (if needed) with a left click mouse drag
* Press `s` to save once the number plate is in shot
* Open the Python script and insert the number plate into the dict
* Save and `python plate_check.py`
* Matching plates will be saved to a text file in `data`

---

## TODO

Currently, this process is far more manual than I would like but it was a one time use hack and people seem to have shown interest. When I get time, I would like to add the following:

* Args for the c++ Script
* Clean up Makefile
* Visual ROI selection
* Auto extract of num plate using OpenCV (if one can be found)
* Read in possible plates from config file 
* More detailed response readout and error handling

Feel free to PR any of these

