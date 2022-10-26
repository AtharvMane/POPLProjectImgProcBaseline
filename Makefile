CXX=g++
INCLUDES = -I/usr/include/opencv4/
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
objects = addborder changing_contrast_and_brightness custom_filter drawing_cv fourier iterating_over_image maskin_operations smoothening thresholding understanding_mat
all: $(objects)
$(objects): %: %.cpp
	$(CXX) -o bin/$@ $^ $(INCLUDES) $(LIBS)
.PHONY: all
