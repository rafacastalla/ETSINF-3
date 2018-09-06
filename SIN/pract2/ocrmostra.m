#!/usr/bin/octave -qf
load("OCR_14x14");
[N,L]=size(data); D=L-1;
I=reshape(data(1,1:D),14,14)';
imshow(1-I);
rand("seed",23); data=data(randperm(N),:);
for n=1:1000
I=reshape(data(n,1:196),14,14)';
imshow(1-I); pause(0.5);
end
