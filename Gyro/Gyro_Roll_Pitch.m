% Prueba de obtención de Roll y Pitch del giroscopio
clear all
clc

s = serialport("COM3", 9600, "Timeout", 5);     % Inicializa el puerto serie

pitchVroll = zeros(300, 2);       % Matriz para almacenar 100 datos de Roll y Pitch (10s)
normPitch = zeros(300, 2);
T3 = [-1*ones(100,1),-1*ones(100,1)];
T2 = [1*ones(100,1),-1*ones(100,1)];
T1 = [ones(100,1), ones(100,1)];
R = [T1;T2;T3];
pitch = char();
roll = char();
muestreoFLAG = 0
minValue = 0;
maxValue = 1023;

for z = 1 :3
    muestreoFLAG = 1
    for i = 1: 100
        data = readline(s);
        data1 = char(data);
        %Detectar '<'
        if data1(1) == '<'   
            for k = 2 : 5
            pitch(k-1) = data1(k);
            end
            for k = 7 : 10
                roll(k-6) = data1(k);
            end    
        end   
        switch z
            case 1
                pitchVroll(i,1) = str2double(pitch);  
                pitchVroll(i,2) = str2double(roll);
                normPitch(i,1) = inputNorm(pitchVroll(i,1), minValue, maxValue);
                normPitch(i,2) = inputNorm(pitchVroll(i,2), minValue, maxValue); 
            case 2
                pitchVroll(i+100,1) = str2double(pitch);  
                pitchVroll(i+100,2) = str2double(roll);
                normPitch(i+100,1) = inputNorm(pitchVroll(i+100,1), minValue, maxValue);
                normPitch(i+100,2) = inputNorm(pitchVroll(i+100,2), minValue, maxValue); 
            case 3
                pitchVroll(i+200,1) = str2double(pitch);  
                pitchVroll(i+200,2) = str2double(roll);
                normPitch(i+200,1) = inputNorm(pitchVroll(i+200,1), minValue, maxValue);
                normPitch(i+200,2) = inputNorm(pitchVroll(i+200,2), minValue, maxValue); 
        end
        flush(s);
    end
    muestreoFLAG = 0
    % Pausa para cambiar a la otra muestra
    pause(10);
end








