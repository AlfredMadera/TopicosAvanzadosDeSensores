clc 

%load DataSet.mat

nodeHidden = 2;
outputs = 2;

fhidden = 'tansig';
foutput = 'tansig';

%% Training
[W1, b1, W2, b2, emedio] = neuralTrain(P, T, nodeHidden, fhidden, foutput);
figure
plot(emedio)
