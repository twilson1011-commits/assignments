# 1. Grayscale only
./imgtool images/Hulda.jpg out1.png --grayscale

# 2. Brighten then grayscale
./imgtool images/Hulda.jpg out2.png --brighten 50 --grayscale

# 3. Grayscale then brighten (different result from #2)
./imgtool images/Hulda.jpg out3.png --grayscale --brighten 50

# 4. Flip horizontally and vertically
./imgtool images/Hulda.jpg out4.png --flipH --flipV

# 5. Full pipeline with rotation
./imgtool images/Hulda.jpg out5.png --rotate 90 --grayscale --brighten 30 --blur

I used the luminance formula in the grayscale.cpp because it takes into effect that the eye is more sensitive 
to the color green so it needs more attention than the rest of the colors.
