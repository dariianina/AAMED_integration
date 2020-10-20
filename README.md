12/10/2020

To **run the prediction** on image:

`cd AAMED_integration`

`python main.py cmake-build/AAMED images/yourimage.jpg`


This generates .txt file for `yourimage.jpg` in **ellipse_cache** directory. The text file consists of lines each representing ellipse information sequence: ellipse centre x, y, height, width, angle and confidence.

i.e. 
58.589775 59.231426 94.059883 93.348831 27.287233 0.976734 (x, y, height, width, angle, confidence).


Image formats jpg, jpeg, png, tiff, bmp are okay. To support other formats refactor src/main.cpp main function.



To **recompile**:

`cd AAMED_integration/cmake-build`

`cmake ..`

`make `