%% EE-433 Project Berkay Yaldiz, Melih Can Zerin, Bevan Deniz Cilgin
clear
close all
clc
indexedImage = imread('car1.jpg');
figure
imshow(indexedImage)
Gray_Image= indexedImage(:,:,1)*0.299+indexedImage(:,:,2)*0.587+indexedImage(:,:,3)*0.114;
figure
imshow(Gray_Image)
RGB_image = gray_to_jet(Gray_Image,'jet');
figure
imshow(RGB_image)
RGB_matlab_image = ind2rgb(Gray_Image, jet);
figure
imshow(RGB_matlab_image)

